#include "myos.h"


typedef struct memory
{
	//Memory Address
	MEMORY address;

	//Length
	int length;

	//Index in memory array
	int index;

	//Flags
	int available;

	//Traverse the linked list.
	struct Node* next;

}memStruct;



//Head of our main process list.
memStruct* memoryQueueHead;

//The Main Memory Array.
MEMORY mainMemory[4096]; //<-- 4096 bytes.


//Array of our memory structs
memStruct arrayOfBlocks[30];


MEMORY OS_Malloc(int val);
BOOL OS_Free(MEMORY m);
void   OS_InitMemory();
