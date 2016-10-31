package pon_service;

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
