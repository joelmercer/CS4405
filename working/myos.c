#include "globalvars.h"

FIFO OS_InitFiFo() {

}

void OS_Write(FIFO f, int val) {

}

BOOL OS_Read(FIFO f, int *val) {

}

void OS_Start() {

    OS_Init();
}

void OS_Init() {
int i, j;
    
//init semaphores
    int semcounter = 0;
    for(i=0;i<MAXSEM;i++) {
        semarray[i].s = -1;
        semarray[i].n = -1;
    } 

}

void OS_Abort() {

}

PID  OS_Create(void (*f)(void), int arg, unsigned int level, unsigned int n) {

}
void OS_Terminate(void) {

}
void OS_Yield(void) {

}
int  OS_GetParam(void) {

}

void OS_InitSem(int s, int n) {
    int i, semcounter;
    
//disable interupts**********************************
    
    //check to make sure s doesn't already exist
    for(i=0;i<MAXSEM;i++) {
        if(semarray[i].s == s) {
            //enable interupts**********************************
            return; //Error
        }
    }
           
    //add s and n to semarray struct
    semarray[semcounter].s = s;
    semarray[semcounter].n = n;
    
    //Init sempid array       
    for(i=0;i<n;i++) {
    semarray[semcounter].sempid[i] = NULL; 
    }
    
    //counter up
    semcounter++;
           
//enable interupts**********************************
return;
}

void OS_Wait(int s){
    int i=0;
    int j=0;
    int currentpid = getpid(); //make getpid() work**********************************
    
//disable interupts**********************************
    
    //check for s
   while(i<MAXSEM) {
        if(semarray[i].s == s) {
                while(semarray[i].n <= 0){
                    OS_Yield(); //Context switch while waiting
                }
            semarray[i].n--;
            while(j<semarray[i].n) {
                if(semarray[i].sempid[j] == NULL){ 
                    semarray[i].sempid[j] = currentpid;
                        break;
                }
                j++;
            }
           break;
        }
       i++;
    }

//enable interupts**********************************

return;
}

void OS_Signal(int s) {
int i=0; 
int j=0;
int currentpid = getpid(); //make getpid() work**********************************    
    
//disable interupts**********************************

    //Check to see if this PID is holding the Semaphore
   while(i<MAXSEM) {
        if(semarray[i].s == s) {
            semarray[i].n++;
            while(j<semarray[i].n) {
                if(semarray[i].sempid[j] == currentpid){ 
                    semarray[i].sempid[j] = NULL;
                        break;
                }
                j++;
            }
           break; 
        }
       i++;
    
          } 
    
//enable interupts**********************************
return;
}

int main() {

    OS_Start();
    OS_InitSem(1, 5);
    OS_Wait(1);
    OS_Signal(1);
    return 0;
}

