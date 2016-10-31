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

#ifndef __TWDM_PON_ONU_PHYIF_H_
#define __TWDM_PON_ONU_PHYIF_H_

#include <omnetpp.h>
#include <fstream>

#include "Common.h"
#include "Frame_m.h"

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class ONU_PhyIF : public cSimpleModule
{
    public:
        ONU_PhyIF();
        ~ONU_PhyIF();
    protected:
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);
        virtual void processControlFrame(cMessage *msg);
        virtual void processDataFrame(cMessage *msg);
        void setModuleColor(int wavelength);
        virtual void finish();

    private:
        cMessage *changeMsg;
        simtime_t activationDelay;
        simtime_t tuningDelay;

        int status;
        int wavelength;
        int tuningWavelength;
        int minWavelength;
        int maxWavelength;

        std::ofstream logOS;
};
#endif
