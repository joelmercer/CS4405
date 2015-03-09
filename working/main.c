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
//int stackheap[2][16];
int ossp;
int oshp;
int fifocounter;
int once;
int stackheap[2][16] = { 
    
    {0x005FFC00, 0x005FFA00, 0x005FF800, 0x005FF600, 0x005FF400, 0x005FF200, 0x005FF000, 0x005FEE00, 0x005FEC00, 0x005FEA00, 0x005FE800, 0x005FE600, 0x005FE400, 0x005FE200, 0x005FE100, 0x005FDE00}, 
    
    {0x005FFA00, 0x005FF800, 0x005FF600, 0x005FF400, 0x005FF200, 0x005FF000, 0x005FEE00, 0x005FEC00, 0x005FEA00, 0x005FE800, 0x005FE600, 0x005FE400, 0x005FE200, 0x005FE100, 0x005FDE00, 0x005FDC00} 
    
};


//For test program
void test(); 
void test2(); 
int extern FIFO1;

int main() {


printf("Done Clear \n");

//printf("sp: %x \n", stackheap[0][0]);	

    OS_Init(); 
	int this = 0;
	int this2 = 0;
	int this3 = 0;
	int this4 = 0;
	BOOL tryfree;
	
	OS_Create(&test, 15, 2, 0);
	
	printf("here\n");
	this = OS_Malloc(4);
	
	printf("\nThis 1: 0x00%x \n", this);
	
	this2 = OS_Malloc(8);
	
	
	printf("\nThis 2: 0x00%x \n", this2);
	
	this3 = OS_Malloc(16);
	
	
	printf("\nThis 3: 0x00%x \n", this3);
	
	this4 = OS_Malloc(2);
	printf("\nThis 4: 0x00%x \n", this4);
	
	tryfree = OS_Free(this2);
	
	printf("\nFree: %d \n", tryfree);
	
	this2 = OS_Malloc(4);
	
	printf("\nThis 2: 0x00%x \n", this2);
	/*
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
    */
    return 0;
}
