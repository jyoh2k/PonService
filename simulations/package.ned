package twdm_pon.simulations;

//import ned.DelayChannel;
//import twdm_pon.Fiber;
import twdm_pon.Host;
//import twdm_pon.Metro;
//import twdm_pon.OLT;
import twdm_pon.ONU;
//import twdm_pon.Splitter;

@license(LGPL);

network TWDM_PON
{
    parameters:
        @display("bgb=1901,1556,,,0;i=background/streetmap;bgi=background/streetmap,s");
    types:
//        channel DistributedFiber extends DelayChannel
//        {
//            delay = default(33.356us);
//        }

    submodules:
//        metro: Metro {
//            @display("p=126,749");
//        }
//        olt: OLT {
//            @display("p=239,749");
//        }
//        splitter: Splitter {
//            @display("p=581.94403,743.768");
//        }
        onu: ONU {
            @display("p=958.49603,273.85602");
        }
        host: Host {
            @display("p=1338.16,236.51201");
        }
//        onu1: ONU {
//            @display("p=958.49603,560.16003");
//        }
//        host1: Host {
//            @display("p=1297.7041,578.83203");
//        }
//        onu2: ONU {
//            @display("p=958.49603,852.68805");
//        }
//        host2: Host {
//            @display("p=1297.7041,852.68805");
//        }
//        onu3: ONU {
//            @display("p=958.49603,1185.672");
//        }
//        host3: Host {
//            @display("p=1297.7041,1182.56");
//        }
//        onu4: ONU {
//            @display("p=860,228");
//        }
//        host4: Host {
//            @display("p=860,128");
//        }
//        onu5: ONU {
//            @display("p=960,228");
//        }
//        host5: Host {
//            @display("p=960,128");
//        }
//        onu6: ONU {
//            @display("p=1060,228");
//        }
//        host6: Host {
//            @display("p=1060,128");
//        }
//        onu7: ONU {
//            @display("p=1160,228");
//        }
//        host7: Host {
//            @display("p=1160,128");
//        }

//        fiber: Fiber {
//            @display("p=401.44803,743.768");
//        }
    //        host8: Host {
    //            @display("p=1159,1419");
    //        }
    //        host9: Host {
    //            @display("p=1059,1425");
    //        }
    //        host10: Host {
    //            @display("p=958,1419");
    //        }
    //        host11: Host {
    //            @display("p=858,1419");
    //        }
    //        host12: Host {
    //            @display("p=758,1425");
    //        }
    //        host13: Host {
    //            @display("p=658,1425");
    //        }
    //        host14: Host {
    //            @display("p=559,1425");
    //        }
    //        host15: Host {
    //            @display("p=458,1425");
    //        }
    //        onu8: ONU {
    //            @display("p=1160,1303");
    //        }
    //        onu9: ONU {
    //            @display("p=1060,1303");
    //        }
    //        onu10: ONU {
    //            @display("p=959,1303");
    //        }
    //        onu11: ONU {
    //            @display("p=860,1297");
    //        }
    //        onu12: ONU {
    //            @display("p=760,1297");
    //        }
    //        onu13: ONU {
    //            @display("p=659,1303");
    //        }
    //        onu14: ONU {
    //            @display("p=560,1303");
    //        }
    //        onu15: ONU {
    //            @display("p=460,1303");
    //        }
    //        host16: Host {
    //            @display("p=1557,161");
    //        }
    //        host17: Host {
    //            @display("p=1557,241");
    //        }
    //        host18: Host {
    //            @display("p=1562,320");
    //        }
    //        host19: Host {
    //            @display("p=1562,406");
    //        }
    //        host20: Host {
    //            @display("p=1564,487");
    //        }
    //        host21: Host {
    //            @display("p=1568,559");
    //        }
    //        host22: Host {
    //            @display("p=1564,646");
    //        }
    //        host23: Host {
    //            @display("p=1562,731");
    //        }
    //        host24: Host {
    //            @display("p=1557,825");
    //        }
    //        host25: Host {
    //            @display("p=1557,905");
    //        }
    //        host26: Host {
    //            @display("p=1562,984");
    //        }
    //        host27: Host {
    //            @display("p=1562,1070");
    //        }
    //        host28: Host {
    //            @display("p=1564,1151");
    //        }
    //        host29: Host {
    //            @display("p=1568,1223");
    //        }
    //        host30: Host {
    //            @display("p=1564,1310");
    //        }
    //        host31: Host {
    //            @display("p=1562,1395");
    //        }
    //        onu16: ONU {
    //            @display("p=1432,161");
    //        }
    //        onu17: ONU {
    //            @display("p=1430,241");
    //        }
    //        onu18: ONU {
    //            @display("p=1432,320");
    //        }
    //        onu19: ONU {
    //            @display("p=1432,406");
    //        }
    //        onu20: ONU {
    //            @display("p=1434,487");
    //        }
    //        onu21: ONU {
    //            @display("p=1434,559");
    //        }
    //        onu22: ONU {
    //            @display("p=1434,646");
    //        }
    //        onu23: ONU {
    //            @display("p=1434,731");
    //        }
    //        onu24: ONU {
    //            @display("p=1432,825");
    //        }
    //        onu25: ONU {
    //            @display("p=1430,905");
    //        }
    //        onu26: ONU {
    //            @display("p=1432,984");
    //        }
    //        onu27: ONU {
    //            @display("p=1432,1070");
    //        }
    //        onu28: ONU {
    //            @display("p=1434,1151");
    //        }
    //        onu29: ONU {
    //            @display("p=1434,1223");
    //        }
    //        onu30: ONU {
    //            @display("p=1434,1310");
    //        }
    //        onu31: ONU {
    //            @display("p=1434,1395");
    //        }
    connections:
//        metro.commPort <--> olt.metroPort;
//        olt.accessPort <--> fiber.OLTSidePort;
//        fiber.ONUSidePort <--> splitter.oltPort;
        onu.clientPort <--> host.clientPort;
//        onu1.clientPort <--> host1.clientPort;
//        onu2.clientPort <--> host2.clientPort;
//        onu3.clientPort <--> host3.clientPort;
        //        onu4.clientPort <--> host4.clientPort;
        //        onu5.clientPort <--> host5.clientPort;
        //        onu6.clientPort <--> host6.clientPort;
        //        onu7.clientPort <--> host7.clientPort;
//        splitter.onuPort++ <--> DistributedFiber <--> onu.accessPort;
//        splitter.onuPort++ <--> DistributedFiber <--> onu1.accessPort;
//        splitter.onuPort++ <--> DistributedFiber <--> onu2.accessPort;
//        splitter.onuPort++ <--> DistributedFiber <--> onu3.accessPort;
}
