#include "os.h"

PID OS_Create(void (*f)(void), int arg, unsigned int level, unsigned int n) {

    //setup struct with PID, function*, arg, level, n
    //add to schedule
    //call the function given
    int i, processcounter;
    
NIOS2_WRITE_STATUS(0); //disable interupts
    
    //check to make sure you don't create too many processes
        if(processcounter >= MAXPROCESS) {
            NIOS2_WRITE_STATUS(1); //enable interupts
            return INVALIDPID; //Error INVALIDPID
        }
    
           
    //add s and n to semarray struct
    processarray[processcounter].pid = processcounter; //*******************????????????
    processarray[processcounter].function = &f;
    processarray[processcounter].arg = arg;
    processarray[processcounter].level = level;
    processarray[processcounter].n = n;
    
    //counter up
    processcounter++;
    
OS_AddTo_Schedule(processarray[processcounter].pid, level); 
           
NIOS2_WRITE_STATUS(1); //enable interupts
return;
}

void OS_Terminate(void) {

    //do last
	
	//remove pid from semaphore lists
	/**int j, k;
		for(j=0;j<MAXSEM;j++){
			for(k=0;k<semarray[j].n;k++){
				if(semarray[j].sempid[k]==//current pid//){ ///**************
					semarray[j].sempid[k]=EMPTY;
				}
			}
		}
	*/
}

void OS_Yield(void) {

Context_Switch_Save();
    return; //How to return back to OS_Start
    
}

int  OS_GetParam(void) {

}
