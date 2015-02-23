#include "globalvars.h"

void OS_Init() {
int i, j;

sporadiccounter = 0;
terminate = 1;
crash = 0;
processcounter = 0; 
FIFO f = 0;
workingpid = EMPTY;

//Schedule setup
for(i=0;i<MAXPROCESS;i++) {
    sporadic[i] = EMPTY;
}
    
//init semaphores
    int semcounter = 0;
    for(i=0;i<MAXSEM;i++) {
        semarray[i].s = EMPTY;
        semarray[i].n = EMPTY;
    } 
	
//init FIFOs
	for(j=0;j<MAXFIFO;j++){
		OS_InitFiFo();
		fifoarray[j].data=EMPTY;
	}
    
//init processes
    processcounter = 1;
    for(i=0;i<MAXPROCESS;i++) {
        processarray[i].pid = EMPTY;
        processarray[i].arg = EMPTY;
        processarray[i].level = 0;
        processarray[i].n = 0;
    } 

for(i=0;i<MAXPROCESS;i++) {
sporadic[i] = EMPTY; 
}



    
j=0;    
for(i=0;i<MAXFIFO;i++) {
    
    fifopidarray[i][j] = EMPTY;

    for(j=0;j<MAXFIFO;j++) {
        
        fifopidarray[i][j] = EMPTY;
    }
}

//Future Timer setup
//OS_Set_Timer(timeq);

return;
}

void OS_Start() {
    int s;
    int p = 0;
  

while(1) {
    int i = 0;
	int test = 0;
	for(i=0;i<MAXPROCESS;i++){
		test = sporadic[i];
		printf("Test %d: %d\n", i, test);
	}

    for(s=0;s<MAXPROCESS;s++) {
        
        processcounter = s;
		printf("Spordadic: %d and s: %d\n", sporadic[s], s); 
		
        if(sporadic[s]!=EMPTY) {
        printf("Going to context switch\n"); 
        //future timer function call: OS_Set_Timer(timeq); //set and load timer to timeq
		printf("Handed PID:%d\n", processarray[sporadic[s]].pid); 
		workingpid = processarray[sporadic[s]].pid;
        Context_Switch(workingpid);
            printf("returned\n");
			
        if(terminate==0){
			printf("TERMINATED!\n");
        OS_Terminate();
        terminate = 1;
        }
            printf("Crash: %d\n", crash);
        if(crash==1) {
        goto crash;   
        }
            printf("Didn't crash\n");
        //Save context switch of os_start PC+1 & Load context switch for sporadic[s]
		workingpid = EMPTY;
        } 
		
      printf("This is a good sign\n"); 
/*  Future PPP      
        for(p=p;p<PPPLen;p++) {
        
            OS_Set_Timer(PPPMax[p]);
            if(PPP[p] != IDLE) {
                //save context switch of os_start
                //load context switch to PPP
            }
        } //end of p loop

        if(p >= PPPLen) {
        pppcounter = 0; }
*/
       
	   
    } //end of s loop
    
} //end of while
    
crash:

return;//Should only return on error
}


void OS_AddTo_Schedule(int pid, int level) {
int i = 0;
    
	printf("add to PID: %d, Level: %d\n", pid, level);

    //Check level
    //Levels
    //SPORADIC 2      /* first-come-first-served, aperiodic */
    //PERIODIC 1      /* cyclic, fixed-order, periodic */
    //DEVICE 0      /* time-driven cyclic device drivers */

    
    if(level == 0) {
     //add to device Q   
    }
	if(level == 1) {
    //add to Periodic Q
    } 
	if(level == 2) {
		
        for(i=0;i<MAXPROCESS;i++) {
            if(sporadic[i]==EMPTY) {
				printf("get here: %d\n", sporadic[i]);
                sporadic[i] = pid;
				printf("get here: %d\n", sporadic[i]);
				i=MAXPROCESS+1;
			}
        }
    }
    
return;    
}



/* Future timer
void OS_Set_Timer(int timer) {

//Timer setup
*(timebase + 0x2 = (timer & 0xFFFF));
*(timebase + 0x3 = (timer >> 16) & 0xFFFF);    

  //Start Timer
*(timebase + 1) = 0x7;  
  
  return;
}
*/

void OS_Abort() {

//Disable Interrupts and never enable them
crash = 1;
return;
    
}
