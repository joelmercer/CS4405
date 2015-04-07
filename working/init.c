#include "globalvars.h"

void OS_Init() {
	
	
	int i, j;
    int once = 1;

    //Init Memory
    oshp = 0x005FFC00;
   
    OS_InitMemory();
    
	//Init global vars
	sporadiccounter = 0;
	crash = 0;
	processcounter = 0; 
	FIFO f = 0;
	fifocounter=0;
	workingpid = EMPTY;

	//Schedule setup
	for(i=0;i<MAXPROCESS;i++) {
		sporadic[i] = EMPTY;
	}
    
    //PPP set up
    for(i=0;i<PPPLen;i++) {
        
        PPP[i] = EMPTY;           
        PPPMax[i] = EMPTY; 
    }
    
    //Device set up

    for(i=0;i<devicelen;i++) { 
    
        device[i] = EMPTY;
        devicemax[i] = EMPTY;
    }
    
    
		
	//init semaphores
		int semcounter = 0;
		for(i=0;i<MAXSEM;i++) {
			semarray[i].s = EMPTY;
			semarray[i].n = EMPTY;
		} 
		
	//init FIFOs
		for(j=0;j<MAXFIFO;j++){
			int clearfifo;
			fifocounter=j;
			clearfifo = OS_InitFiFo();
			fifoarray[clearfifo].data=EMPTY;
			fifoarray[clearfifo].flag=0;
		}
		
	//init processes
		processcounter = 1;
		printf("Does this get called more than once?****************************************************\n");
		for(i=0;i<MAXPROCESS;i++) {
			processarray[i].pid = EMPTY;
			processarray[i].arg = EMPTY;
			processarray[i].level = 0;
			processarray[i].n = 0;
            processarray[i].sp = EMPTY;
            processarray[i].hp = EMPTY;
            processarray[i].state = EMPTY;
		} 

		//Scheduler setup
		processarray[16].pid = 16;
			processarray[16].arg = EMPTY;
			processarray[16].level = 0;
			processarray[16].n = 0;
			processarray[16].sp = EMPTY;
            processarray[16].hp = EMPTY;
            processarray[16].state = 1;
		
	for(i=0;i<MAXPROCESS;i++) {
	sporadic[i] = EMPTY; 
	}
		
	j=0;    
	for(i=0;i<MAXFIFO;i++) {
		
		fifopidarray[i] = EMPTY;

		for(j=0;j<MAXFIFO;j++) {
			
			fifopidarray[i] = EMPTY;
		}
	}

	NIOS2_WRITE_IENABLE( 0x3 );		/* set interrupt mask bits for levels 0 (interval * timer) and level 1 (pushbuttons) */
	
	return;
}

