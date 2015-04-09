#include "globalvars.h"

int hey=0; //bartender being called by patron
int lock=1;
int count=0;
int numPatrons=3;
FIFO bar;
MEMORY* menu;

void bartender(){
	int open=1;
	
	menu = OS_Malloc(4*16);
	
	if(menu==0){ // OS_Malloc() failed
		OS_Terminate();
	}
	
	menu[]={3, 5, 6, 8, 2, 1, 4, 7, 6, 2, 7, 9, 5, 3, 4, 2};
	
	OS_InitSem(lock, 1);
	bar=OS_InitFiFo();
	
	while(open==1){
		if(numPatrons>0){ //bar open
			if(hey!=0){
				OS_Write(bar, menu[count]);
				if(count==15){
					count=0;
				} else{
					count++;
				}
				hey=0;
			} else {
				OS_Yield();
			}
		} else{
			open=0; // bar closed
		}
	}

	OS_Free(menu);
	OS_Terminate();
}

void patron(){

	int hasDrink=0;
	int done=0;
	int total=OS_GetParam;
	int counter=0;
	int timer=0;
	int* drink=0;
	
	while(done==0){
		if(hasDrink==0){
			OS_Wait(lock);
				hey=1;
				OS_Yield();
				OS_Read(bar, drink);
				total--;
				hasDrink=1;
			OS_Signal(lock);
			timer=*drink;
			while(timer>0){
				//sip
				timer--;
			}
		}
		if(total>0){
			hasDrink=0;
		} else{
			break;
		}
	}

	numPatrons--;
	OS_Terminate();
}
