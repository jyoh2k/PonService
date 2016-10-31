package pon_service;

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
