#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main (int argc, char *argv[]){
	int sleepTimer = atoi(argv[1]);
	int repeatFactor = atoi(argv[2]);
	
	int index;

for (index = 0; index < repeatFactor; index++){
	sleep(sleepTimer);
	fprintf (stderr, "Process ID is %d\n", getpid());
}
return 1;
}


