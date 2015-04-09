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
int oshp;
int fifocounter;
int once;
volatile int * interval_timer_ptr = (int *) 0x10002000;
int nextp = 0;
int nexts = 0;
int PPPLen = 0;   //The User needs to define this before starting
int slen = 0;
int PPP[8] = {1, -1, 1, -1, 1, -1, 1, -1};         								// User defined
int PPPMax[8] = {250000, 250000, 250000, 250000, 250000, 250000, 250000, 250000};       //User Defined
int devicelen = 0; 
int device[0];
int devicemax[0];
int devicetimer[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int unsigned currentdevicetimer;
int startregs[32] = {0};
int savepid = 0;
int doesnothing = 0;
int unsigned nextimer = 0;
int unsigned dtimermin = 4294967295;
int unsigned dtimermax = 0;
int unsigned dtimercount = 0;
int unsigned dtimer = 0;
int unsigned timecounter = 0;
int unsigned stack[16] = {0x005FFC00, 0x005FFA00, 0x005FF800, 0x005FF600, 0x005FF400, 0x005FF200, 0x005FF000, 0x005FEE00, 0x005FEC00, 0x005FEA00, 0x005FE800, 0x005FE600, 0x005FE400, 0x005FE200, 0x005FE100, 0x005FDE00};
int unsigned heap = 0x005FFE00;


//For test program
void test1(); 
void test2(); 
void test3(); 
void test4(); 
int extern FIFO1;
void deviceblink();
void ppprocess();

int main() {

    OS_Init(); 
	
	printf("PPP at the start: %d\n", PPP[1]);

    //Fifo test to show functionality
    int FIFO1 = OS_InitFiFo();
	
	int FIFOData = 0x3;
	
	OS_Write(FIFO1, FIFOData);

    //init a semaphore for our test program
    OS_InitSem(0, 1); //Creates a semaphore 0 with value 1
    
    //Adding a process format OS_Create(&Function, ARG, Level, n)
	OS_Create(&deviceblink, 0, 0, 10);
	OS_Create(&test2, 1, 1, 1);
	OS_Create(&test3, 5, 2, 0);
	OS_Create(&test4, 5, 2, 0);
	
	//OS_Create(&test2, 20, 2, 0);
	savepid = 16;
	workingpid = 16;
	processarray[workingpid].hp = heap;
    OS_StartTimer(0xFFFF);
	
		
	
	while(1) {}
		
    //OS_Start(); //Never returns unless error
    
    return 0;
}
