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

#include "AGVControlApp.h"
#include "Constant.h"
#include "veins/modules/application/traci/TraCIDemo11pMessage_m.h"


using namespace veins;

Register_Class(AGVControlApp);

void AGVControlApp::initialize(int stage)
{
    TraCIDemo11p::initialize(stage);
    if (stage == 0) {
        int idDebug = getId();
        sendBeacon= new cMessage("send Beacon");
        if(idDebug == 15){
            mobility = TraCIMobilityAccess().get(getParentModule());
            traciVehicle = mobility->getVehicleCommandInterface();
        }
    }
    else if (stage == 1) {

        if (sendBeacon->isScheduled())
        {
            cancelEvent(sendBeacon);
        }
        scheduleAt(simTime() + 0.1, sendBeacon);
        //EV<<"Send to RSU. Waiting for response from RSU!";
    }
}

void AGVControlApp::finish()
{
    TraCIDemo11p::finish();
    //EV<<"Reach destination over here"<<endl;
    // statistics recording goes here
}

void AGVControlApp::onBSM(DemoSafetyMessage* bsm)
{
    //for my own simulation circle
}

void AGVControlApp::onWSM(BaseFrame1609_4* wsm)
{
    // Your application has received a data message from another car or RSU
    // code for handling the message goes here, see TraciDemo11p.cc for examples
}

void AGVControlApp::onWSA(DemoServiceAdvertisment* wsa)
{
    // Your application has received a service advertisement from another car or RSU
    // code for handling the message goes here, see TraciDemo11p.cc for examples
}

void AGVControlApp::handleSelfMsg(cMessage* msg)
{
    TraCIDemo11p::handleSelfMsg(msg);
    // this method is for self messages (mostly timers)
    // it is important to call the DemoBaseApplLayer function for BSM and WSM transmission
    {
        TraCIDemo11pMessage* carBeacon = new TraCIDemo11pMessage("test", 0);
        carBeacon->setDemoData(Constant::FIRST);
        carBeacon->setSenderAddress(myId);
        BaseFrame1609_4* WSM = new BaseFrame1609_4();
        WSM->encapsulate(carBeacon);
        populateWSM(WSM);
        send(WSM,lowerLayerOut);
        return;
    }
}

void AGVControlApp::handlePositionUpdate(cObject* obj)
{
    TraCIDemo11p::handlePositionUpdate(obj);
    // the vehicle has moved. Code that reacts to new positions goes here.
    // member variables such as currentPosition and currentSpeed are updated in the parent class

}

void AGVControlApp::handleLowerMsg(cMessage* msg)
{
    BaseFrame1609_4* WSM = check_and_cast<BaseFrame1609_4*>(msg);
    cPacket* enc = WSM->getEncapsulatedPacket();
    if(TraCIDemo11pMessage* bc = dynamic_cast<TraCIDemo11pMessage*>(enc)){
        char *ret = mergeContent(myId);

        if(strcmp(ret, bc->getDemoData()) == 0){
            if(traciVehicle->getSpeed() <= 5){
                traciVehicle->setSpeedMode(0x06);
                traciVehicle->setSpeed(20);
            }
            else if(false){
                std::string land ("B0toB1_0");
                std::string new_land("B1toB0_0");
                std::string sub_new_land("B1toB0_1");
                if(land.compare(traciVehicle->getLaneId()) == 0
                        && new_land.compare(traciVehicle->getLaneId()) != 0
                        && sub_new_land.compare(traciVehicle->getLaneId()) != 0
                        )
                {
                    if(myId == 16)
                        EV<<"\tprepare to change route of "<<myId<<endl;
                    //willChange = true;
                    bool change = traciVehicle->changeVehicleRoute({
                        "B0toB1", "B1toB0", "B0toA0", "A0toA1"
                    });
                    if(myId == 16)
                        EV<<"Could change route? "<<change<<endl;
                }
            }
        }
    }
    else{

    }
}
