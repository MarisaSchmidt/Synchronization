//
//Marisa Schmidt
//March 24, 2015
//



//Mutex/Conditional Variable scheme
#ifndef MUTEX_COND_SCHEME
#define MUTEX_COND_SCHEME
#include "Condvar.h"

void * pMultiple (void *); //producer function
void * cMultiple (void *); //consumer function
Mutexcl theMutex; //one mutex to protect one buffer
CondVar pCondition(&theMutex); //signal to consumer
CondVar cCondition(&theMutex); //signal to producer




                            /* FOR MUTEX / COND VAR SCHEME */
/*-----------------------------------------------------------------------------------------*/


void * pMultiple (void * voidId) {
    int me = 0;
    thread * extraConsumers[5];
    while (iGlobal < stop){
        theMutex.lock();
        while(buf.full()){
            //wait for a not full signal (coming from consumer once something has been removed from the buffer)
            
            /* !!!  EXTRA CREDIT (2) !!! */
            //more consumers need to be created when buffer is max'd
            for (int i=0; i < 5; i++) {
                extraConsumers[i] = new thread(cMultiple);
            }
            cCondition.wait(); //wait for consumer signal
        }; //end while
        buf.push(getTask());
        print(me);
        iGlobal++;
        //since something has been added to the buffer, send a not empty signal (coming from producer)
        pCondition.signal();
        theMutex.unlock();
    }
    
    //for extra credit
    for (int i=0; i < 5; i++) {
        delete extraConsumers[i];
    }
    return(NULL);
};

void * cMultiple (void * voidId) {
    int me = 1;
    while (iGlobal < stop){
        theMutex.lock();
        while(buf.empty()){
            //wait for a not empty signal (coming from producer once something has been added to the buffer)
            pCondition.wait();
        };
        buf.pop();
        print(me);
        iGlobal++;
        //since something has been removed from the buffer, send a not full signal (coming from consumer)
        cCondition.signal();
        theMutex.unlock();
    }
    return(NULL);
};

#endif
