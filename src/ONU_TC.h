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

#ifndef __TWDM_PON_ONU_TC_H_
#define __TWDM_PON_ONU_TC_H_

#include <omnetpp.h>
#include <queue>
#include <fstream>

#include "Common.h"
#include "Frame_m.h"

using namespace omnetpp;

typedef std::queue<EM*> Buffer;

/**
 * TODO - Generated class
 */
class ONU_TC : public cSimpleModule
{
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    void scheduleNextPacket();
    void constructEMChunks(TC_US* tcFrame, long grantSize);
    int processFromUpperLayer(cMessage *msg);
    int processFromLowerLayer(cMessage *msg);
    int processControlFrame(cMessage *msg);
    int parsingBWmap(BWMAP_ARRAY BWMAPs);
    int parsingPLOAMd(PLOAM_ARRAY PLOAMd);

    void FiniteStateMachine(int inputCode);
    void setModuleColor(int wavelength);
    virtual void finish();

  private:
    bool bActive;
    bool bTuningCompletion;
    bool bSleepCompletion;
    bool bPLOAMPending;
    bool even;

    PLOAM pendingPLOAM;

    char SLA;

    char state;
    int wavelength;
    int initialWavelength;
    int tuningWavelength;

    int grantSize;

    unsigned short ONU_ID;
    int EQD;

    long txBufferLen;
    long rxBufferLen;
    long queueLengthLimit;

    bool fragmented;
    Buffer txBuffer;
    Buffer rxBuffer;

    simtime_t txStartTime;

    simsignal_t txBufferSignal;
    //simsignal_t rxBufferSignal;
    simsignal_t queueDelaySignal;
    simsignal_t txRateSignal;
    simsignal_t waveRptSignal;
    simsignal_t tuningRangeSignal;
    simsignal_t dropRateSignal;

    cMessage* startMsg;
    cMessage* timerMsg;
    simtime_t timerInterval;
    simtime_t startTime;
    simtime_t stopTime;
    std::ofstream logOS;
};

#endif
