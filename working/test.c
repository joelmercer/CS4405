#include "os.h"
#include "globalvars.h"

#define GREEN_LED_BASE 0x10000010
#define NIOS2_WRITE_STATUS(src) do { __builtin_wrctl(0, src); } while (0)

volatile int * green_led_ptr = (int *) GREEN_LED_BASE;

int i = 0;
int p = 0;
int b = 0;
int b2 = 0;
int end = 0;
int end2 = 0;
int FIFO1;
unsigned int green_led_pattern = 0x55555555;
int pattern = 0;
int pattern2 = 0;
int wait = 0;
int wait2 = 0;
int fact = 1;

void test2(){
	
	
	end2 = OS_GetParam(); //Gets length of for loop
//end = 200;
	//green_led_pattern = 0; 
	green_led_pattern = 0x2;
	//Reads in pattern from FIFO
	//OS_Read(FIFO1, &green_led_pattern);	
	
	pattern2 = green_led_pattern;
	while(1) {
	if(wait2 == 0) {
			wait2 = 1;
		//	OS_Wait(0); 
		} 
		if(b2>=end2) {
	wait2 = 0;
	//OS_Signal(0);
//	b2=0;
}
//while(b2<end2) {
		
	for(i=0; i<100000; i++){
		*(green_led_ptr) = pattern2; //Blink pattern
	//	printf("blink");
	}

	//b2++;
	NIOS2_WRITE_STATUS( 0 );
	printf("************************************TEST2\n");
	NIOS2_WRITE_STATUS( 1 );
	

	if(b2<end2){ //Check if it should stop
	
		for(i=0; i<100000; i++){

			*(green_led_ptr) = 0;
	
		}
	}
	
//}
	
	*(green_led_ptr) = 0; //Stop blinking

	}
	//OS_Signal(0); //Release Semaphore
	
	processarray[workingpid].state = 0;
	return;
}


void test3(){
	

	end = OS_GetParam(); //Gets length of for loop

	OS_Read(FIFO1, &green_led_pattern);	
	
	pattern = green_led_pattern;
	while(1) {
		if(wait == 0) {
			wait = 1;
		
		}
		if(b>=end) {

	wait =0;
	b=0;
	while(1){}
}

		
	for(i=0; i<100000; i++){
		*(green_led_ptr) = pattern; //Blink pattern
	
	}

NIOS2_WRITE_STATUS( 0 );
	printf("************************************TEST3\n");
	NIOS2_WRITE_STATUS( 1 );

	if(b<end){ //Check if it should stop
	
		for(i=0; i<100000; i++){

			*(green_led_ptr) = 0;
	
		}
	}
	
//}
	
	*(green_led_ptr) = 0; //Stop blinking

	}
	processarray[workingpid].state = 0;
	return;
}



void test4(){
	
	
	end2 = OS_GetParam(); //Gets length of for loop
//end = 200;
	//green_led_pattern = 0; 
	green_led_pattern = 0x55555555;
	//Reads in pattern from FIFO
	//OS_Read(FIFO1, &green_led_pattern);	
	
	pattern2 = green_led_pattern;
	while(1) {
	if(wait2 == 0) {
			wait2 = 1;
		//	OS_Wait(0); 
		} 
		if(b2>=end2) {
	wait2 = 0;
	//OS_Signal(0);
//	b2=0;
}
//while(b2<end2) {
		
	for(i=0; i<100000; i++){
		*(green_led_ptr) = pattern2; //Blink pattern
	//	printf("blink");
	}

	//b2++;
	NIOS2_WRITE_STATUS( 0 );
	printf("************************************TEST4\n");
	NIOS2_WRITE_STATUS( 1 );
	

	if(b2<end2){ //Check if it should stop
	
		for(i=0; i<100000; i++){

			*(green_led_ptr) = 0;
	
		}
	}
	
//}
	
	*(green_led_ptr) = 0; //Stop blinking

	}
	//OS_Signal(0); //Release Semaphore
	
	processarray[workingpid].state = 0;
	return;
}


void devicep() {

	green_led_pattern = 0xF;
	
	for(i=0; i<100000; i++){
		*(green_led_ptr) = green_led_pattern; //Blink pattern
	//	printf("blink");
	}

NIOS2_WRITE_STATUS( 0 );
	printf("************************************TESTDB\n");
	NIOS2_WRITE_STATUS( 1 );
	
	for(i=0; i<100000; i++){

		*(green_led_ptr) = 0;
	
	}

	*(green_led_ptr) = 0; //Stop blinking

}

void ppprocess() {

	green_led_pattern = 0xF0;
	
	for(i=0; i<100000; i++){
		*(green_led_ptr) = green_led_pattern; //Blink pattern
	//	printf("blink");
	}

NIOS2_WRITE_STATUS( 0 );
	printf("************************************TESTDB\n");
	NIOS2_WRITE_STATUS( 1 );
	
	for(i=0; i<100000; i++){

		*(green_led_ptr) = 0;
	
	}

	*(green_led_ptr) = 0; //Stop blinking

}

