#include<os.h>

void OS_InitSem(int s, int n){
    
}

void OS_Wait(int s){
//disable interupts
    while(s <= 0){
        //interupt (like a early timer), save process, move to next process (don't forget to enable interupts again)
    }
    s--;
//enable interupts
}

void OS_Signal(int s){
    //disable interupts
    s++;
    //enable interupts
}
