#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct readonlyfiles
{
	char filename[100];
	int address;
} readfile;

typedef struct copyonwritefiles
{
	char filename[100];
	char address[11];
} writefile;

int frames = 0;
char memtrace[100];



int main ( int argc, char *argv[] ) {
	int i=0, k=0, sum = 0, opt;
	
	int binA[11] = {0}; // for pDir
	int a=0;
	int binB[10] = {0}; // for pTable
	int b=0;
	int binC[11] = {0}; // for offset
	int c=0;
	
	int pDir[2048] = {0};
	int pTable[1024] = {0;};
	int offset[2048] = {0};

	int number; 

	printf("How many -l ?\n");
	  scanf("%d", &number);

	readfile readarray[number];

	for(i = 0; i < number; i++) {
		printf("Name of file?\n");
		  scanf("%s", &readarray[i].filename);

		printf("Address of file?\n");
		  scanf("%d", &readarray[i].address);
	}

	printf("How many -s ?\n");
	  scanf("%d", &number);

	writefile writearray[number];

	for(i = 0; i < number; i++) {
		printf("Name of file?\n");
		  scanf("%s", &writearray[i].filename);

		printf("Address of file?\n");
		  scanf("%s", &writearray[i].address);
	}

	int frames;

	printf("Number of frames?\n");
	  scanf("%d", &frames);

	printf("What is the -r trace file name?\n");
	  scanf("%s", &memtrace);

	long long temp = 1234567899;
	int binAdd[32] = {0};

	toBinary(binAdd, temp);

	printf("\nAddress: ");

	for(i = 31; i >= 0; i--){
		printf("%d", binAdd[i]);
	}
	
	//code for separating address bits
	k=0;
	for(i=0; i<11; i++){
		binA[k]=binAdd[i];
		k++
	}
	a=toDecimal(binA);
	
	k=0;
	for(i=11; i<21; i++){
		binB[k]=binAdd[i];
		k++
	}
	b=toDecimal(binB);
	
	k=0;
	for(i=21; i<32; i++){
		binC[k]=binAdd[i];
		k++
	}
	c=toDecimal(binC);
	
	printf("\n\n");
	//printf("\nArgs: %s %s %s %s %s %s %d %s  \n", readarray[0].filename, readarray[0].address, readarray[1].filename, readarray[1].address, writearray[0].filename, writearray[0].address, frames, memtrace);



	 
	return 0;

}

void toBinary(int bin[], int address){
	long long j;
	int n=32; //31?
	
	for(j=4294967296; j > 1 ; j = j/2) {
		if(address>=j){
			address=address-j;
			bin[n]=1;
		}else{
			bin[n]=0;
		}
		n--;
	}
	
	if((j==1)&&(address==1)) {
		bin[n]=1;
	}
	if((j==1)&&(address==0)) {
		bin[n]=0;
	}
	
	return;
}

int toDecimal(int bin[]){
	int n, j, retVal;
	int len = sizeof(bin) / sizeof(int);
	
	if(len==11){
		j=1024;
	} else{
		j=512;
	}
	
	for(n=0; n<len; n++){
		retVal+=(bin[n]*j);
		j=j/2;
	}
	
	return retVal;
}
