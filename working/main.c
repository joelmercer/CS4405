#include "globalvars.h"

//Helps declare globals for all c files
FIFO f;
process processarray[MAXPROCESS+1];
sem semarray[MAXSEM];
int fifopidarray[MAXFIFO];
node fifoarray[MAXFIFO][FIFOSIZE];
int sporadic[MAXPROCESS];
int sporadiccounter;
int terminate;
int crash;
int processcounter; 
int semcounter;
int workingpid;
//int stackheap[2][16];
int oshp;
int fifocounter;
int once;
volatile int * interval_timer_ptr = (int *) 0x10002000;
int PPPLen = 0;   //The User needs to define this before starting
int PPP[0];           
int PPPMax[0];       
int devicelen = 0; //The User needs to define this before starting
int device[0];
int devicemax[0];
int devicetimer;
int currentdevicetimer;
int startregs[32] = {0};
int savepid = 0;
int doesnothing = 0;
int unsigned stack[16] = {0x005FFC00, 0x005FFA00, 0x005FF800, 0x005FF600, 0x005FF400, 0x005FF200, 0x005FF000, 0x005FEE00, 0x005FEC00, 0x005FEA00, 0x005FE800, 0x005FE600, 0x005FE400, 0x005FE200, 0x005FE100, 0x005FDE00};
int unsigned heap = 0x005FFE00;


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
	OS_Create(&test, 5, 2, 0);
	OS_Create(&test2, 5, 2, 0);
	//OS_Create(&test2, 20, 2, 0);
	savepid = 16;
	workingpid = 16;
    OS_StartTimer(0xFFFF);
   processarray[workingpid].hp = heap;
		
	
	while(1) {}
		
    //OS_Start(); //Never returns unless error
    
    return 0;
}
