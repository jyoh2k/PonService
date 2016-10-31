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

#include "ONU_TC.h"

Define_Module(ONU_TC);

void ONU_TC::initialize()
{
    // TODO - Generated method body
    bActive = false;
    even = true;
    bTuningCompletion = true;
    bSleepCompletion = true;
    bPLOAMPending = false;

    fragmented = false;

    switch(par("SLA").longValue())
    {
    case 2:
        SLA = 'H';
        break;
    case 1:
        SLA = 'M';
        break;
    default:
        SLA = 'L';
        break;
    }

    state = ONU_INITIAL_STATE0;
    wavelength = par("wavelength");
    initialWavelength = wavelength;
    setModuleColor(wavelength);


    grantSize = 0;

    ONU_ID = -1;
    EQD = -1;

    txStartTime = 0;
    txBufferLen = 0;
    rxBufferLen = 0;
    txBufferSignal = registerSignal("txBuffer");
    //rxBufferSignal = registerSignal("rxBuffer");
    queueDelaySignal = registerSignal("queueDelay");
    txRateSignal = registerSignal("txRate");
    waveRptSignal = registerSignal("waveRpt");
    tuningRangeSignal = registerSignal("tuningRange");
    dropRateSignal = registerSignal("dropRate");
    queueLengthLimit = par("queueLength");

    timerMsg = new cMessage("Timer_ONU");
    timerInterval = par("timerInterval");

    startTime = par("startTime");
    stopTime = par("stopTime");

    if (stopTime >= SIMTIME_ZERO && stopTime < startTime)
        error("Invalid startTime/stopTime parameters");

    startMsg = new cMessage("Start Alarm!");
    scheduleAt(startTime, startMsg);
    scheduleAt(startTime + timerInterval, timerMsg);

    if(DEBUG)
    {
        char fileName[255] = {};
        sprintf(fileName, "ONU[%d] Log.txt", getId());
        logOS.open(fileName);
    }
}

void ONU_TC::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
    int stateInputCode = NOTHING;
    if(msg->isSelfMessage())
    {
        if(msg == startMsg)
            bActive = true;
        else if(msg == timerMsg)
        {
            even = even ? false : true;
            if(even)
                emit(waveRptSignal, wavelength);
            else
                emit(waveRptSignal, wavelength+1);
            scheduleNextPacket();
        }
    }

    else
    {
        if(bActive)
        {
            if(strstr(msg->getArrivalGate()->getName(), "phyDataPort$i"))
                stateInputCode = processFromLowerLayer(msg);
            else if(strstr(msg->getArrivalGate()->getName(), "phyCtrlPort$i"))
                stateInputCode = processControlFrame(msg);
            else stateInputCode = processFromUpperLayer(msg);
        }
        else cancelAndDelete(msg);
    }

    FiniteStateMachine(stateInputCode);
}


void ONU_TC::scheduleNextPacket()
{
    simtime_t cur = simTime();
    simtime_t next = cur + timerInterval;

    if (stopTime<0 || next < stopTime)
        scheduleAt(next, timerMsg);
}

int ONU_TC::processFromUpperLayer(cMessage *msg)
{
    // TODO - Generated method body
    GenericFrame* genericFrame = check_and_cast<GenericFrame*>(msg);
    if(genericFrame->getType() == CONN)
    {
        int id = genericFrame->getSrc();
        genericFrame->setSrc(getId());
        genericFrame->setDest(id);
        char msgName[30] = {0, };
        if(state >= ONU_OPERATION_STATE)
        {
            genericFrame->setType(ACCEPT);
            sprintf(msgName, "Accept SLA(%c)", SLA);
        }
        else
        {
            genericFrame->setType(NOTACCEPT);
            sprintf(msgName, "Not Accepted");
        }


        genericFrame->setName(msgName);

        send(genericFrame, "servicePort$o");
    }

    else if(genericFrame->getType() == REQ)
    {
        if(queueLengthLimit<0 || (txBufferLen + genericFrame->getByteLength()) < queueLengthLimit)
        {
            EM* em = new EM;
            em->header.portID = ONU_ID;
            em->header.keyIndex = 0;
            em->header.Others = 0;
            strcpy(em->name, genericFrame->getName());
            em->payload.src = genericFrame->getSrc();
            em->payload.dest = genericFrame->getDest();
            em->payload.seqNum = genericFrame->getSeqNum();
            em->payload.type = genericFrame->getType();
            em->payload.responseBytes = genericFrame->getResponseBytes();
            strcpy(em->name, genericFrame->getName());
            em->header.LF = true;
            em->header.PLI = genericFrame->getByteLength();
            em->timeStamp = simTime().dbl();

            txBufferLen += (genericFrame->getByteLength());
            txBuffer.push(em);
            emit(txBufferSignal, txBufferLen);
            cancelAndDelete(genericFrame);
        }
        else
        {
            emit(dropRateSignal, genericFrame);
            cancelAndDelete(genericFrame);
        }
    }

    else
        cancelAndDelete(genericFrame);

    return NOTHING;
}

