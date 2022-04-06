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

#include "Car001.h"

using namespace veins;
Define_Module(veins::Car001);

/*Car001::Car001() {
    EV <<"creating car node\n";
}

Car001::~Car001() {
    EV <<"destroying car node\n";
}*/

void Car001::initialize(int stage)
{
    EV <<__LINE__<<"\n";
}

void Car001::handlePositionUpdate(cObject* obj)
{
    DemoBaseApplLayer::handlePositionUpdate(obj);
}

void Car001::onWSA(DemoServiceAdvertisment* wsa)
{
    EV <<__LINE__<<"\n"<<endl;
}

void Car001::onWSM(BaseFrame1609_4* frame)
{
    EV <<__LINE__<<"\n"<<endl;
}

void Car001::handleSelfMsg(cMessage* msg)
{
    EV <<__LINE__<<"\n"<<endl;
}