void OS_Start() {
//	NIOS2_WRITE_STATUS( 1 );			// enable Nios II interrupts
	NIOS2_WRITE_STATUS( 0 );			// disable Nios II interrupts
    int s, p, d;
    
   printf("Restart loop\n");
        
	while(1) {
		
		
		int i = 0;
    devicetimer = 0;
    
    for(d=0;d<devicelen;d++) {
        if(devicemax[d]!=EMPTY) {
            devicetimer = devicemax[d];
        }
    }

		for(s=0;s<MAXPROCESS;s++) {
			
			//Checks crash value if there is a crash    
			if(crash==1) {
			goto crash;   
			}
			
			//keeping track of the next process
			processcounter = s;
			
            //Checks to see if a device should be run
            rundevice:
            if(devicetimer<=0) {
                for(d=0;d<devicelen;d++){
                    if(device[d]!=EMPTY) {
                     
                        for(i=0;i<MAXPROCESS;i++){
                            if(device[d]==processarray[i].pid)
                                workingpid = device[d];
                        }
                        
                        OS_StartTimer(0x2);
			int jasdfasdfas;
			int asdfasdfads;
			int asdfadsf;
			int asdfasdff;
                        workingpid = EMPTY;
                        
                        for(d=0;d<devicelen;d++) {
                            if(devicemax[d]!=EMPTY) {
                                devicetimer = devicemax[d];
                            }
                        }
                
                }
            }
            }
                
            //Looks for the next PPP process to run    
               for(p=0;p<PPPLen;p++){
                    if(PPP[p]!=EMPTY) {
                        if(PPP[p]!=-1){
                     
                        for(i=0;i<MAXPROCESS;i++){
                            if(PPP[p]==processarray[i].pid)
                                workingpid = PPP[p];
                        }
                        
                        OS_StartTimer(0x2);
			int jasdfasdfas;
			int asdfasdfads;
			int asdfadsf;
			int asdfasdff;
                        workingpid = EMPTY;
                        
                        for(p=0;p<PPPLen;p++) {
                            if(PPPMax[p]!=EMPTY) {
                                //decerment device timer
                                devicetimer -= PPPMax[p];
                                 if(devicetimer<=0) {
                                 goto rundevice;
                                 }
                            }
                        }
                //Looks for next spordic process to run
                } else {
					
			if(sporadic[s]!=EMPTY) {
			
			workingpid = processarray[sporadic[s]].pid;
			printf("OS_Start Call the timer\n");
			OS_StartTimer(0x2);
			int jasdfasdfas;
			int asdfasdfads;
			int asdfadsf;
			int asdfasdff;
				
			if(processarray[workingpid].state==0){
			OS_Terminate();
                
            //decerment device timer
			 devicetimer -= PPPMax[p];
                if(devicetimer<=0) {
                goto rundevice;
                }
			}
			
			//Save context switch of os_start PC+1 & Load context switch for sporadic[s]
			workingpid = EMPTY;
			} 
               }
					}
			   }
            
			//Looks for next spordic process to run if there is no PPP processes
		if(PPPLen <= 0) {
						if(sporadic[s]!=EMPTY) {
			
			workingpid = processarray[sporadic[s]].pid;
			
			printf("OS_Start Call the timer\n");
			savepid = 16;
			OS_StartTimer(0x1);
			printf("stupid\n");
			int jasdfasdfas = 0;
			int asdfasdfads = 0;
			int asdfadsf = 0;
			int asdfasdff = 0;
			
			if(processarray[workingpid].state==0){
			OS_Terminate();
			}
			
			//Save context switch of os_start PC+1 & Load context switch for sporadic[s]
			workingpid = EMPTY;
			} 
               }
		} //end of s loop
		
	
	} //end of while
    
	crash:

	return;//Should only return on error
}


void OS_AddTo_Schedule(int pid, int level, int n) {
	int i = 0;
        
    if(level == 0) {
        
    for(i=0;i<devicelen;i++) { 
        if(device[i]==EMPTY){
    
            device[i] = pid;
            devicemax[i] = n;
            i=devicelen + 1;
     }
    }
    }
    
	if(level == 1) {
        
    for(i=0;i<PPPLen;i++) {
           if(PPP[i]==EMPTY){
        
            PPP[i] = n;           
            //PPPMax[i] = n; 
            i=PPPLen + 1;
           }
         
    }
        
    } 
    
	if(level == 2) {
		//Adds to sporadic level schedule list
        for(i=0;i<MAXPROCESS;i++) {
            if(sporadic[i]==EMPTY) {
                sporadic[i] = pid;
				i=MAXPROCESS + 1;
			}
        }
    }
    
	
	
return;    
}

void OS_Abort() {
	
	//goes to address 0x0
	int gotozero = 0x0;
	asm (	"mov	r31, %0" ::"r"(gotozero));
	asm (	"ret"			);
	  
}

void OS_StartTimer(int timecounter) {
	*(interval_timer_ptr) = 0; 
	*(interval_timer_ptr + 1) = 0; 
*(interval_timer_ptr + 0x2) = (timecounter & 0xFFFF);
*(interval_timer_ptr + 0x3) = (timecounter >> 16) & 0xFFFF;
*(interval_timer_ptr + 1) = 0x5;	// STOP = 0, START = 1, CONT = 1, ITO = 1 
NIOS2_WRITE_IENABLE( 0x3 );
NIOS2_WRITE_STATUS( 1 );
return;

}
