#include "globalvars.h"

#include "contextswitch.c"
#include "init.c"
#include "processman.c"
#include "semaphores.c"
#include "semaphores.c"
#include "fifo.c"
#include "ihandler.c"

//Init Global Vars
int crash = 0;
volatile int *timebase = (int*)0x10002000; //interval timer base address
int timeq = 0x260000; // 1/(50 MHz) × (0x260000) = ~50 msec
int pppcounter = 0;
int sporadic[MAXPROCESS] = EMPTY;
int sporadiccounter = 0;

int main() {

    
  if(crash != 1) { //abort is a global var set to 1 *************
        
    OS_Init(); 
    OS_InitSem(0, 1); //Creats OS's semaphore 0 with value 1
    OS_InitFiFo(); 

    //OS_Create(void (*f)(void), int arg, unsigned int level, unsigned int n)
    
    NIOS2_WRITE_STATUS(1);    
    OS_Start(); //Never returns
        
   }
    
    return 0;
}