int ONU_TC::processFromLowerLayer(cMessage *msg)
{
    // TODO - Generated method body
    int tRetCode = DS_SYNC;
    TC_DS* tcFrame = check_and_cast<TC_DS*>(msg);
    BWMAP_ARRAY BWmap = tcFrame->getBWMAPs();
    PLOAM_ARRAY PLOAMs = tcFrame->getPLOAMd();
    EM_CHUNKS EMs = tcFrame->getEMs();

    int  tGrantCode = parsingBWmap(BWmap);
    int  tMsgCode = parsingPLOAMd(PLOAMs);

    tRetCode |= tGrantCode;
    tRetCode |= tMsgCode;

    while(!EMs.empty())
    {
        EM emFrame = EMs.front();
        EM* bufferedEM = new EM;
        memcpy(bufferedEM, &emFrame, sizeof(EM));
        EMs.pop();

        bool LF = bufferedEM->header.LF;
        rxBuffer.push(bufferedEM);
        rxBufferLen+=(bufferedEM->header.PLI+EM_HEADER_SIZE);

        if(LF)
        {
            long len = 0;

            EM reconstructedFrame;
            while(!rxBuffer.empty())
            {
                EM* tempBufferEM = rxBuffer.front();
                memcpy(&reconstructedFrame, tempBufferEM, sizeof(EM));
                len+=reconstructedFrame.header.PLI;
                rxBufferLen-=(reconstructedFrame.header.PLI+EM_HEADER_SIZE);
                delete tempBufferEM;
                rxBuffer.pop();
            }

            if(reconstructedFrame.header.portID == ONU_ID)
            {
                GenericFrame* outFrame = new GenericFrame;
                outFrame->setName(emFrame.name);
                outFrame->setSrc(emFrame.payload.src);
                outFrame->setDest(emFrame.payload.dest);
                outFrame->setSeqNum(emFrame.payload.seqNum);
                outFrame->setType(emFrame.payload.type);
                outFrame->setResponseBytes(emFrame.payload.responseBytes);
                outFrame->setByteLength(len);
                send(outFrame, "servicePort$o");
            }
        }
        //emit(rxBufferSignal, rxBufferLen);
    }
    cancelAndDelete(tcFrame);
    return tRetCode;
}

int ONU_TC::processControlFrame(cMessage *msg)
{
    GenericFrameWithPHYControl* ctrlMsg = check_and_cast<GenericFrameWithPHYControl*>(msg);
    if(ctrlMsg->getCommand() == ONU_MANAGEMENT_COMMAND_SUCCESS)
    {
        wavelength = ctrlMsg->getTuningWavelength();
        tuningWavelength = -1;
        cancelAndDelete(ctrlMsg);
        return TUNING_COMPLETION;
    }
    else
    {
        cancelAndDelete(ctrlMsg);
        return STATE_FAIL;
    }
    cancelAndDelete(ctrlMsg);
    return NOTHING;
}

int ONU_TC::parsingBWmap(BWMAP_ARRAY BWMAPs)
{
    int tRetCode = NOTHING;
    while(!BWMAPs.empty())
    {
        BWMAP aBWMAP = BWMAPs.front();
        BWMAPs.pop();

        if(!aBWMAP.DBRu && aBWMAP.grantSize <= 0)
        {
            tRetCode |= QUIET_GRANT;
        }

        if(aBWMAP.AllocID == ONU_ID)
        {
            grantSize = aBWMAP.grantSize;
            if(grantSize<0)
            {
                char msg[30] = {0, };
                sprintf(msg, "Grant Size (%d) Update Error!!", aBWMAP.grantSize);
                error(msg);
                tRetCode |= NOTHING;
            }
            else
            {
                txStartTime = ((double)aBWMAP.startTime*4*8)/US_TRANSMISSION_RATE;
                bubble("Grant!!");
                EV<<"Grant!!"<<endl;
                tRetCode |= BW_ALLOCATION;
            }
        }
    }
    return tRetCode;
}

