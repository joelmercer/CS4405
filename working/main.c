#include "globalvars.h"

int main() {

    
  if(abort != 1) { //abort is a global var set to 1 *************
        
    OS_Init(); 
    OS_InitSem(0, 1); //Creats OS's semaphore 0 with value 1
    OS_InitFiFo(); 

    //OS_Create(void (*f)(void), int arg, unsigned int level, unsigned int n)
    
    NIOS2_WRITE_STATUS(1);    
    OS_Start(); //Never returns
        
   }
    
    return 0;
}
