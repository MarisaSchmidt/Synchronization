#ifndef CONDITIONAL_VAR_H
#define CONDITIONAL_VAR_H
#include "Mutexcl.h"

class CondVar{
    
public:
    CondVar(Mutexcl *);
    ~CondVar();
    void signal();
    void wait();
    
private:
    pthread_cond_t condition;
    Mutexcl * theMutex;
    
};

CondVar::CondVar(Mutexcl * mutexPtr){
    theMutex = mutexPtr;
    pthread_cond_init(&condition, NULL);
};

CondVar::~CondVar(){
    pthread_cond_destroy(&condition);
};

void CondVar::signal(){
    pthread_cond_signal(&condition);
};

void CondVar::wait(){
    pthread_cond_wait(&condition, &(theMutex->pMutex));
};

#endif
