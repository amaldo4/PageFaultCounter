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
const int total = 100;

bool hitMiss(int, int[], int);
int FIFOFaults(int[], int);

int main(){
    int refString[total];
    //int testString[] = {1,2,3,1,6,5,6,3,4,6,8,7,1,0,5,4,6,2,3,0,1};
    int j = 0;
    int numFrames = 0;
    int FIFOCount = 0;

    cout << "How many frames: ";
    cin >> numFrames;


    srand(time(NULL));

    for(int i = 0; i < total; i++){
        j = rand()%50;
        refString[i] = j;
    }


    for(int i = 0; i < total; i++)
    {
        cout <<"Position " << i  <<": "<< refString[i] << endl;
    }
    cout << endl;
    cout << endl;

    FIFOCount = FIFOFaults(refString, numFrames);
    //FIFOCount = FIFOFaults(testString, numFrames);
    cout << "Number of FIFO Faults: " << FIFOCount << endl;
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
    

    for(int i = 0; i < total; i++){
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
