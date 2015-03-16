#include "myos.h"
#include "memory.h"
#include "process.h"
//#include "context_switch.h"
#include <stdlib.h>


//===================================================
// 			Macro for resetting the board!
//===================================================
#define NIOS2_RESET_ADDR 0x00900800
#define NIOS2_RESET() \
	NIOS2_WRITE_STATUS(0);\
	NIOS2_WRITE_IENABLE(0);\
	((void (*) (void)) NIOS2_RESET_ADDR)()





//============================================
//			YOUR PROGRAM GOES HERE
//============================================



int processFunction(void)
{
	MEMORY *ptr = OS_Malloc(1);
	*ptr = 6;
	unsigned int x = *ptr;

	printf(" HO MAMA: %d", x);
	printf("\n DAD IS THAT YOU??????????");

	OS_Free(ptr);
	printf("\n FREEEEEEE: %d", *ptr);
	return 1;
}





//----------------------------------------------------------------
//						   OS FUNCTIONS
//----------------------------------------------------------------




void OS_Init()
{
	//Setup all the memory structs and zero out the heap
	OS_InitMemory();

	//Set all PCBs to available.
	int i;
    for(i = 0; i < MAXPROCESS; i++)
    	processStructArray[i].available = 1;




	//~~~~~~~~~~~~~~~~~
	//Process 1
	puts("Making first process");
	void (*foo)(void);
	foo = processFunction; //<--- Make your own function to simulate a test program.
	PID proc1 = OS_Create(foo, 2, SPORADIC, 0); //<-- enqueue your own process.



	//~~~~~~~~~~~~~~~~~
	//Process 2
	//YOUR
	//PROCESS
	//GOES
	//HERE
	//:D :D :D :D




	//------------------------------------------------
	// These are not relevant until we implement
	// more than just sporadic processes and do memory.
	//------------------------------------------------
	// TODO: initialize PPP[]
	// TODO: initialize PPPMax[]
	//OS_InitSem();
	//OS_InitFiFo();
}



void OS_Start()
{
	//SCHEDULING
	while(1)
	{
		//Pop a process
		puts("\n Set the head pointer.");
		process *currentProc = sporadicQueueHead;


		currentProc->process();
		puts("\n We returned from the context switch.");

		//Throw the process to the back of the list.
		process *temp = dequeueProcess(&sporadicQueueHead);
		enqueueProcess(&sporadicQueueHead, temp);
	}
}



void OS_Abort()
{
	//NIOS2_RESET();
}




/*
	This is what the Altera Monitor program loads+runs.
	This function is fundamental to making the OS run
*/
void main()
{
	OS_Init();

	OS_Start();
}





//----------------------------------------------------------------
//						  END OS FUNCTIONS
//----------------------------------------------------------------







