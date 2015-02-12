#include<os.h>
#include<globalvars.h>

void OS_InitSem(int s, int n) {
    int i;
    
//disable interupts
    
    //check to make sure s doesn't already exist
    for(i=0;i<MAXSEM;i++) {
        if(if(sem[i][0] = s) {
            //enable interupts
            return -1;
        }
    }
           
    //add s and n to sem array
    sem[0][semcounter]=s;
    sem[1][semcounter]=n;
    semcounter++;
           
//enable interupts
return;
}

void OS_Wait(int s){
    int i, tempS;
    int processpid = getpid();
//disable interupts
    
    //check for s
     for(i=0;i<MAXSEM;i++) {
        if(sem[0][i] = s) {
            tempS = i;
            sem[i][1]--;
            i=MAXSEM;
            //Add the PID of the process to list stating it has used this semaphore
        } 
    }

    while(sem[1][tempS]<= 0){
        OS_Yield(); //Context switch while waiting
    }
 
//enable interupts
return;
}

void OS_Signal(int s){
int i;
//disable interupts

    //Check to see if this PID is holding the Semaphore, if so, keep on
    
        //check for s
     for(i=0;i<MAXSEM;i++) {
        if(sem[0][i] = s) {
            tempS = i;
            sem[i][1]++;
            i=MAXSEM;
            //Remove the PID from the process to list stating it is finished using it.
        } 
    }
//enable interupts
return;
}