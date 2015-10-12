//
//Marisa Schmidt
//March 24, 2015
//


#ifndef BUFFER_H
#define BUFFER_H
#include <string>
#include <iostream>
using namespace std;

class circle {
    
public:
    circle();
    bool push(string);
    bool pop();
    bool empty();
    bool full();
    void display();
    int  getCount();
private:
    static const int MAX = 10;
    int in;
    int out;
    int count;
    string array[MAX];
    
    /*implementing semaphores
     semaphore fillCount = 0; // items produced
     semaphore emptyCount = MAX; // remaining space
     */
    
};

void circle::display() {
    int i=0;
    if (!empty()){
        while (i<count) {
            cout << left << setw(4) << setfill(' ') << array[(out+i)%MAX] << " ";
            i++;
        }
    }
};

int circle::getCount() {
    return(count);
}

circle::circle(): in(0), out(0), count(0){
    for (int i=0; i<MAX; i++){
        array[i] = "";
    }
};

bool circle::push(string itemToPush){
    bool pushed = false;
    if (!full()){
        array[in] = itemToPush;
        count++;
        in = (in+1)%MAX;
        pushed = true;
    }
    return (pushed);
};

bool circle::pop(){
    bool popped = false;
    if (!empty()){
        count--;
        out = (out+1)%MAX;
        popped = true;
    }
    return (popped);
};

bool circle::full(){
    return (count==MAX);
};

bool circle::empty(){
    return (count==0);
};

#endif
