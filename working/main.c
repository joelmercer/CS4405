#include "globalvars.h"

//Helps declare globals for all c files
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
int stackheap[2][16];
int ossp;
int oshp;

//For test program
void test(); 
void test2(); 
int extern FIFO1;

int main() {

    OS_Init(); 
	
    //Fifo test to show functionality
    int FIFO1 = OS_InitFiFo();
	
	int FIFOData = 0x55555555;
	
	OS_Write(FIFO1, FIFOData);

    //init a semaphore for our test program
    OS_InitSem(0, 1); //Creates a semaphore 0 with value 1
    
    //Adding a process format OS_Create(&Function, ARG, Level, n)
	OS_Create(&test, 15, 2, 0);
	OS_Create(&test2, 20, 2, 0);
    
    OS_Start(); //Never returns unless error
    
    return 0;
}
