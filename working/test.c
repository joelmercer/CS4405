#define GREEN_LED_BASE 0x10000010
#define NIOS2_WRITE_STATUS(src) do { __builtin_wrctl(0, src); } while (0)

volatile int * green_led_ptr = (int *) GREEN_LED_BASE;
int green_led_pattern = 0x55555555;
int green_led_pattern2 = 0x44444444;

int i = 0;
int b = 0;

int blink(){
int end = OS_GetParam();	
	
for(i=0; i<100000; i++){


*(green_led_ptr) = green_led_pattern;

}
printf("param: %d \n",b);
b++;
if(b<end){
dontblink();
}
b = 0;
*(green_led_ptr) = 0;
return;
}

int dontblink(){
	
for(i=0; i<100000; i++){


*(green_led_ptr) = 0;

}	\
blink();
return;

}

int blink2(){
int end = OS_GetParam();	

for(i=0; i<100000; i++){


*(green_led_ptr) = green_led_pattern2;

}
printf("param: %d \n",b);
b++;
if(b<end){
dontblink2();
}
b=0;
*(green_led_ptr) = 0;
return;
}

int dontblink2(){
	
for(i=0; i<100000; i++){


*(green_led_ptr) = 0;

}	\
blink2();
return;

}



