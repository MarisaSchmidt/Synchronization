//
//Marisa Schmidt
//March 24, 2015
//



//Peterson's scheme
#ifndef PETERSON_SCHEME
#define PETERSON_SCHEME

const int MAX = 2;
int turn = 0;
bool interested[MAX] = {false, false};
void * pSingle (void *); //producer function
void * cSingle (void *); //consumer function
int getTime(int);
void enter (int);
void leave (int);


                                /* FOR PETERSON'S SCHEME */
/*-----------------------------------------------------------------------------------------*/


void * pSingle (void * voidId) {
    int me = 0;
    while (iGlobal < stop) {
        while(buf.full()) { //can make it sleep here
            sleep(getTime(cTime));
        };
        enter(me);
        //start critical region
        buf.push(getTask());
        print(me);
        iGlobal++;
        //end critical region
        leave(me);
    }
    return(NULL);
};

void * cSingle (void * voidId) {
    int me = 1;
    while (iGlobal < stop) {
        while(buf.empty()) { //can make it sleep here 
            sleep(getTime(pTime));
        }
        enter(me);
        buf.pop();
        print(me);
        iGlobal++;
        leave(me);
    }
    return(NULL);
};

void enter (int me) {
    int you = 1-me;
    interested[me] = true;
    turn = me;
    while (turn == me && interested[you]);
};

void leave (int me) {
    interested[me] = false;
};

int getTime (int avgTime) { //return time
    return (rand () % ((2*avgTime)+1));
};
#endif
