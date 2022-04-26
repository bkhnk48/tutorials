#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <limits.h>
using namespace std;

int readFile(){
    fstream newfile;
    int N;
    int absent = 0;
    newfile.open("input.txt", ios::in);
    if (newfile.is_open()){   //checking whether the file is open
        string tp;
        getline(newfile, tp);
        N = atoi(tp.c_str());
        cout<<"N = "<<N<<endl;

        int offset = 0;
        int index = 0;
        int count = 0;
        int arr[N] = {-1};
        for(int i = 0; i < N; i++){
            arr[i] = -1;
        }
        
        int sum = 0;
        for(int i = 0; i < N; i++)
        {
            sum += i;
        }
        cout<<"Sum is "<<sum<<endl;
        int total = 0;
        while(getline(newfile, tp)){ //read data from file object and put it into string.
            //cout<<"\nnew line = "<<tp<<" ";
            if(count == 334)
            {
                cout<<"DEBUG HERRE"<<endl;
            }
            int y = getIndex(tp.c_str());
            y = adjust(y);
            total += y;
            //cout<<" y = "<<y;
            //if(count < 10)
            
            if(y < 0 || y > N){
                cout<<"as str = "<<tp<<" and count="<<count<<" the y ="<<y<<endl;
                //cout<<"Out of range"<<endl;
            }
            else{
                arr[y] = 1;
            }
            count++;
        }
        if(sum == total)
            cout<<"Equals 0"<<endl;
        else
            cout<<"Sum = "<<sum<<" but total = "<<total<<endl;
        newfile.close(); //close the file object.
    }
    return 0;
}

int main(){
    readFile();
    return 0;
}
