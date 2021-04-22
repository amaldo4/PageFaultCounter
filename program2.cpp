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
int FIFOFaults(int[], int);

int main(){
    int refString[100];
    int j = 0;
    srand(time(NULL));

    for(int i = 0; i < 100; i++){
        //refString += to_string(i);
        j = rand()%50;
        cout << "J value is: " << j << endl;
        refString[i] = j;
    }

    // test to make sure thre were actually values in the array.
    /*for(int i = 0; i < 100; i++)
    {
        cout << refString[i] << " ";
    }*/
    



}

int FIFOFaults(int refString[], int frames){
    
}
