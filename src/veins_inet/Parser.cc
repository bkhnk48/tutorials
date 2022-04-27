/*
 * Parser.cpp
 *
 *  Created on: Apr 27, 2022
 *      Author: agile
 */

#include "Parser.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <filesystem>
#include <unistd.h>
#include <dirent.h>
//using std::filesystem::current_path;

Parser::Parser() {
    // TODO Auto-generated constructor stub

}

Parser::~Parser() {
    // TODO Auto-generated destructor stub
}

const char * Parser::getId(std::string str){
    std::string id = "";
    id = id + str.at(0) + str.at(1);

    for(int i = 2; i < str.length() - 1; i++){
        id = id + str.at(i);
        if(str.at(i + 1) == ' '){
            break;
        }
    }
    return id.c_str();
}

int Parser::getIndex(const char* str){
    int offset = 0;
    int index = 0;

    if(str[0] == '-'){
        index++; //skip '-'
        offset = 1;
    }
    index++; //skip 'E'
    char num[4];
    num[3] = '\0';
    int j = index;
    for(j = index; j < index + 3; j++){
        num[j - index] = str[j];
        if(str[j+1] == '_' && ((j - index + 1) < 3))
        {
            num[j - index + 1] = '\0';
            break;
        }
    }
    int x = atoi(num);
    x = (offset == 1) ? -x : x;
    int y = (2*abs(x) + offset);
    return y;
}

int Parser::adjust(int key){
    int newKey = key;

    #pragma region declare anchors
    int anchor0 = 143;
    int anchor1 = 152;
    //144, 145, 146, 147, 148, 149, 150, 151,
    int anchor2 = 173;
    int anchor3 = 180;
    //174, 175, 176, 177, 178, 179,
    int anchor4 = 375;
    int anchor5 = 378;
    //376, 377,
    int anchor6 = 397;
    int anchor7 = 400;
    //398, 399,
    int anchor8 = 831;
    int anchor9 = 834;
    //832, 833,
    int anchor10 = 891;
    int anchor11 = 902;
    //892, 893, 894, 895, 896, 897, 898, 899, 900, 901,
    int anchor12 = 933;
    int anchor13 = 948;
    //934, 935, 936, 937, 938, 939, 940, 941, 942, 943, 944, 945, 946, 947
    #pragma endregion
    if(key <= anchor0){
        return key;
    }
    else if(key >= anchor1 && key <= anchor2){
        newKey = key - (anchor1 - anchor0 - 1);
    }
    else if(key >= anchor3 && key <= anchor4){
        newKey = key - (anchor3 - anchor2 - 1) - (anchor1 - anchor0 - 1);
    }
    else if(key >= anchor5 && key <= anchor6){
        newKey = key - (anchor5 - anchor4 - 1)
                     - (anchor3 - anchor2 - 1)
                     - (anchor1 - anchor0 - 1);
    }
    else if(key >= anchor7 && key <= anchor8){
        newKey = key - (anchor7 - anchor6 - 1)
                     - (anchor5 - anchor4 - 1)
                     - (anchor3 - anchor2 - 1)
                     - (anchor1 - anchor0 - 1);
    }
    else if(key >= anchor9 && key <= anchor10){
        newKey = key - (anchor9 - anchor8 - 1)
                     - (anchor7 - anchor6 - 1)
                     - (anchor5 - anchor4 - 1)
                     - (anchor3 - anchor2 - 1)
                     - (anchor1 - anchor0 - 1);
    }
    else if(key >= anchor11 && key <= anchor12){
        newKey = key - (anchor11 - anchor10 - 1)
                     - (anchor9 - anchor8 - 1)
                     - (anchor7 - anchor6 - 1)
                     - (anchor5 - anchor4 - 1)
                     - (anchor3 - anchor2 - 1)
                     - (anchor1 - anchor0 - 1);
    }
    else if(key >= anchor13){
        newKey = key - (anchor13 - anchor12 - 1)
                     - (anchor11 - anchor10 - 1)
                     - (anchor9 - anchor8 - 1)
                     - (anchor7 - anchor6 - 1)
                     - (anchor5 - anchor4 - 1)
                     - (anchor3 - anchor2 - 1)
                     - (anchor1 - anchor0 - 1);
    }
    return newKey;
}


