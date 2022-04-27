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

#ifndef VEINS_INET_GLANE_H_
#define VEINS_INET_GLANE_H_

class GLane {
public:
    GLane();
    virtual ~GLane();
    double length;
    int number;//# of zones
    double *zones;
    char id[20];//id of lane itself
    //char edge_id[20]; //id of edge container
    int neighborsIds[3];
    int numNeighbors ;
    //GLane operator= (const GLane &gl );
};

#endif /* VEINS_INET_GLANE_H_ */
