#include "globalvars.h"


FIFO OS_InitFiFo() {
	NIOS2_WRITE_STATUS( 0 );
	int i, j;
	FIFO temp;
	//find unused fifo
	for(i=0; i<MAXFIFO; i++){
		if(fifopidarray[i]==EMPTY){
			temp=i;
			fifopidarray[i]=OS_GetPID();
			break;
		}
		if(i==(MAXFIFO-1) && (fifopidarray[i]!=EMPTY)){ // no empty fifos
		NIOS2_WRITE_STATUS( 1 );
			return INVALIDFIFO;
		}
	}
	//clear fifo
	for(i=0; i<MAXFIFO; i++){
		fifoarray[temp][i].head=0;
		fifoarray[temp][i].tail=0;
		fifoarray[temp][i].data=EMPTY;
		fifoarray[temp][i].flag=0;
	}
	fifoarray[temp][0].head=1;
	fifoarray[temp][0].tail=1;
	
	NIOS2_WRITE_STATUS( 1 );
	return temp;
}

void OS_Write(FIFO f, int val) {
	NIOS2_WRITE_STATUS( 0 );
	int i, k;
	for(i=0; i<FIFOSIZE; i++){
		if(fifoarray[f][i].tail==1){
			if((fifoarray[f][i].head==1) && (fifoarray[f][i].data==EMPTY)){ // empty fifo
				fifoarray[f][i].tail=0;
				fifoarray[f][fifoarray[f][i].next].tail=1;
				k=i;
				break;
			}
			else if((fifoarray[f][i].head==1) && (fifoarray[f][i].data!=EMPTY)){ // fifo full
				fifoarray[f][i].head=0;
				fifoarray[f][fifoarray[f][i].next].head=1;
				fifoarray[f][i].tail=0;
				fifoarray[f][fifoarray[f][i].next].tail=1;
				k=i;
				break;
			}
			else{
				fifoarray[f][i].tail=0;
				fifoarray[f][fifoarray[f][i].next].tail=1;
				k=i;
				break;
			}
		}
	}
	fifoarray[f][k].data=val;
	NIOS2_WRITE_STATUS( 1 );
	return;
}

BOOL OS_Read(FIFO f, int *val) {
	NIOS2_WRITE_STATUS( 0 );
	int i;
	for(i=0; i<FIFOSIZE; i++){
		if(fifoarray[f][i].head==1){
			if(fifoarray[f][i].data!=EMPTY){
				fifoarray[f][i].flag=0;
				*val=fifoarray[f][i].data;
				fifoarray[f][i].data=EMPTY;
				fifoarray[f][i].head=0;
				fifoarray[f][fifoarray[f][i].next].head=1;
					if(fifoarray[f][fifoarray[f][i].next].tail==1){
						if(fifoarray[f][fifoarray[f][i].next].data!=EMPTY){
							fifoarray[f][fifoarray[f][i].next].tail=0;
							fifoarray[f][fifoarray[f][fifoarray[f][i].next].next].tail=1;
						}
					}
				NIOS2_WRITE_STATUS( 1 );
				return TRUE;
			}else{
				NIOS2_WRITE_STATUS( 1 );
				return FALSE;
			}
		}
	}
}
