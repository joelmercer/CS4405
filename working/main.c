#include "globalvars.h"

int main(int abort) {
int f = EMPTY;
    
    if(abort != 0) { 
        
    OS_Init(); 
    OS_InitSem(0, 1); //Creats OS's semaphore 0 with value 1
    OS_InitFiFo(); 
        
    OS_Create(void (*f)(void), int arg, unsigned int level, unsigned int n)
        
    OS_Start(); //Never returns
        
    }
    
    return 0;
}
