#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <assert.h>
#include "HashAPI.cpp"
#include<ctype.h>
#include <regex>
using namespace std;

vector<string> split(const string& str, const string& delim)
{
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}

int *getNeighbors(std::string content){
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
            arr[count - 2] = x;
        }
        count++;
    }
    return arr;
}
double getLength(const char *content){
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

int readFile(){
    fstream newfile;
    int N;
    
    newfile.open("input.txt", ios::in);
    if (newfile.is_open()){   //checking whether the file is open
        string tp;
        getline(newfile, tp);
        N = atoi(tp.c_str());
        
        int arr[N] = {-1};
        for(int i = 0; i < N; i++){
            arr[i] = -1;
        }
        
        int sum = 0;
        for(int i = 0; i < N; i++)
        {
            sum += i;
        }
        
        int total = 0;
        int index = 0;
        while(getline(newfile, tp)){ //read data from file object and put it into string.
            int y = getIndex(tp.c_str());
            y = adjust(y);
            total += y;
            //arr[y] = 1;
            double length = getLength(tp.c_str());              
            assert(length != 0);
            int *indexesOfNeighbors = getNeighbors(tp);
            cout<<tp<<". Neighbors: "<<indexesOfNeighbors[0]
                    <<" "<<indexesOfNeighbors[1]<<" "
                    <<indexesOfNeighbors[2]<<endl;
            
        }
        assert(sum == total);
        
        newfile.close(); //close the file object.
    }
    return 0;
}

int main(){
    readFile();
    cout<<"Read completely"<<endl;
    return 0;
}