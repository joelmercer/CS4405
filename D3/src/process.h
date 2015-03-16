#include "myos.h"


//==========================================
//				PROCESS STRUCT
//==========================================
typedef struct proc_t
{
	//Used to ID the process
	PID PID; //<---- :o

	//Function Handle
	int (* process)();

    //Lock for semaphores.
	int procLock;

	//The index for its first block of memory.
	int blockIndex;

    //Argument
    int arg;

    //Availability of this particular PCB
    int available;

	//Traverse the doubly linked list.
	struct Node* next;
}process;



//Array of available process structs.
process processStructArray[MAXPROCESS];



//Head of our main process list.
process* sporadicQueueHead;
int processFunction(void);
