#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <assert.h>
#include "HashAPI.cpp"

void assertAllLanes(int N, Lane *allLanes){
    for(int i = 0; i < N; i++){
        assert(allLanes[i].length > 0);
        size_t size = sizeof(allLanes[i].id) / sizeof(allLanes[i].id[0]);
        assert(size >= 4);
        if(i % 2 == 1)
            assert(allLanes[i].id[0] == '-');
        else{
            assert(allLanes[i].id[0] != '-');
        }
    }
}