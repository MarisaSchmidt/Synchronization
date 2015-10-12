//
//Marisa Schmidt
//March 24, 2015
//


#ifndef THREAD_H
#define THREAD_H
#include <pthread.h>

class thread {
public:
    thread(void * (*) (void *) = NULL);
    ~thread();
    pthread_t self();
    void wait();
private:
    pthread_t tid;
    pthread_attr_t attr;
    void * (*func) (void *);
    static void * run(void *);
};

thread::thread(void * (*_func) (void*)): tid(0){
    pthread_attr_init(&attr);
    if (_func) {
        func = _func;
        pthread_create(&tid, &attr, run, this);
    };
};

thread::~thread(){};

pthread_t thread::self(){
    return (tid);
};

void thread::wait(){
    pthread_join(tid, NULL);
};

void * thread::run(void * self){
    ((thread *) self)->func(NULL);
    return (NULL);
};

#endif
