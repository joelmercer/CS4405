#include <stdlib.h>
#include "myos.h"
#include "process.h"
#define NULL 0


//=================
//Structs

typedef struct sem_t
{
	//Used to ID the sem
	int semID;

	//The position of this semaphore in the
	//master active semaphore array.
	int index;

	//The actual mutex value.
	int lock;

	//The array of waiting PIDs
	PID waitingPID[MAXPROCESS];
	int waitListIndex;

	//For semaphore queue
	struct sem_t* next;
}semaphore;







//=================
//Globals

//Used as a handler for our queue of sems.
semaphore* masterSem = NULL;






//==================
//Queue Functions

int enqueueSemaphore(semaphore **head, semaphore *newSem)
{
    semaphore *tmp;

    if (newSem == NULL)
        return -1;

    //Case where it is the first one in the list.
    if (*head == NULL)
    {
        *head = newSem;
        newSem->next = NULL;
    }
    //Else the list is not empty, append this sem to the tail.
    else
    {
        tmp = *head;
        while (tmp->next != NULL)
            tmp = tmp->next;

        tmp->next = newSem;
        newSem->next = NULL;
    }
    return 1;
}




semaphore* dequeue(semaphore **head)
{
    semaphore *tmp = NULL;

    if (*head != NULL)
    {
        tmp = *head;
        *head = (*head)->next;
    }
    return tmp;
}




semaphore* findSemID(semaphore *head, int sem_ID)
{
    semaphore *tmp = head;
    while (tmp != NULL)
        if (tmp->semID == sem_ID)
            return tmp;
        else
            tmp = tmp->next;
    return tmp;
}






//==================
//Semaphore Functions

//Here we lay out memory for our new node.
void OS_InitSem(int sem_ID, int max_num)
{
	//Lay out memory for our semaphore
	semaphore *sem = malloc(1024); //<-- DONT FUCKING MALLOC

	//Initialize some sem data
	sem->semID = sem_ID;
	sem->lock = max_num;
	sem->waitListIndex = 0;
	sem->next = NULL;

	for(int = 0; i < MAXPROCESS; i++)
		tmp->waitingPID[i] = 0);



	//Throw our new semaphore in front of the list of sems.
	enqueueSemaphore(&masterSem, sem);
}




void OS_Wait(int sem_ID)
{
	//Create a handler for the requested sem
	semaphore *tmp;
	tmp = findSemID(masterSem, sem_ID);

	//decrement lock
	tmp->lock -= 1;
	
	if(tmp->lock < 0)
	{
		//Create a handle to the current process, set its lock.
		proc *current = sporadicQueueHead;
		current->procLock = 1;

		//Add the caller to the list of waiting processes.
		tmp->waitingPID[tmp->waitListIndex] = current->PID;
		tmp->waitListIndex++;

		//Check if lock is in use
		while(current->procLock == 1);
	}
}




void OS_Signal(int sem_ID)
{
	//Create a handler for the requested sem
	semaphore *sem;
	sem = findSemID(masterSem, sem_ID);

	//Gather the PId of the next process up
	//for the semaphore.
	PID nextProcess = sem->waitingPID[0];

	//Move through process list until we find
	//the one that matches and tell it to go.
	process *tmp = sporadicQueueHead;
    while (tmp->PID != nextProcess)
    	tmp = tmp->next;

    //Give that process the go ahead.
    tmp->procLock = 0;

    //Remove the process from the wait list
    for(int = 0; i < MAXPROCESS; i++)
		tmp->waitingPID[i] = tmp->waitingPID[i+1];
    
	//Update index
	tmp->waitListIndex--;

	//increment lock
	sem->lock += 1;
	
	return;
}
