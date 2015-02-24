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

//For test program
void test(); 
void test2(); 


int main() {
	
    OS_Init(); 
    OS_InitSem(0, 1); //Creates a semaphore 0 with value 1
	
    int FIFO1 = OS_InitFiFo();
	int FIFO2 = OS_InitFiFo();
	
	int FIFOData1 = 0;
	int FIFOData2 = 0;	

	OS_Write(FIFO1, 1);
	OS_Write(FIFO2, 2);
	
	OS_Read(FIFO1, &FIFOData1);
	OS_Read(FIFO2, &FIFOData2);

	OS_Create(&test, 15, 2, 0);
	OS_Create(&test2, 20, 2, 0);
    
    OS_Start(); //Never returns unless error
    
    return 0;
}

