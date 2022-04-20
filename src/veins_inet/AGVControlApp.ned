package lab001.veins_inet;//Phai tao ra trong thu muc viens_inet
//import org.car2x.veins.modules.application.ieee80211p.DemoBaseApplLayer;
import org.car2x.veins.modules.application.traci.TraCIDemo11p;
//
// network description file for your Veins Application. Add parameters here
//
simple AGVControlApp extends TraCIDemo11p
{
    //Khai bao namespace cua VehicleControlApp la veins
    //nen o day chung ta dung veins::
    @class(veins::AGVControlApp);
    string appName = default("My first Veins App!");
}
