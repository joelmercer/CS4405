#include "globalvars.h"


//Init Global Vars
//
//Future stuff
//volatile int *timebase = (int*)0x10002000; //interval timer base address
//int timeq = 0x260000; // 1/(50 MHz) × (0x260000) = ~50 msec
//int pppcounter = 0;
//

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


void dontblink();
void blink();
void blink2();

int main() {
	
        int *ptr;
    OS_Init(); 
    OS_InitSem(0, 1); //Creats OS's semaphore 0 with value 1
    OS_InitFiFo(); 
OS_Wait(0);
OS_Write(f, 9);
OS_Read(f, &ptr);

crash=0;

printf("MAIN 1: %d\n", crash);
OS_Create(&blink, 5, 2, 0);
printf("MAIN 2: %d\n", crash);
OS_Create(&blink2, 5, 2, 0);
    
    NIOS2_WRITE_STATUS(1);    // enable interrupts
    OS_Start(); //Never returns
    
    return 0;
}
