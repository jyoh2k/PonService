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

#ifndef __PON_SERVICE_HOST_H_
#define __PON_SERVICE_HOST_H_

#include <omnetpp.h>

#include "Common.h"
#include "Frame_m.h"

using namespace omnetpp;
/**
 * TODO - Generated class
 */
class Host : public cSimpleModule
{
    public:
        Host();
        virtual ~Host();
    protected:
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);
        virtual void finish();

        void scheduleNextPacket();
        void cancelNextPacket();
        void cancelMakeConnection();
        void makeConnection();
        void sendPacket();
        void receivePacket(cMessage *msg);


    private:
        char SLA;
        bool bNight;
        bool connected;
        int status;

        // send parameters
        int destID;
        long seqNum;

        cPar *reqLength;
        cPar *respLength;
        simtime_t sendInterval_High;
        simtime_t sendInterval_DAY;
        simtime_t sendInterval_NIGHT;
        simtime_t sendInterval_LOW;

        // self messages
        cMessage *transitionMsg;
        cMessage *pktGenerationTimerMsg;
        cMessage *connTimerMsg;
        simtime_t startTime;
        simtime_t stopTime;
        simtime_t timerInterval;
        simtime_t transitionTime;

        // receive statistics
        long packetsSent;
        long packetsReceived;
        simsignal_t sentPkSignal;
        simsignal_t rcvdPkSignal;
};

#endif
