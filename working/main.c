#include "globalvars.h"
int abort = 0;
volatile int *timeq = (int*)0x10002000; //interval timer base address

int main() {

    
  if(abort != 1) { //abort is a global var set to 1 *************
        
    OS_Init(); 
    OS_InitSem(0, 1); //Creats OS's semaphore 0 with value 1
    OS_InitFiFo(); 

    OS_Create(void (*f)(void), int arg, unsigned int level, unsigned int n)
    OS_Interrupt_Init();       
    OS_Start(); //Never returns
        
   }
    
    return 0;
}
