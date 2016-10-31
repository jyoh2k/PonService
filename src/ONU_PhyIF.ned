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
simple ONU_PhyIF
{
    parameters:
        int wavelength = default(0);
        int minWavelength = default(0);
        int maxWavelength = default(8);
        double activationDelay @unit(s) = default(125us);
        double tuningDelay @unit(s) = default(10ms);

        @display("i=block/rxtx");
    gates:
//        inout phyDataPort;
        inout phyCtrlPort;
        inout tcPort;
}
