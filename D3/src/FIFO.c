#include "os.h"
#include "process.h"
#define NULL 0


//================================================
//				 STOP INTERRUPTS
//================================================
//=================
//Structs

typedef struct FIFO_t
{
	//Holds the FIFO descriptor used to
	//ID this particular FIFO.
	FIFO descriptor;

	//The current position of the writer
	int indexW;

	//The current position of the reader.
	int indexR;

	//Pointer to the first array element of fifo data.
	unsigned int data[FIFOSIZE];

	//Linked List stuff
	//Traverse the doubly linked list.
	struct FIFOstruct* next;
	struct FIFOstruct* prev;

}FIFOstruct;


//===================
//GLOBALS
FIFOstruct *fifoStructHead = NULL;
int fifoCount;




FIFO OS_InitFiFo()
{
	//Create some elements to build the new FIFO
	FIFOstruct *newFIFO;
	newFIFO = malloc(sizeof(FIFOstruct)); //<--- REPLACE THIS :D

	//Creates an ID for the FIFO
	newFIFO->descriptor = fifoCount;
	fifoCount++;
	
	//To start the reader and writer at 0
	newFIFO->indexW = 0;
	newFIFO->indexR = 0;

	//initialize every element in the buffer to NULL
	int i;
	for(i = 0; i < MAXFIFO -1; i++)
	{
		newFIFO->data[i] = NULL;
	}

	//Add it to the list
	enqueueFIFO(fifoStructHead, newFIFO);

	return newFIFO->descriptor;
}






//===========================
//		Queue Functions
//===========================
int enqueueFIFO(FIFOstruct **head, FIFOstruct *newFIFO)
{
    FIFOstruct *tmp = NULL;

    if (newFIFO == NULL)
        return -1;

    //Case where it is the first one in the list.
    if (*head == NULL)
    {
        *head = newFIFO;
        newFIFO->next = NULL;
    }
    //Else the list is not empty, append this sem to the tail.
    else
    {
        tmp = *head;
        while (tmp->next != NULL)
            tmp = tmp->next;

        tmp->next = newFIFO;
        newFIFO->next = NULL;
    }
    return 1;
}




FIFOstruct* dequeueFIFO(FIFOstruct **head)
{
    FIFOstruct *tmp = NULL;

    if (*head != NULL)
    {
        tmp = *head;
        *head = (*head)->next;
    }
    return tmp;
}




//Given a process queue, it will find the matching process
//for a given PID
FIFOstruct* findFIFO(FIFOstruct *head, int descriptor)
{
    FIFOstruct *tmp = head;
    while (tmp != NULL)
        if (tmp->descriptor == descriptor)
            return tmp;
        else
            tmp = tmp->next;
    return tmp;
}



//===========================
//		END Queue Functions
//===========================





//===========================
//		FIFO FUNCTIONS
//===========================


void OS_Write(FIFO f, int val)
{
	//Handle for the requested FIFO
	FIFOstruct *temp = NULL;

	//Find the FIFO requested.
	temp = findFIFO(fifoStructHead, f);

	//We use Modular division to create a circular bounded buffer.
	int indexMod = temp->indexW % FIFOSIZE;
	temp->data[indexMod] = val;

	//Here, to keep our cicle working, we have to reset the index
	//if it has hit the limit.
	if(temp->indexW == FIFOSIZE)
		temp->indexW = 0;
	else
		temp->indexW += 1;

}


BOOL OS_Read(FIFO f, int *val)
{
	//Handle for the requested FIFO
	FIFOstruct *temp = NULL;

	//Find the FIFO requested.
	temp = findFIFO(fifoStructHead, f);


	if(temp == NULL)
		return FALSE;//could not find FIFO requested.

	//Set the reader position in the buffer
	int indexMod = temp->indexR % FIFOSIZE;
	
	if(temp->indexR == FIFOSIZE)
		temp->indexR = 1;
	else
		temp->indexR += 1;
	
	//Check to see if FIFO empty
	int check = 0;
	int i;
	for(i = 0; i < MAXFIFO -1; i++)
	{
		if(temp->data[i] != NULL)
			check = 1;
	}

	if(check != 0)
	{
		//Set the data *val points too with what is in the buffer.
		*val = temp->data[indexMod];
		return TRUE;
	}
	else
		return FALSE;
}



//===========================
//		END FIFO FUNCTIONS
//===========================




void main()
{

}




//================================================
//				 START INTERRUPTS
//================================================