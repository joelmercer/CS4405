#include<os.h>

void OS_Start() {

}

void OS_Init() {
int i, j;
    
//init semaphore arrays
    semcounter = 0;
    for(i=0;i<MAXSEM;i++) {
        for(j=0;j<2;j++){
            sem[j][i] = null;
        }
    } 

    for(i=0;i<MAXSEM;i++) {
        semcheckout[i] = null;
    } 
}

void OS_Abort() {

}