int ONU_TC::parsingPLOAMd(PLOAM_ARRAY PLOAMd)
{
    char sla;
    int id=-1;
    //int ch = 0;
    int retCode = NOTHING;
    while(!PLOAMd.empty())
    {
        PLOAM aPLOAM = PLOAMd.front();
        if(aPLOAM.ONU_ID == ONU_ID || aPLOAM.ONU_ID == BROADCAST_ONU_ID)
        {
            switch(aPLOAM.Msg_Type_ID)
            {
                case ASSIGN_ONU_ID:
                    sscanf(&aPLOAM.Msg_Contents[2], "ONU[%3d]-%c", &id, &sla);
                    if(id == getParentModule()->getId() && sla == SLA)
                    {
                        ONU_ID = ((unsigned char)aPLOAM.Msg_Contents[0]<<8|(unsigned char)aPLOAM.Msg_Contents[1])&0xFFFF;
                        retCode |= ASSIGN_ID;
                        if(DEBUG)
                            logOS<<"ONU_ID assignment ["<< ONU_ID <<"]"<<endl;
                    }
                    break;

                case RANGING_TIME:
                    if(aPLOAM.ONU_ID == ONU_ID)
                    {
                        EQD = aPLOAM.Msg_Contents[6]<<24|aPLOAM.Msg_Contents[7]<<16|aPLOAM.Msg_Contents[8]<<8|aPLOAM.Msg_Contents[9];
                        retCode |= RANGING_ACK;
                    }
                    break;

                case WAVE_TUNING:
                    if(aPLOAM.ONU_ID == ONU_ID)
                    {
                        bTuningCompletion = false;
                        tuningWavelength = aPLOAM.Msg_Contents[0]&0x0F;
                        if(DEBUG)
                        {
                            logOS<<"Current Wavelength: channel - "<< wavelength <<endl;
                            logOS<<"Wavelength Tuning: channel - "<< tuningWavelength <<endl;
                        }
                        retCode |= TUNING_READY;
                    }
                    break;

                case PROFILE:
                    /*
                    for(ch = 0; ch<MAX_INTERFACE_NUM; ch++)
                    {
                        if(aPLOAM.Msg_Contents[33]&(1<<ch))
                            break;
                    }

                    if(ch != MAX_INTERFACE_NUM)
                        initialWavelength = ch;
                    else
                    {
                        if(aPLOAM.Msg_Contents[34] == 0x00)
                            initialWavelength = wavelength;
                        else
                        {
                            do
                            {
                                ch = rand()%MAX_INTERFACE_NUM;
                            }while(!(aPLOAM.Msg_Contents[33]&(1<<ch)));
                            initialWavelength = ch;
                        }
                    }*/
                    initialWavelength = wavelength;
                    retCode |= BURST_PROFILE;
                    break;

                case WAVE_CONFIRM:
                    if(aPLOAM.ONU_ID == ONU_ID)
                    {
                        bTuningCompletion = true;
                        retCode |= TUNING_CONFIRM;
                    }
                    break;

                case DISABLE_SN:
                case REQ_REGISTRATION:
                case ASSIGN_ALLOC_ID:
                case KEY_CTRL:
                case SLEEP_ALLOW:
                default:
                    break;
            }
        }
        else
        {

        }
        PLOAMd.pop();
    }
    return retCode;
}

