#include "process.h"

//==============
//GLOBALS
PID pidIndex = 0;
#define NULL 0





//----------------------------------------------------------------
//                      PROCESS CALLS
//----------------------------------------------------------------


//=-=-=-=-=-=-=-=-=-=-=-
//Queue Functions

int enqueueProcess(process **head, process *newProcess)
{
    process *tmp;

    if (newProcess == NULL)
        return -1;

    //Case where it is the first one in the list.
    if (*head == NULL)
    {
        *head = newProcess;
        newProcess->next = NULL;
    }
    //Else the list is not empty, append this sem to the tail.
    else
    {
        tmp = *head;
        while (tmp->next != NULL)
            tmp = tmp->next;

        tmp->next = newProcess;
        newProcess->next = NULL;
    }
    return 1;
}




process* dequeueProcess(process **head)
{
    process *tmp = NULL;

    if (*head != NULL)
    {
        tmp = *head;
        *head = (*head)->next;
    }
    else
    {
        return NULL;
    }
    return tmp;
}



//Given a process queue, it will find the matching process
//for a given PID
process* findPID(process *head, int PID)
{
    process *tmp = head;
    while (tmp != NULL)
        if (tmp->PID == PID)
            return tmp;
        else
            tmp = tmp->next;
    return tmp;
}






//-=-=-=-=-=-=-=-=-=-=-
//OS Functions


PID  OS_Create(void (*f)(void), int arg, unsigned int level, unsigned int n)
{
    //Update the current PID
    pidIndex += 1;

    //Find an available process struct (PCB)
    int i;
    process *tmp;
    process *proc = NULL;
    for(i = 0; i < MAXPROCESS; i++)
    {
        tmp = &processStructArray[i];

        if(tmp->available == 1)
        {
            proc = &processStructArray[i];
            break;
        }
    }

    //Check to see if we couldn't find one
    if(proc == NULL)
        return 0;

    //Set some fields
    proc->available = 0;
    proc->process = f;
    proc->PID = pidIndex;
    proc->arg = arg;
    proc->procLock = 0;

    //Append to the appropriate queue
    enqueueProcess(&sporadicQueueHead, proc);

    return pidIndex;
}



void OS_Terminate(void)
{
    //Get the process off the queue. This essentially "kills it"
    //in our current primitive kernal.
    process *proc = dequeueProcess(&sporadicQueueHead);

    //Kill it.

    //Release semaphores it had

    //Free up its memory

}


void OS_Yield(void)
{
    //Queue the head process into the back.
    // TODO: When multiple processes are implemented (periodic, device),
    // implement OS_Yield.
    //
    // Do this by popping the current process and
    // return it to the end of the queue to try again at a later
    // point. This will return the context switch back to the
    // scheduler, to prevent dealing with multiple scope levels.
    // :D
}


int  OS_GetParam(void)
{
    //Gather the param from the process that is the current
    //head of the queue. AKA the process that is executing.
    process *proc = sporadicQueueHead;
    int param = proc->arg;

    return param;
}


//----------------------------------------------------------------
//                      END PROCESS CALLS
//----------------------------------------------------------------


