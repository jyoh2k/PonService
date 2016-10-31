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
simple Host
{
    parameters:
        double startTime @unit(s) = default(0s);  // time of sending the first request
        double stopTime @unit(s) = default(-1s);  // time of finishing sending, negative values mean forever
        double timerInterval @unit(s) = default(125us);  // interval between sending requests
        double transitionTime @unit(s) = default(5s);
                
        volatile int reqLength @unit(B) = default(1500B);  // length of request packets
        volatile int respLength @unit(B) = default(6000B);  // length of response packets

        @display("i=device/pc4");
        @signal[sentPk](type=GenericFrame);
        @signal[rcvdPk](type=GenericFrame);
        @statistic[rcvdPk](title="packets received"; source=rcvdPk; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);
        @statistic[sentPk](title="packets sent"; source=sentPk; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);
    gates:
        inout clientPort;
}
