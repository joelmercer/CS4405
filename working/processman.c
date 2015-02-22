#include "globalvars.h"




PID OS_Create(void (*f)(void), int arg, unsigned int level, unsigned int n) {
NIOS2_WRITE_STATUS(0); //disable interupts

int i;
    
for(i=0;i<MAXPROCESS;i++) {
    if(processarray[i].pid == EMPTY) {      
        processarray[i].pid = i;
        processarray[i].function = &f;
        processarray[i].arg = arg;
        processarray[i].level = level;
        processarray[i].n = n;
            
        OS_AddTo_Schedule(i, level); 
            
        i = MAXPROCESS + 2;
    }
}
    
if(i!=(MAXPROCESS+2)) {
    NIOS2_WRITE_STATUS(1); //enable interupts
    return INVALIDPID; //Error INVALIDPID
}
   
NIOS2_WRITE_STATUS(1); //enable interupts
return;
}

void OS_Terminate(void) {
    //do last
    int pid = OS_GetPID();
	int i, k;
		//remove from semaphore lists
		for(i=0;i<MAXSEM;i++){//remove pid from semaphore lists
			for(k=0;k<semarray[i].n;k++){
				if(semarray[i].sempid[k]==pid){ 
					semarray[i].sempid[k]=EMPTY;//remove pid
				}
			}
		}
		//remove from fifo lists
		for(i=0;i<MAXFIFO;i++){//rows
			for(k=0;k<MAXFIFO;k++){//columns
				if(fifopidarray[i][k]==pid){
					fifopidarray[i][k]=0;//remove pid
				}
			}
		}

//remove from schedule
for(i=0;i<MAXPROCESS;i++) {
    if(sporadic[i] = pid);
        sporadic[i] = EMPTY;
       
     //deallocate memory, most likely with OS_Free()

    
}
    
}

void OS_Yield(void) {

<<<<<<< HEAD
//Context_Switch_Save();
=======
//****************
>>>>>>> origin/master
    return; //How to return back to OS_Start
    
}

int  OS_GetParam(void) {
	return processarray[processcounter].arg;  
}

int  OS_GetPID(void) {
	return processarray[processcounter].pid;  
}
