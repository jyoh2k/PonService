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

package pon_service;

module ONU
{
    parameters:
        int initWavelength = default(0);
        @display("i=device/device;bgb=292,273");
    gates:
//        inout accessPort;
        inout clientPort;
    submodules:
        onu_phyif: ONU_PhyIF {
            wavelength = initWavelength;
            @display("p=200,126");
        }
        onu_tc: ONU_TC {
            wavelength = initWavelength;
            @display("p=80,126");
        }
    connections:
//        onu_phyif.phyDataPort <--> accessPort;
        onu_phyif.tcPort <--> onu_tc.phyDataPort;
        onu_tc.servicePort <--> clientPort;
        onu_tc.phyCtrlPort <--> onu_phyif.phyCtrlPort;
}
