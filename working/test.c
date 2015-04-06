#include "os.h"
#include "globalvars.h"

#define GREEN_LED_BASE 0x10000010
#define NIOS2_WRITE_STATUS(src) do { __builtin_wrctl(0, src); } while (0)

volatile int * green_led_ptr = (int *) GREEN_LED_BASE;

int i = 0;
int b = 0;
int b2 = 0;
int end = 0;
int end2 = 0;
int FIFO1;
int green_led_pattern = 0x55555555;
int pattern = 0;
int pattern2 = 0;

void test(){
	while(1) {
	//OS_Wait(0); //Semaphore Wait
	end = OS_GetParam(); //Gets length of for loop
//end = 200;
	//green_led_pattern = 0; 
	
	//Reads in pattern from FIFO
	OS_Read(FIFO1, &green_led_pattern);	
	
	pattern = green_led_pattern;
	
while(b<end) {
		
	for(i=0; i<100000; i++){
		*(green_led_ptr) = pattern; //Blink pattern
	//	printf("blink");
	}

	//b++;
	//NIOS2_WRITE_STATUS( 0 );
	//printf("B: %d\n", b);
	//NIOS2_WRITE_STATUS( 1 );
	

	if(b<end){ //Check if it should stop
	
		for(i=0; i<100000; i++){

			*(green_led_ptr) = 0;
	
		}
	}
	
}
	
	*(green_led_ptr) = 0; //Stop blinking

	 
	}
	//OS_Signal(0); //Release Semaphore
	processarray[workingpid].state = 0;
	return;
}



void test2(){
	//OS_Wait(0); //Semaphore Wait
	while(1) {
	
	end2 = OS_GetParam(); //Gets length of for loop
//end = 200;
	//green_led_pattern = 0; 
	green_led_pattern = 0x44444444;
	//Reads in pattern from FIFO
	//OS_Read(FIFO1, &green_led_pattern);	
	
	pattern2 = green_led_pattern;
	
while(b2<end2) {
		
	for(i=0; i<100000; i++){
		*(green_led_ptr) = pattern2; //Blink pattern
	//	printf("blink");
	}

	//b2++;
	//NIOS2_WRITE_STATUS( 0 );
	//printf("B: %d\n", b);
	//NIOS2_WRITE_STATUS( 1 );
	

	if(b2<end2){ //Check if it should stop
	
		for(i=0; i<100000; i++){

			*(green_led_ptr) = 0;
	
		}
	}
	
}
	
	*(green_led_ptr) = 0; //Stop blinking

	
	}
	//OS_Signal(0); //Release Semaphore
	
	processarray[workingpid].state = 0;
	return;
}
