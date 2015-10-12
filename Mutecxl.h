#ifndef MUTEXCL_H
#define MUTEXCL_H
#include <pthread.h>
#include "Condvar.h"

class Mutexcl {

    friend class CondVar; //so that CondVar function pthread_cond_wait can access Mutexcl private data member pMutex

public:
    Mutexcl();
    ~Mutexcl();
    bool lock();
    bool unlock();

private:
    pthread_mutex_t pMutex;

};

Mutexcl::Mutexcl(){
    pthread_mutex_init(&pMutex, NULL);
};

Mutexcl::~Mutexcl(){
    pthread_mutex_destroy(&pMutex);
};

bool Mutexcl::lock(){
    bool locked = true;
    if (pthread_mutex_lock(&pMutex)==0){
        locked=false;
    }
    return(locked);
};

bool Mutexcl::unlock(){
    bool unlocked = true;
    if (pthread_mutex_unlock(&pMutex)==0){
        unlocked=false;
    }
    return(unlocked);
};

#endif
