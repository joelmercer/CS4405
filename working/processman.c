#include "globalvars.h"

PID OS_Create(void (*f)(void), int arg, unsigned int level, unsigned int n) {
NIOS2_WRITE_STATUS(0); //disable interupts

int i;
    
for(i=0;i<MAXPROCESS;i++) {
    if(processarray[i].pid == EMPTY) {      
        //add args to processarray struct
        processarray[i].pid = i;
        processarray[i].function = &f;
        processarray[i].arg = arg;
        processarray[i].level = level;
        processarray[i].n = n;
            
        OS_AddTo_Schedule(i, level) 
            
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
	//deallocate fifos
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
	//deallocate memory, most likely with OS_Free()
}

void OS_Yield(void) {

Context_Switch_Save();
    return; //How to return back to OS_Start
    
}

int  OS_GetParam(void) {

}
