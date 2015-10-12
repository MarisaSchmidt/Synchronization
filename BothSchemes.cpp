//
//Marisa Schmidt
//March 24, 2015
//


#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <iomanip>
#include "unistd.h"
#include "Buffer.h"
#include "threads.h"
using namespace std;


/////VARIABLES AND FUNCTIONS//////
//Both schemes
int stop = 20; //how many times producer and consumer will perform
circle buf;
void print(int);
int taskNum = 1;
string getTask();
int pNum = 0; //number of producers
int cNum = 0; //number of consumers
int pTime = 0; //time for producer
int cTime = 0; //time for consumer 
int iGlobal = 0; //shared iterator, keep track of stop (how many times performed)


#include "peterson.h"
#include "mutexScheme.h"



///////////////////////////////////////////MAIN///////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////


int main (int argc, char * argv[]) {
    if (argc > 1) {
        stop = atoi(argv[1]);
    }

    //getting proper user input for pNum/cNum (user must enter number >= 1) and pTime/cTime (user must enter number >= 0)
    bool input = true;
    cout << endl;

    
                            /* STEP 1: CHOOSE # OF THREADS */
    /*---------------------------------------------------------------------------------*/
    do {
        input = true;
        cout << "Enter number of producers: ";
        cin >> pNum;
        if (pNum < 1) {
            input = false;
            cout << "Incorrect input! Must be at least 1 producer." << endl;
        }
    } while (input == false);
    do {
        input = true;
        cout << "Enter number of consumers: ";
        cin >> cNum;

        if (cNum < 1) {
            input = false;
            cout << "Incorrect input! Must be at least 1 consumer." << endl;
        }
    } while(input==false);


                    /* STEP 2: IF 2 THREADS ----> CHECK TO SEE IF PETERSON OR MUTEX? */
    /*---------------------------------------------------------------------------------*/
    bool peterson = false; //assume multiple threads
    if ((pNum + cNum) == 2){
        char scheme;
        do {
            input = true;
            cout << "Enter preferred scheme (p for Peterson, m for Mutex): ";
            cin >> scheme;
            if (scheme=='p' || scheme=='P'){
                peterson = true;
            }
            else if (scheme=='m' || scheme=='M'){
                peterson = false;
            }
            else {
                input = false;
                cout << "Incorrect input! Please enter either p or m." << endl;
            }
        } while (input==false);
    }

    
                    /* STEP 3: IF PETERSON ----> CHOOSE TIME TO COMPLETE */
     /*---------------------------------------------------------------------------------*/
    if (peterson==true) {
        do {
            input = true;
            cout << "Enter average time to produce: ";
            cin >> pTime;
            if (pTime < 0) {
                input = false;
                cout << "Incorrect input! Time must be non-negative." << endl;
            }
        } while(input == false);
        do {
            input = true;
            cout << "Enter average time to consume: ";
            cin >> cTime;
            if (cTime < 0) {
                input = false;
                cout << "Incorrect input! Time must be non-negative." << endl;
            }
        } while (input == false);
    }
    
    
                                /* PETERSON'S SCHEME */
    /*---------------------------------------------------------------------------------*/
    if (peterson==true){
        thread producer(pSingle);
        thread consumer(cSingle);
        producer.wait();
        consumer.wait();
    } //end if statement
   else {
                                /* MUTEX / CONDITIONAL VAR */
    /*---------------------------------------------------------------------------------*/



    /* DISPATCH MULTIPLE THREADS */

    thread * producer[pNum]; //array of producer threads
    thread * consumer[cNum]; //array of consumer threads
    for (int i=0; i<pNum; i++) {
        producer[i] = new thread(pMultiple);
    }
    for (int i=0; i<cNum; i++) {
        consumer[i] = new thread(cMultiple);
    }
    


    /* MAIN WAITS FOR PRODUCERS/CONSUMERS TO FINISH */
    if (pNum > cNum) { 
    //if more producers than consumers, wait for last consumer
        consumer[cNum-1]->wait(); 
    }
    else { 
    ///////ELSE: less or equal producers than consumers, wait for last producer
        producer[pNum-1]->wait();
    }



    /* MAIN RETURNS HERE AFTER WAITING */
    /* FREE DYNAMICALLY ALLOCATED MEMORY */
    for (int i=0; i<pNum; i++) {
        delete producer[i];
    }
    for (int i=0; i<cNum; i++) {
        delete consumer[i];
    }//end for loop
   }//end else statement
    

//END MAIN!!! 
};






///////////////////////////////////FUNCTION DEFINITIONS///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////


                                /* FOR BOTH SCHEMES */
/*------------------------------------------------------------------------------------------*/

void print(int me) { //display
    if (me==0) {
        // cout << "[producer] ";
        cout << "P ";
    }
    else if (me==1) {
        // cout << "[consumer] ";
        cout << "C ";
    }
    // cout << "| count: " << buf.getCount() << " ";
    cout << left << setw(3) << setfill(' ') << buf.getCount() << " ";
    // cout << "| contents: ";
    buf.display();
    cout << endl;
}

string getTask() { //return task number
    ostringstream ss;
    ss << "R" << taskNum;
    taskNum++;
    return (ss.str());
};
