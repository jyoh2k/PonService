//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "Host.h"

Define_Module(Host);

Host::Host()
{
    reqLength = NULL;
    respLength = NULL;
}

Host::~Host()
{
}

void Host::initialize()
{
    // TODO - Generated method body
    reqLength = &par("reqLength");
    respLength = &par("respLength");

    sendInterval_High = 0.00125;
    sendInterval_DAY = 0.000125;
    sendInterval_NIGHT = 0.000500;
    sendInterval_LOW = 0.000500;

    transitionTime = par("transitionTime");
    bNight = false;

    timerInterval = par("timerInterval");
    connected = false;

    destID = getSimulation()->getModuleByPath("PON_SERVICE.onu")->getId();  //@jason
    seqNum = 0;
    WATCH(seqNum);

    // statistics
    packetsSent = packetsReceived = 0;
    sentPkSignal = registerSignal("sentPk");
    rcvdPkSignal = registerSignal("rcvdPk");
    WATCH(packetsSent);
    WATCH(packetsReceived);

    startTime = par("startTime");
    stopTime = par("stopTime");
    if (stopTime >= SIMTIME_ZERO && stopTime < startTime)
        error("Invalid startTime/stopTime parameters");

    transitionMsg = new cMessage("Day-Night Transition");
    pktGenerationTimerMsg = new cMessage("Pkt_Gen MSG");
    connTimerMsg = new cMessage("Conn_Timer MSG");
    scheduleAt(startTime+0.5, transitionMsg);
    scheduleAt(startTime+timerInterval, connTimerMsg);
    SLA = 'N';
}

void Host::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
    if (msg->isSelfMessage())
   {
       if(msg == connTimerMsg && !connected)
           makeConnection();
       else if(msg == transitionMsg)
       {
           bNight = bNight ? false : true;
           scheduleAt(simTime()+transitionTime, transitionMsg);
       }
       else if(msg == pktGenerationTimerMsg)
       {
           sendPacket();
           scheduleNextPacket();
       }
       else error("Wrong message at Host!!");
   }
   else
       receivePacket(msg);
}

void Host::scheduleNextPacket()
{
    simtime_t next = 0;
    switch(SLA)
    {
    case 'H':
        next = simTime() + exponential(sendInterval_High);
        break;
    case 'M':
        if(bNight)
            next = simTime() + exponential(sendInterval_NIGHT);
        else
            next = simTime() + exponential(sendInterval_DAY);
        break;
    case 'L':
        next = simTime() + exponential(sendInterval_LOW);
        break;
    default:
        next = simTime() + exponential(sendInterval_LOW);
        break;
    }


    if (stopTime<0 || next < stopTime)
        scheduleAt(next, pktGenerationTimerMsg);
}

void Host::cancelNextPacket()
{
    if(pktGenerationTimerMsg)
        cancelEvent(pktGenerationTimerMsg);
}

void Host::cancelMakeConnection()
{
    if(connTimerMsg)
        cancelEvent(connTimerMsg);
}

void Host::makeConnection()
{
    char msgname[30];
    sprintf(msgname, "Connection-%d", getId());
    EV << "Connection packet `" << msgname << "'\n";

    GenericFrame *connFrame = new GenericFrame(msgname);

    connFrame->setSrc(getId());
    connFrame->setDest(destID);
    connFrame->setType(CONN);

    send(connFrame, "clientPort$o");
}


void Host::sendPacket()
{
    seqNum++;

    char msgname[30];
    sprintf(msgname, "req-%d-%ld", getId(), seqNum);
    EV << "Generating packet `" << msgname << "'\n";

    GenericFrame *dataFrame = new GenericFrame(msgname);

    dataFrame->setSrc(getId());
    dataFrame->setDest(destID);
    dataFrame->setSeqNum(seqNum);
    dataFrame->setType(REQ);

    long len = reqLength->longValue();
    dataFrame->setByteLength(len);

    long respLen = respLength->longValue();
    dataFrame->setResponseBytes(respLen);

    emit(sentPkSignal, dataFrame);
    send(dataFrame, "clientPort$o");
    packetsSent++;
}

void Host::receivePacket(cMessage *msg)
{
    GenericFrame* frame = check_and_cast<GenericFrame*>(msg);
    if(frame->getType() == ACCEPT)
    {
        bubble("Connected!!");
        connected = true;
        sscanf(frame->getName(), "Accept SLA(%c)", &SLA);
        cancelMakeConnection();
        scheduleNextPacket();
    }

    else if(frame->getType() == NOTACCEPT)
    {
            bubble("Not Connected!!");
            scheduleAt(simTime()+timerInterval, connTimerMsg);
    }

    else
    {
        if(frame->getDest() == getId())
        {
            EV << "Received packet `" << frame->getName() << "'\n";
            bubble("Received packet");
            packetsReceived++;
            emit(rcvdPkSignal, msg);
        }

        else EV << "Received wrong packet `" << frame->getName() << "'\n";
    }

    delete msg;
}

void Host::finish()
{
    if(transitionMsg)
        cancelAndDelete(transitionMsg);
    if(pktGenerationTimerMsg)
        cancelAndDelete(pktGenerationTimerMsg);
    if(connTimerMsg)
        cancelAndDelete(connTimerMsg);
}
