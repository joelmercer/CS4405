#include "globalvars.h"

PID OS_Create(void (*f)(void), int arg, unsigned int level, unsigned int n) {
	int i;
		
	//Adds function args into our process structs    
	for(i=0;i<MAXPROCESS;i++) {
		if(processarray[i].pid == EMPTY) {      
			processarray[i].pid = i;
			processarray[i].function = f;
			processarray[i].arg = arg;
			processarray[i].level = level;
			processarray[i].n = n;
            processarray[i].sp = stackheap[0][i];
            processarray[i].hp = stackheap[1][i];
				
			printf("sp: 0x00%x \n", stackheap[0][i]);	
			printf("hp: 0x00%x \n", processarray[0].hp);	
			OS_AddTo_Schedule(i, level); 
				
			i = MAXPROCESS + 2;
		}
	}
		
	//Invalid PID check    
	if(i!=(MAXPROCESS+2)) {
		return INVALIDPID; //Error INVALIDPID
	}
	   
	return;
}

void OS_Terminate(void) {
    //do last
    int pid = workingpid;
	
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
		if(sporadic[i] == pid) {
			sporadic[i] = EMPTY;
			i = MAXPROCESS+1;
		}
	}
    
    //Clear processarray  
    processarray[pid].pid = EMPTY;
    processarray[pid].arg = EMPTY;
    processarray[pid].level = 0;
    processarray[pid].n = 0;
    processarray[pid].sp = EMPTY;
    processarray[pid].hp = EMPTY;
        
    
}
    


void OS_Yield(void) {

    //How to return back to OS_Start
    OS_Start();

    return; 
    
}

int  OS_GetParam(void) {
	return processarray[processcounter].arg;  
}

int  OS_GetPID(void) {
	return processarray[processcounter].pid;  
}
