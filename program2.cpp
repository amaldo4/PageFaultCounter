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
#include <vector>



using namespace std;
const int TOTAL = 100;
//const int TOTAL = 21;

bool hitMiss(int, int[], int);
int FIFO(int[], int);
int LRU(int[], int);
bool OPTsearch(int, vector<int>&);
int OPTpredict(int[], vector<int>& fr, int);
int OPT(int[], int);

int main(){
    int refString[TOTAL];
    //int testString[] = {1,2,3,1,6,5,6,3,4,6,8,7,1,0,5,4,6,2,3,0,1};
    int j = 0;
    int numFrames = 0;
    int FIFOCount = 0;
    int LRUCount = 0;
    int OPTCount = 0;

    srand(time(NULL));
    for(int i = 0; i < TOTAL; i++){
        j = rand()%50;
        refString[i] = j;
    }

    for(int i = 1; i < 31; i++){
        numFrames = i;

        cout << "Number of frames being used is: " << numFrames << endl;
        FIFOCount = FIFO(refString, numFrames);
        //FIFOCount = FIFOFaults(testString, numFrames);
        cout << "Number of FIFO Faults: " << FIFOCount << endl;
        LRUCount = LRU(refString, numFrames);
        //LRUCount = LRU(testString, numFrames);
        cout <<"Number of LRU Faults: " << LRUCount << endl;
        OPTCount = OPT(refString, numFrames);
        //OPTCount = OPT(testString, numFrames);
        cout <<"Number of OPT Faults: " << OPTCount << endl;
        cout << endl;
        cout << endl;
    }
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

int FIFO(int refString[], int numFrames){
    bool found;
    int frameArray[numFrames];
    int lookingFor = 0;
    int front = 0;
    int rear = -1;
    int faults = 0;
    

    for(int i = 0; i < TOTAL; i++){
        lookingFor = refString[i];
        //use hitmiss to see if value is already in frames
        found = hitMiss(lookingFor, frameArray, numFrames);
        if(found == true){
        }

        else{
            //not found so add to faults and eject first in
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
    int frameCount[numFrames];

    //set all values to -1
    for(int i = 0; i < numFrames; i++){
        frameArray[i] = -1;
        frameCount[i] = 0;
    }

    int test = 0;
    while(test < TOTAL){
        int j = 0;
        int flag = 0;
        while(j < numFrames){
            if(refString[test] == frameArray[j]){
                flag = 1;
                frameCount[j] = test + 1;
            }
            j++;
        }
        j = 0;
        if(flag == 0){
            int min = 0;
            int k = 0;
            while(k < (numFrames - 1)){
                if(frameCount[min] > frameCount[k+1])
                    min= k + 1;
                    k++;
                
            }
                frameArray[min] = refString[test];
                frameCount[min] = test+1;
                faults++;
                while(j<numFrames){
                    j++;
                }
            }
            test++;
        }
        return faults;
    }


bool OPTsearch(int value, vector<int>& frames)
{
    //function will search the created vector for the value
    //returns true if it is in a frame, false if not
    for (int i = 0; i < frames.size(); i++)
        if (frames[i] == value)
            return true;
    return false;
}

int OPTpredict(int refString[], vector<int>& frames, int index)
{
    // Store the index of pages which are going
    // to be used recently in future
    int res = -1, farthest = index;
    for (int i = 0; i < frames.size(); i++) {
        int j;
        for (j = index; j < TOTAL; j++) {
            if (frames[i] == refString[j]) {
                if (j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
  
        // If a page is never referenced in future,
        // return it.
        if (j == TOTAL)
            return i;
    }
  
    // If all of the frames were not in future,
    // return any of them, we return 0. Otherwise
    // we return res.
    return (res == -1) ? 0 : res;
}

int OPT(int refString[], int numFrames)
{
    vector<int> frames;
  
    // Traverse through page reference array
    // and check for miss and hit.
    int hit = 0;
    for (int i = 0; i < TOTAL; i++) {
  
        // Page found in a frame : HIT
        if (OPTsearch(refString[i], frames)) {
            hit++;
            continue;
        }
        // If there is space available in frames.
        if (frames.size() < numFrames)
            frames.push_back(refString[i]);
  
        // Find the page to be replaced.
        else {
            int j = OPTpredict(refString, frames, i + 1);
            frames[j] = refString[i];
        }
    }
    int faults = TOTAL - hit;
    return faults;
}
