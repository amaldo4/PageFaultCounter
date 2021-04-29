/*CS 4328 Program 1
Austin Maldonado
3/31/2021*/



#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <stdint.h>
#include <iostream>
#include <string>
#include <ctime>
#include <time.h>



using namespace std;
const int TOTAL = 100;

bool hitMiss(int, int[], int);
int FIFOFaults(int[], int);
int LRU(int[], int);

int main(){
    int refString[TOTAL];
    int testString[] = {1,2,3,1,6,5,6,3,4,6,8,7,1,0,5,4,6,2,3,0,1};
    int j = 0;
    int numFrames = 0;
    int FIFOCount = 0;
    int LRUCount = 0;

    cout << "How many frames: ";
    cin >> numFrames;

    srand(time(NULL));
    for(int i = 0; i < TOTAL; i++){
        j = rand()%50;
        refString[i] = j;
    }

    FIFOCount = FIFOFaults(refString, numFrames);
    //FIFOCount = FIFOFaults(testString, numFrames);
    cout << "Number of FIFO Faults: " << FIFOCount << endl;
    LRUCount = LRU(refString, numFrames);
    //LRUCount = LRU(testString, numFrames);
    cout <<"Number of LRU Faults: " << LRUCount << endl;
}

bool hitMiss(int lookingFor, int frameArray[], int numFrames){
    bool test = false;
    for(int i = 0; i < numFrames; i++){
        if(frameArray[i] == lookingFor){
            test = true;
        }
    }
    return test;
}

int FIFOFaults(int refString[], int numFrames){
    bool found;
    int frameArray[numFrames];
    int lookingFor = 0;
    int front = 0;
    int rear = -1;
    int faults = 0;
    

    for(int i = 0; i < TOTAL; i++){
        lookingFor = refString[i];
        //cout << "looking for: " << lookingFor << endl;
        found = hitMiss(lookingFor, frameArray, numFrames);
        if(found == true){
        }

        else{
            //cout << "didnt find in cache" << endl;
            faults++;
            front = (front + 1) % numFrames;
            rear = (rear + 1) % numFrames;
            frameArray[front] = refString[i];
        }
    }
    return faults;
}

int LRU(int refString[], int numFrames){
    int faults = 0;
    int frameArray[numFrames];
    int fcount[numFrames];

    for(int i = 0; i < numFrames; i++){
        frameArray[i] = -1;
        fcount[i] = 0;
    }

    int test = 0;
    while(test < TOTAL){
        int j = 0;
        int flag = 0;
        while(j < numFrames){
            if(refString[test] == frameArray[j]){
                flag = 1;
                fcount[j] = test + 1;
            }
            j++;
        }
        j = 0;
        if(flag == 0){
            int min = 0;
            int k = 0;
            while(k < (numFrames - 1)){
                if(fcount[min] > fcount[k+1])
                    min= k + 1;
                    k++;
                
            }
                frameArray[min] = refString[test];
                fcount[min] = test+1;
                faults++;
                while(j<numFrames){
                    j++;
                }
            }
            test++;
        }
        return faults;
    }
