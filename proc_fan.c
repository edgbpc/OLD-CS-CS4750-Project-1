#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#ifndef MAX_CANON
#define MAX_CANON 14
#endif

void print_usage () {
	printf("Usage: proc_fan -n/-h\n-n to specify number of processes to spawn.\n  -h display this usage information\n");
}


int main (int argc, char *argv[]) {
	FILE *fp;

	pid_t childpid = 0;
	pid_t endID;
	int status;	

	int i;

	int pr_limit= -1;
	int pr_count;

	int option = 0;

	fp = fopen(argv[3], "r");
	char str[13];
	
while ((option = getopt(argc, argv, "n:h")) != -1){
	switch (option){
		case 'n' : pr_limit = atoi(optarg);
		break;

		case 'h': print_usage();
		return(0);		break;

		default : print_usage(); 
		exit(EXIT_FAILURE);
	}
}

if(fp == NULL) {
	perror("Error openning file");
	return (-1);
}


//if (argc != 2) {
//	fprintf (stderr, "Usage: %s, processes\n", argv[0]);
//	return 1;
//}

//numOfChildProcesses = atoi(argv[1]);
if (pr_limit ==  -1) {
	print_usage();
	exit(EXIT_FAILURE);
}

while (fgets(str, MAX_CANON, fp) != NULL) {
	
	if (pr_count == pr_limit) {
		childpid = wait(NULL);
		pr_count--;
	} else { 
		childpid = fork();
		system(str);
		pr_count++;
		}

	do {
		endID = waitpid(childpid, &status, WNOHANG);
		if (endID != 0){
			pr_count--;
		}		
	} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		
	
}
fclose(fp);

//for (i = 1; i < pr_limit; i++)
//	if ((childpid = fork()) <= 0 ){
//		system("./testsim 5 10");
//		break;
//}
//fprintf(stderr, "i:%d process ID:%ld parent ID:%ld child ID: %ld\n",
//	i, (long)getpid(), (long)getppid(), (long)childpid);
return 0;
}
