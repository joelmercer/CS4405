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
long long j;
int binAdd[32] = {0};
i=32;

for(j=4294967296; j > 1 ; j = j/2) {
printf("j: %llu \n", j);

if(temp>=j){
temp=temp-j;
binAdd[i]=1;
printf("Binadd[%d]: %d\n", i, binAdd[i]);
}else{
binAdd[i]=0;
printf("Binadd[%d] : %d\n", i, binAdd[i]);
}

printf("j: %llu temp: %llu \n", j, temp);

i--;
}

if((j==1)&&(temp==1)) {
binAdd[i]=1;
printf("Binadd[%d]: %d\n", i, binAdd[i]);
}

if((j==1)&&(temp==0)) {
binAdd[i]=0;
printf("Binadd[%d]: %d\n", i, binAdd[i]);
}


printf("\nAddress: ");

for(i = 31; i >= 0; i--)
printf("%d", binAdd[i]);

printf("\n\n");
//printf("\nArgs: %s %s %s %s %s %s %d %s  \n", readarray[0].filename, readarray[0].address, readarray[1].filename, readarray[1].address, writearray[0].filename, writearray[0].address, frames, memtrace);



 
return 0;

}

