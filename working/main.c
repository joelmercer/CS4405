#include "globalvars.h"

FIFO f;
process processarray[MAXPROCESS];
sem semarray[MAXSEM];
int fifopidarray[MAXFIFO][MAXFIFO];
node fifoarray[MAXFIFO];
int sporadic[MAXPROCESS];
int sporadiccounter;
int terminate;
int crash;
int processcounter; 
int semcounter;
int workingpid;


int dontblink();
int blink();
int dontblink2();
int blink2();

int main() {
	
        int ptr;
    OS_Init(); 
    OS_InitSem(0, 1); //Creats OS's semaphore 0 with value 1
    OS_InitFiFo(); 
OS_Wait(0);
OS_Write(f, 9);
OS_Read(f, &ptr);

printf("MAIN 1: %d\n", ptr);

crash=0;

printf("MAIN 1: %d\n", crash);
OS_Create(&blink, 15, 2, 0);
printf("MAIN 2: %d\n", crash);
OS_Create(&blink2, 15, 2, 0);
    
    NIOS2_WRITE_STATUS(1);    // enable interrupts
    OS_Start(); //Never returns
    
    return 0;
}