GLane* Parser::initAllLanes(int N){
    allLanes = (GLane *)malloc(N*sizeof(GLane));
    for(int i = 0; i < N; i++){
        GLane* t = new GLane();
        allLanes[i] = *t;
        allLanes[i].length = 0;
        allLanes[i].number = 0;
        allLanes[i].neighborsIds[0] = -1;
        allLanes[i].neighborsIds[1] = -1;
        allLanes[i].neighborsIds[2] = -1;
        allLanes[i].numNeighbors = 0;
    }
    return allLanes;
}

std::vector<std::string> Parser::split(const std::string& str, const std::string& delim)
{
    std::vector<std::string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == std::string::npos) pos = str.length();
        std::string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}

int* Parser::getNeighbors(std::string content){
    std::string regex_str = " ";
    int count = 0;
    int NUM_NEIGHBOR = 3;
    int *arr = (int *)malloc(NUM_NEIGHBOR*sizeof(int));

    arr[0] = arr[1] = arr[2] = -1;
    auto tokens = split(content, regex_str);

    for (auto& item : tokens)
    {
        if(count >= 2){
            int x = getIndex(item.c_str());
            x = adjust(x);
            arr[count - 2] = x;
        }
        count++;
    }
    return arr;
}

double Parser::getLength(const char *content){
    int found = -1;//find the position of length edge
    for(int i = 0; i < strlen(content); i++){
        if(content[i] == '_'){
            found = i;
        }
        else if(found != -1 && content[i] == ' '){
            found = i;
            break;
        }
    }
    int NUM_LENGTH = 5;
    char num[NUM_LENGTH]; int index = 0;
    if(found != -1 && isdigit(content[found + 1])){//found the start of lane's length
        for(int i = found; i < strlen(content); i++){
            if(content[i] == '.' || isdigit(content[i]) && index < NUM_LENGTH)
            {
                num[index] = content[i];
                index++;
            }
        }
    }
    else{
        return 0.0;
    }
    num[NUM_LENGTH - 1] = '\0';
    char *eptr;
    double result = strtod(num, &eptr);
    return result;
}

int Parser::getSumFromZeroTo(int N){
    int sum = 0;
    for(int i = 0; i < N; i++)
    {
        sum += i;
    }
    return sum;
}

void Parser::updateLanes(GLane* allLanes, std::string tp, int *total){
    int i = getIndex(tp.c_str());

    i = adjust(i);
    *total += i;
    double length = getLength(tp.c_str());
    assert(length != 0);
    int *indexesOfNeighbors = getNeighbors(tp);
    allLanes[i].length = length;
    strcpy(allLanes[i].id, getId(tp));
    allLanes[i].number = ceil(allLanes[i].length/Constant::ZONE_LENGTH);

    allLanes[i].zones = (double *)malloc(allLanes[i].number*sizeof(double));

    allLanes[i].neighborsIds[0] = indexesOfNeighbors[0];
    allLanes[i].neighborsIds[1] = indexesOfNeighbors[1];
    allLanes[i].neighborsIds[2] = indexesOfNeighbors[2];
    if(indexesOfNeighbors[0] != -1) allLanes[i].numNeighbors++;
    if(indexesOfNeighbors[1] != -1) allLanes[i].numNeighbors++;
    if(indexesOfNeighbors[2] != -1) allLanes[i].numNeighbors++;
}

void Parser::readFile(){
    std::fstream newfile;
    int N;
    char cwd[256];

    newfile.open("input.txt", std::ios::in);
    if (newfile.is_open()){   //checking whether the file is open
        EV<<"FOUND"<<endl;
        std::string tp;
        getline(newfile, tp);
        N = atoi(tp.c_str());

        GLane *allLanes = initAllLanes(N);

        int sum = getSumFromZeroTo(N);

        int total = 0;

        while(getline(newfile, tp)){ //read data from file object and put it into string.
            updateLanes(allLanes, tp, &total);
        }
        assert(sum == total);
        //assertAllLanes(N, allLanes);

        newfile.close(); //close the file object.
    }
}
