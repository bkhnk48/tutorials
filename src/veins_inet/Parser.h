/*
 * Parser.h
 *
 *  Created on: Apr 27, 2022
 *      Author: agile
 */

#ifndef VEINS_INET_PARSER_H_
#define VEINS_INET_PARSER_H_
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <assert.h>
#include<ctype.h>
#include <regex>
#include "GLane.h"
#include "Constant.h"

class Parser {
public:
    Parser();
    virtual ~Parser();
    const char* getId(std::string str);
    int getIndex(const char* str);
    int adjust(int key);
    GLane *getAllLanes();
    void readFile();

private:
    GLane *allLanes;
    GLane *initAllLanes(int N);
    std::vector<std::string> split(const std::string& str, const std::string& delim);
    int *getNeighbors(std::string content);
    double getLength(const char *content);
    int getSumFromZeroTo(int N);
    void updateLanes(GLane* allLanes, std::string tp, int *total);
};

#endif /* VEINS_INET_PARSER_H_ */
