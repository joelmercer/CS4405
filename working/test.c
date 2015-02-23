#define GREEN_LED_BASE 0x10000010
#define NIOS2_WRITE_STATUS(src) do { __builtin_wrctl(0, src); } while (0)

volatile int * green_led_ptr = (int *) GREEN_LED_BASE;
int green_led_pattern = 0x55555555;
int green_led_pattern2 = 0x44444444;
int i = 0;
int k = 0;
int db = 0x00000378;
int b = 0x00000378;

void blink(){
for(i=0; i<100000; i++){


*(green_led_ptr) = green_led_pattern;

}

//asm ("ldw (pc), (db)");
printf("%d\n",b);
b++;
if(b<900){
dontblink();
} else {
	//OS_Abort();
}

return 0;
}

void dontblink(){
	
for(i=0; i<100000; i++){


*(green_led_ptr) = 0;

}	
//asm ("ldw (pc), (b)");
blink();
return;

}

void blink2(){
for(i=0; i<100000; i++){


*(green_led_ptr) = green_led_pattern2;

}

//asm ("ldw (pc), (db)");
printf("%d\n",b);
b++;
if(b<900){
dontblink2();
} else {
	//OS_Abort();
}

return 0;
}

void dontblink2(){
	
for(i=0; i<100000; i++){


*(green_led_ptr) = 0;

}	
//asm ("ldw (pc), (b)");
blink2();
return;

}

/*int main(){
NIOS2_WRITE_STATUS( 0 ); 	
int db = 0;
int b = 0;

//asm ("ldw (pc), (b)"); 




//while(1){
//blink();
//dontblink();


//}
return 0;
} */

