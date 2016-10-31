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

package twdm_pon;

//
// TODO auto-generated module
//
simple ONU_TC
{
    parameters:
        @display("i=device/cpu");
        @signal[txBuffer](type="long");
        //@signal[rxBuffer](type="long");
        //@signal[queueDelay](type="double");
        @signal[queueDelay](type="simtime_t");  //@jason
        @signal[tuningRange](type="long");
        @signal[txRate](type="long");
        //@signal[wavelength](type="long");
        @signal[waveRpt](type="long");
        @signal[dropRate](type="type=GenericFrame");
        @statistic[txBuffer](title="Transmission Buffer"; source=txBuffer; record=vector; interpolationmode=none);
        //@statistic[rxBuffer](title="Receipt Buffer"; source=rxBuffer; record=count,vector; interpolationmode=none);
        @statistic[queueDelay](title="Queueing delay"; source=queueDelay; record=vector; interpolationmode=none);
        @statistic[tuningRange](title="Tuning Range"; source=tuningRange; record=count; interpolationmode=none);
        @statistic[txRate](title="Transmission Rate"; source=txRate; record=vector; interpolationmode=none);
        @statistic[waveRpt](title="Wavelength Trace"; source=waveRpt; record=vector; interpolationmode=none);
        @statistic[dropRate](title="Packet drop"; source=dropRate;  record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);

        int SLA = default(1);
        int wavelength = default(0);
        int queueLength @unit("B") = default(100MiB);
        double timerInterval @unit(s) = default(125us);  // interval between sending requests
        double startTime @unit(s) = default(0s);  // time of sending the first request
        double stopTime @unit(s) = default(-1s);  // time of finishing sending, negative values mean forever

    gates:
        inout phyDataPort;
        inout phyCtrlPort;
        inout servicePort;
}

