#include "os.h"

PID  OS_Create(void (*f)(void), int arg, unsigned int level, unsigned int n) {

}

void OS_Terminate(void) {
terminate = 1;
    //do last
}

void OS_Yield(void) {
//interupt******* 
//context switch *********
    //Not needed for D1
}

int  OS_GetParam(void) {

}
