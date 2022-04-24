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

#ifndef VEINS_INET_CONSTANT_H_
#define VEINS_INET_CONSTANT_H_

#include <stdlib.h>
#include <string.h>
#include <string>
#include <stdio.h>
#include "veins/modules/mobility/traci/TraCIMobility.h"
//using veins::TraCIMobility;
using namespace veins;

class Constant {
public:
    static constexpr const char* FIRST = "First vehicle";
    static constexpr const char* RSU_IDENTIFY = "RSU";
    static constexpr const long WANTED_ID = 52;
    Constant();
    virtual ~Constant();
    static TraCIMobility* activation;
};

static char* mergeContent(long Id){
    char *cstr = new char[strlen(Constant::RSU_IDENTIFY) + 1];
    strcpy(cstr, Constant::RSU_IDENTIFY);
    std::string str = std::to_string(Id);
    char *new_str = new char[str.length() + 1];
    strcpy(new_str, str.c_str());
    char *ret = new char[strlen(Constant::RSU_IDENTIFY) + strlen(new_str) + 1];
    strcpy(ret, cstr);
    strcat(ret, new_str);
    return ret;
}

#endif /* VEINS_INET_CONSTANT_H_ */
