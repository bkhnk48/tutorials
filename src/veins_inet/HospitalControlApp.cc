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
// along with this program. If not, see http://www.gnu.org/licenses/.
// 

#include "HospitalControlApp.h"

#include "Constant.h"
//#include "HashAPI.cpp"
//#include "UnitTest.cpp"
//#include "ReadFile.cpp"

#include "veins/modules/application/traci/TraCIDemo11pMessage_m.h"

using namespace veins;

Register_Class(HospitalControlApp);

void HospitalControlApp::initialize(int stage)
{
    TraCIDemoRSU11p::initialize(stage);
    if(graphGenerator == NULL){
        graphGenerator = new Parser();
        graphGenerator->readFile();
    }
    if (stage == 0) {
        sendBeacon= new cMessage("send Beacon");
    }
    else if (stage == 1) {
        // Initializing members that require initialized other modules goes here
        //traci->getperson->getIDList();
    }
    //mobility = TraCIMobilityAccess().get(getParentModule());
    //if(mobility == NULL){
    //    EV<<"Mobility = NULL"<<endl;
    //}
    //else
    //    traci = mobility->getCommandInterface();
}

/*Coord HospitalControlApp::getPositionById(int personId){
    return traci->genericGetCoord(CMD_GET_PERSON_VARIABLE, personId, VAR_POSITION, RESPONSE_GET_PERSON_VARIABLE);
}*/

void HospitalControlApp::finish()
{
    //Duoc goi khi RSU ket thuc cong viec
    TraCIDemoRSU11p::finish();
    if(traci == NULL){
        EV<<"NULL eventually"<<endl;
    }
    if(Constant::activation == NULL){
            EV<<"Constant is helpless eventually"<<endl;
    }
    // statistics recording goes here
}

void HospitalControlApp::onBSM(DemoSafetyMessage* bsm)
{
    //for my own simulation circle
}

void HospitalControlApp::onWSM(BaseFrame1609_4* wsm)
{
    // Your application has received a data message from another car or RSU
    // code for handling the message goes here, see TraciDemo11p.cc for examples
    cPacket* enc = wsm->getEncapsulatedPacket();
    if(TraCIDemo11pMessage* bc = dynamic_cast<TraCIDemo11pMessage*>(enc)){
        if(strcmp(Constant::FIRST, bc->getDemoData()) == 0
                && wsm->getKind() == 0
        ){
            //EV << "my message = " <<bc->getDemoData()<<" from "<<bc->getSenderAddress()<<endl;
            if(sendBeacon != NULL){
                if (sendBeacon->isScheduled())
                {
                    cancelEvent(sendBeacon);
                }

                TraCIDemo11pMessage* rsuBeacon = new TraCIDemo11pMessage();

                char *ret = mergeContent(bc->getSenderAddress());
                rsuBeacon->setDemoData(ret);
                rsuBeacon->setSenderAddress(myId);
                BaseFrame1609_4* WSM = new BaseFrame1609_4();
                WSM->encapsulate(rsuBeacon);
                populateWSM(WSM);
                send(WSM,lowerLayerOut);
            }
        }
        else{
            if(bc->getSenderAddress() == Constant::WANTED_ID){
                if(traci == NULL){
                    if(Constant::activation != NULL)
                        traci = Constant::activation->getCommandInterface();
                }
                std::list<std::string> allPeople = traci->getPersonIds();
                //if(allPeople != NULL)
                EV<<"At:"<<simTime().dbl()<<" "<<allPeople.size()<<" peds. ";
                std::string lastId = allPeople.back();
                Coord lastPos = traci->getPersonPosition(lastId);
                EV<<"Last: "<<lastPos.x<<":"<<lastPos.y<<endl;
                //}
                //else
                //    EV<<"NULLL"<<endl;

            }
        }
    }
}

void HospitalControlApp::onWSA(DemoServiceAdvertisment* wsa)
{
    // Your application has received a service advertisement from another car or RSU
    // code for handling the message goes here, see TraciDemo11p.cc for examples
}

void HospitalControlApp::handleSelfMsg(cMessage* msg)
{
    TraCIDemoRSU11p::handleSelfMsg(msg);
}

void HospitalControlApp::handlePositionUpdate(cObject* obj)
{
    TraCIDemoRSU11p::handlePositionUpdate(obj);
    // the vehicle has moved. Code that reacts to new positions goes here.
    // member variables such as currentPosition and currentSpeed are updated in the parent class

}
/*std::string HospitalControlApp::getIdOfGLane(std::string str){
    std::string id = "";
    id = id + str.at(0) + str.at(1);

    for(int i = 2; i < str.length() - 1; i++){
        id = id + str.at(i);
        if(str.at(i + 1) == ' '){
            break;
        }
    }
    return id;
}*/
//int HospitalControlApp::getX2(int x){
    //return x*x;
//}
