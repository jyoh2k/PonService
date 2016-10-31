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

#include "ONU_PhyIF.h"

Define_Module(ONU_PhyIF);

ONU_PhyIF::ONU_PhyIF()
{

}
ONU_PhyIF::~ONU_PhyIF()
{

}

void ONU_PhyIF::initialize()
{
    // TODO - Generated method body
    status = RUNNING;
    activationDelay = par("activationDelay");
    tuningDelay = par("tuningDelay");
    wavelength = par("wavelength");
    minWavelength = par("minWavelength");
    maxWavelength = par("maxWavelength");
    changeMsg = new cMessage("Tuning Complete!!");

    if(DEBUG)
    {
        char fileName[255]={0, };
        sprintf(fileName, "ONU_PHY[%d] Log.txt", getId());
        logOS.open(fileName);
    }
}

void ONU_PhyIF::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
    if(msg->isSelfMessage())
    {
        GenericFrameWithPHYControl* ctrlMsg = new GenericFrameWithPHYControl("TF MSG!!");
        wavelength = tuningWavelength;
        tuningWavelength = -1;
        ctrlMsg->setCommand(ONU_MANAGEMENT_COMMAND_SUCCESS);
        ctrlMsg->setTuningWavelength(wavelength);
        setModuleColor(wavelength);
        send(ctrlMsg, "phyCtrlPort$o");
    }

    else
    {
        if(strstr(msg->getArrivalGate()->getName(), "phyCtrlPort"))
            processControlFrame(msg);
        else
            processDataFrame(msg);
    }
}

void ONU_PhyIF::processControlFrame(cMessage *msg)
{
    GenericFrameWithPHYControl* ctrlMsg = check_and_cast<GenericFrameWithPHYControl*>(msg);
    switch(ctrlMsg->getCommand())
    {
    case ONU_SLEEP:
        break;
    case ONU_DOZE:
        break;
    case ONU_WAKEUP:
        break;
    case ONU_TUNING:
        tuningWavelength = -1;
        tuningWavelength = ctrlMsg->getTuningWavelength();
        ctrlMsg->setCommand(ONU_MANAGEMENT_COMMAND_SUCCESS);
        scheduleAt(simTime() + tuningDelay, changeMsg);
        break;
    default:
        break;
    }
    cancelAndDelete(ctrlMsg);
}

void ONU_PhyIF::processDataFrame(cMessage *msg)
{
    cGate* gOut = NULL;
    cChannel* ch = NULL;

    if(strcmp(msg->getArrivalGate()->getName(),"tcPort$i")==0)
    {
        TC_US* tcFrame = check_and_cast<TC_US *>(msg);
        tcFrame->setKind(wavelength);
        tcFrame->setWavelength(wavelength);

        if(DEBUG)
        {
            PLOAM debugPLOAM = tcFrame->getPLOAMu();
            if(debugPLOAM.Msg_Type_ID == WAVE_TUNING_ACK)
            {
                int debugWavelength = tcFrame->getKind();
                logOS<<"ONU ID["<<debugPLOAM.ONU_ID<<"] : "<<(int)debugPLOAM.Msg_Contents[0]<<endl;
                logOS<<"through wavelength["<<debugWavelength<<"]"<<endl;
            }
        }

        //gOut = gate("phyDataPort$o");     @jason
        EV << "@jason ==> gOut = gate(\"phyDataPort$o\")";

        ch = gOut->getChannel();

        if(!ch||!ch->isTransmissionChannel()) send(tcFrame, gOut);
        else
        {
            simtime_t finishTime = ch->getTransmissionFinishTime();
            simtime_t delay = finishTime > simTime() ? finishTime - simTime() : 0;
            sendDelayed(tcFrame, delay, gOut);
        }
    }
    else
    {
        TC_DS* tcFrame = check_and_cast<TC_DS *>(msg);
        if(tcFrame->getKind() == wavelength)
        {

            gOut = gate("tcPort$o");
            ch = gOut->getChannel();

            if(!ch||!ch->isTransmissionChannel()) send(tcFrame, gOut);
            else
            {
                simtime_t finishTime = ch->getTransmissionFinishTime();
                simtime_t delay = finishTime > simTime() ? finishTime - simTime() : 0;
                sendDelayed(tcFrame, delay, gOut);
            }
        }

        else
        {
            //EV<<"Wavelength "<<tcFrame->getKind()<<" Filtered";
            cancelAndDelete(tcFrame);
            return;
        }
    }
}

void ONU_PhyIF::setModuleColor(int wavelength)
{
    char dispStr[30] = {0, };
    switch(wavelength)
    {
    case 0:
        sprintf(dispStr, "p=200,126;i=block/rxtx,red");
        break;
    case 1:
        sprintf(dispStr, "p=200,126;i=block/rxtx,green");
        break;
    case 2:
        sprintf(dispStr, "p=200,126;i=block/rxtx,blue");
        break;
    case 3:
        sprintf(dispStr, "p=200,126;i=block/rxtx,white");
        break;
    case 4:
        sprintf(dispStr, "p=200,126;i=block/rxtx,yellow");
        break;
    case 5:
        sprintf(dispStr, "p=200,126;i=block/rxtx,cyan");
        break;
    case 6:
        sprintf(dispStr, "p=200,126;i=block/rxtx,magenta");
        break;
    case 7:
        sprintf(dispStr, "p=200,126;i=block/rxtx,black");
        break;
    default:
        sprintf(dispStr, "p=200,126;i=block/rxtx,grey");
        break;
    }
    getDisplayString().parse(dispStr);
}

void ONU_PhyIF::finish()
{
    if(changeMsg)
        cancelAndDelete(changeMsg);

    if(DEBUG)
        logOS.close();
}
