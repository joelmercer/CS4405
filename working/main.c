#include "globalvars.h"



//Init Global Vars
//
//Future stuff
//volatile int *timebase = (int*)0x10002000; //interval timer base address
//int timeq = 0x260000; // 1/(50 MHz) × (0x260000) = ~50 msec
//int pppcounter = 0;
//

int sporadic[MAXPROCESS];
int sporadiccounter;
int terminate;
int crash;
int processcounter; 
int terminate;
int crash;
int semcounter;
int fifopidarray[MAXFIFO][MAXFIFO];

int main() {
        
    OS_Init(); 
    OS_InitSem(0, 1); //Creats OS's semaphore 0 with value 1
    OS_InitFiFo(); 

    //OS_Create(void (*f)(void), int arg, unsigned int level, unsigned int n)
    
    NIOS2_WRITE_STATUS(1);    
    OS_Start(); //Never returns
    
    return 0;
}
