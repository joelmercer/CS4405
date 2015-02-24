#include "os.h"

#define GREEN_LED_BASE 0x10000010
#define NIOS2_WRITE_STATUS(src) do { __builtin_wrctl(0, src); } while (0)

volatile int * green_led_ptr = (int *) GREEN_LED_BASE;

int i = 0;
int b = 0;

int blink(int end, int pattern){
	
	for(i=0; i<100000; i++){
		*(green_led_ptr) = pattern; //Blink pattern
	}

	b++;

	if(b<end){ //Check if it should stop

		dontblink(end, pattern); //keep blinking
	}

	b = 0; //reset b
	*(green_led_ptr) = 0; //Stop blinking

	return;
}

int dontblink(int end, int pattern){
	
	for(i=0; i<100000; i++){

		*(green_led_ptr) = 0;
	}

	blink(end, pattern);
	return;
}

void test(){
	OS_Wait(0); //Semaphore Wait
	int end = OS_GetParam(); //Gets length of for loop

	int green_led_pattern = 0x55555555;
	
	blink(end, green_led_pattern); //Blink some lights!
	
	OS_Signal(0); //Release Semaphore
	return;
}

void test2(){
	OS_Wait(0); //Semaphore Wait
	int end = OS_GetParam(); //Gets length of for loop

	int green_led_pattern = 0x44444444;
	
	blink(end, green_led_pattern); //Blink some lights!
		
	OS_Signal(0); //Release Semaphore
	return;
}