void ONU_TC::FiniteStateMachine(int inputCode)
{
    if(inputCode == NOTHING)
        return;

    switch(state)
    {
        EV<<"ONU["<<ONU_ID<<"]'s state = "<<state<<endl;
        case ONU_INITIAL_STATE0:
            if(inputCode&DS_SYNC)
                state = ONU_INITIAL_STATE1;
            else if(inputCode&TIMEOUT)
            {
                GenericFrameWithPHYControl* ctrlMsg = new GenericFrameWithPHYControl("Wavelength Tuning");
                ctrlMsg->setType(GENERIC_CONTROL_FRAME);
                ctrlMsg->setCommand(ONU_TUNING);
                ctrlMsg->setTuningWavelength((wavelength++)%MAX_INTERFACE_NUM);
                send(ctrlMsg, "phyCtrlPort$o");
            }
            break;

        case ONU_INITIAL_STATE1:
            if(inputCode&BURST_PROFILE)
            {
                if(initialWavelength == wavelength)
                    state = ONU_INITIAL_TUNING_STATE1;
                else
                {
                    state = ONU_INITIAL_TUNING_STATE0;
                    GenericFrameWithPHYControl* ctrlMsg = new GenericFrameWithPHYControl("Wavelength Tuning");
                    ctrlMsg->setType(GENERIC_CONTROL_FRAME);
                    ctrlMsg->setCommand(ONU_TUNING);
                    ctrlMsg->setTuningWavelength(initialWavelength);
                    send(ctrlMsg, "phyCtrlPort$o");
                }
            }
            break;

        case ONU_INITIAL_TUNING_STATE0:
            if(inputCode&TUNING_COMPLETION)
                state = ONU_INITIAL_TUNING_STATE1;
        break;

        case ONU_INITIAL_TUNING_STATE1:
            if(inputCode&DS_SYNC)
                state = ONU_SN_STATE0;
        break;

        case ONU_SN_STATE0:
            if(inputCode&QUIET_GRANT)
            {
                state = ONU_SN_STATE1;
                PLOAM aPLOAM;
                aPLOAM.ONU_ID = BROADCAST_ONU_ID;
                aPLOAM.Msg_Type_ID = SN_ONU;
                sprintf(&aPLOAM.Msg_Contents[2], "ONU[%3d]-%c", getParentModule()->getId(), SLA);

                TC_US* upstreamFrame = NULL;
                upstreamFrame = new TC_US("US with SN_ONU");
                upstreamFrame->setPLOAMu(aPLOAM);
                upstreamFrame->setByteLength(52);
                //upstreamFrame->setKind(wavelength);
                sendDelayed(upstreamFrame, uniform(0, 40)*0.000001, "phyDataPort$o");
            }
            else if(inputCode&TIMEOUT)
                state = ONU_INITIAL_STATE0;
            break;

        case ONU_SN_STATE1:
            if(inputCode&ASSIGN_ID)
                state = ONU_RANGING_STATE0;
            if(inputCode&TIMEOUT)
                state = ONU_INITIAL_STATE0;
            break;

        case ONU_RANGING_STATE0:
            if(inputCode&QUIET_GRANT)
            {
                state = ONU_RANGING_STATE1;
                PLOAM aPLOAM;
                aPLOAM.ONU_ID = ONU_ID;
                aPLOAM.Msg_Type_ID = REGISTRATION;

                TC_US* upstreamFrame = NULL;
                upstreamFrame = new TC_US("US with Registration");
                upstreamFrame->setPLOAMu(aPLOAM);
                upstreamFrame->setByteLength(52);
                //upstreamFrame->setKind(wavelength);
                sendDelayed(upstreamFrame, uniform(0, 40)*0.000001, "phyDataPort$o");
            }
            else if(inputCode&STATE_FAIL)
                state = ONU_INITIAL_STATE0;
            break;

        case ONU_RANGING_STATE1:
            if(inputCode&RANGING_ACK)
                state = ONU_OPERATION_STATE;
            else if(inputCode&STATE_FAIL)
                state = ONU_INITIAL_STATE0;
            break;

        case ONU_OPERATION_STATE:
            if(inputCode&TUNING_READY)
            {
                PLOAM aPLOAM;
                aPLOAM.ONU_ID = ONU_ID;
                aPLOAM.Msg_Type_ID = WAVE_TUNING_ACK;
                aPLOAM.Msg_Contents[0] = tuningWavelength;

                TC_US* upstreamFrame = new TC_US("US with Tuning_ACK");
                upstreamFrame->setPLOAMu(aPLOAM);
                upstreamFrame->setByteLength(52);
                //upstreamFrame->setKind(wavelength);
                send(upstreamFrame, "phyDataPort$o");

                GenericFrameWithPHYControl* ctrlMsg = new GenericFrameWithPHYControl("Wavelength Tuning");
                ctrlMsg->setType(GENERIC_CONTROL_FRAME);
                ctrlMsg->setCommand(ONU_TUNING);
                ctrlMsg->setTuningWavelength(tuningWavelength);
                send(ctrlMsg, "phyCtrlPort$o");

                if(DEBUG)
                {
                    logOS<<"Current Wavelength: channel - "<< wavelength <<endl;
                    logOS<<"Tuning ACK: channel - "<< tuningWavelength <<endl;
                }

                state = ONU_TUNING_STATE;
                emit(tuningRangeSignal, wavelength>tuningWavelength ? (wavelength-tuningWavelength) : (tuningWavelength-wavelength));
            }

            else if(inputCode&BW_ALLOCATION)
            {
                if(grantSize<0)
                {
                    error("Grant Size Error!!");
                    return;
                }

                TC_US* upstreamFrame = NULL;
                upstreamFrame = new TC_US("US");
                constructEMChunks(upstreamFrame, grantSize*4);
                upstreamFrame->setONU_ID(ONU_ID);
                upstreamFrame->setByteLength(grantSize*4);

                DBRU tempDBRu;
                tempDBRu.push(txBufferLen/4);
                upstreamFrame->setDBRu(tempDBRu);

                //upstreamFrame->setKind(wavelength);
                sendDelayed(upstreamFrame, txStartTime, "phyDataPort$o");
                grantSize = 0;
                txStartTime = -1;
            }

            break;
        case ONU_TUNING_STATE:
            if(inputCode&TUNING_COMPLETION)
                state = ONU_ILODS_STATE;
            break;
        case ONU_ILODS_STATE:
            if(inputCode&TUNING_CONFIRM)
            {
                state = ONU_OPERATION_STATE;
                PLOAM aPLOAM;
                aPLOAM.ONU_ID = ONU_ID;
                aPLOAM.Msg_Type_ID = WAVE_TUNING_RESPONSE;
                aPLOAM.Msg_Contents[0] = wavelength;

                TC_US* upstreamFrame = new TC_US("US with Tuning_Response");
                upstreamFrame->setPLOAMu(aPLOAM);
                upstreamFrame->setByteLength(52);
                send(upstreamFrame, "phyDataPort$o");
                setModuleColor(wavelength);
            }
            else if(inputCode&TIMEOUT)
                state = ONU_INITIAL_STATE0;

            //else
            //    state = ONU_OPERATION_STATE;

            break;
        case ONU_EMERGENCY_STATE:
            break;
        default:
            break;
    }
}

