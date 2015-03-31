#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct readonlyfiles
{
	char * filename;
	int address;
} readfile;

typedef struct copyonwritefiles
{
	char * filename;
	int address;
} writefile;

int frames = 0;
char * memtrace;

int pdir[2048];
int ptable[10];
int **base;

//Mem_trace
FILE * memfile;
char memrw[1];
unsigned int memaddress;
unsigned int memdata;

//MAIN STARTS HERE
int main ( int argc, char *argv[] ) {
int i=0, j=0, k=0, lcount=0, scount=0;
int frames;

char * test;

for(i = 0; i < argc; i++) {
if (strcmp(argv[i],"-l") == 0)
lcount++;
if (strcmp(argv[i],"-s") == 0)
scount++;
}

readfile readarray[lcount];
writefile writearray[scount];

for(i = 0; i < argc; i++) {

if (strcmp(argv[i],"-l") == 0) {
readarray[j].filename = argv[i+1];
readarray[j].address = atoi(argv[i+2]);
j++;
}
if (strcmp(argv[i],"-s") == 0) {
writearray[k].filename = argv[i+1];
writearray[k].address = atoi(argv[i+2]);
k++;
}
if (strcmp(argv[i],"-f") == 0) {
frames = atoi(argv[i+1]);
}
if (strcmp(argv[i],"-r") == 0) {
memtrace = argv[i+1];
}
}

char mainmemory [(frames*2048)];

//11111111111000000000000000000000 - 4292870144
//00000000000111111111100000000000 - 2095104
//00000000000000000000011111111111 - 2047

//01000000000000000000000000000000 - 1073741824
//01011001011010000010111100000000 - 1500000000

//unsigned int pd = ((readarray[0].address & 4292870144) >> 21);
//unsigned int pm = ((readarray[0].address & 2095104) >> 11);
//unsigned int off = readarray[0].address & 2047;

//printf("\npd: %d\n", pd);
//printf("pm: %d\n", pm);
//printf("off: %d\n", off);


//Open Mem_trace

printf("got here\n");

memfile = fopen (memtrace, "r");

fscanf(memfile, "%s %u %d", memrw, &memaddress, &memdata);

printf("\nmemrw: %s\n", memrw);
printf("memaddress: %u\n", memaddress);
printf("memdata: %d\n", memdata);


 
return 0;

}