void ONU_TC::constructEMChunks(TC_US* tcFrame, long grantByteSize)
{
    long len = 0;
    long remainingBytes = grantByteSize;    //Bytes
    simtime_t ts = 0;
    EM_CHUNKS tempEMs;

    while(remainingBytes>0)
    {
        if(txBuffer.empty())
        {
            EV<<"ONU["<<ONU_ID<<"]'s Buffer is empty!!"<<endl;
            if(txBufferLen>0)
                error("BufferManagement is Weird!!");
            break;
        }

        EM* em = txBuffer.front();
        len = em->header.PLI+EM_HEADER_SIZE;

        EM transmittedEM;
        memcpy(&transmittedEM, em, sizeof(EM));

        if(remainingBytes >= len)
        {
            transmittedEM.header.PLI = em->header.PLI;
            transmittedEM.header.LF = true;
            remainingBytes -= len;
            ts = transmittedEM.timeStamp;
            txBufferLen-=em->header.PLI;
            txBuffer.pop();
            delete em;
        }
        else
        {
            transmittedEM.header.PLI = remainingBytes-EM_HEADER_SIZE;
            transmittedEM.header.LF = false;
            em->header.PLI -= (remainingBytes-EM_HEADER_SIZE);
            ts = transmittedEM.timeStamp;
            txBufferLen -= (remainingBytes-EM_HEADER_SIZE);
            remainingBytes = 0;
        }

        tempEMs.push(transmittedEM);
    }

    tcFrame->setEMs(tempEMs);
    emit(txRateSignal, grantByteSize);
    emit(txBufferSignal, txBufferLen);
    emit(queueDelaySignal, simTime() - ts);
}

void ONU_TC::setModuleColor(int wavelength)
{
    char dispStr[30] = {0, };
    switch(wavelength)
    {
    case 0:
        sprintf(dispStr, "i=device/device,red");
        break;
    case 1:
        sprintf(dispStr, "i=device/device,green");
        break;
    case 2:
        sprintf(dispStr, "i=device/device,blue");
        break;
    case 3:
        sprintf(dispStr, "i=device/device,white");
        break;
    case 4:
        sprintf(dispStr, "i=device/device,yellow");
        break;
    case 5:
        sprintf(dispStr, "i=device/device,cyan");
        break;
    case 6:
        sprintf(dispStr, "i=device/device,magenta");
        break;
    case 7:
        sprintf(dispStr, "i=device/device,black");
        break;
    default:
        sprintf(dispStr, "i=device/device,grey");
        break;
    }
    getParentModule()->getDisplayString().parse(dispStr);
}

void ONU_TC::finish()
{
    // TODO - Generated method body
    while(!txBuffer.empty())
    {
        EM* em = txBuffer.front();
        delete em;
        txBuffer.pop();
    }

    while(!rxBuffer.empty())
    {
        EM* em = rxBuffer.front();
        delete em;
        rxBuffer.pop();
    }

    if(DEBUG)
        logOS.close();

    cancelAndDelete(startMsg);
}
