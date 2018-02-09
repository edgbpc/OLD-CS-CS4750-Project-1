#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#ifndef MAX_CANON
#define MAX_CANON 15
#endif

void print_usage () {
	printf("Format: proc_fan Option Integar < Filename \n Options:  \n -n to specify max number processes that can be ran at once\n\t Example: proc_fan -n 5 \n -h display this usage information\n");
}


int main (int argc, char *argv[]) {
//	FILE *fp;

	pid_t childpid = 0;
	pid_t endID;
	int status;	

	int i;
	int pr_limit;
	int pr_count = 0; //holds number of active children
	int option = 0;
//	fp = fopen(argv[3], "r");
	char str[13];
	int numtokens;
	char delimiters[] = " ";
	char **myargv;
	
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
//checks if file openned without error
//if(fp == NULL) {
//	perror("Proc_fan: Error: File Did Not Open.  Terminating program.");
//	return (-1);
//}

if (argc != 3){
	perror("Error: Incorrect parameters passed. proc_fan -h for help");
	exit(0);	
}



//in a main loap, continue until end of file reached

while (fgets(str, MAX_CANON, stdin) != NULL) { //fgets takes a line from testing.data.  loop stops when NULL is returned

	// if pr_count is pr_limit, wait for children to finish and decrement pr_count
	if (pr_count == pr_limit) {
		childpid = wait(NULL);
		pr_count--;
	} 
		//read  line from standard input and execute program corresponding to the command like by forking a child
	childpid = fork();
	pr_count++;


        if (childpid == 0) {
			if ((numtokens = makeargv(str, delimiters, &myargv)) == -1) {
				fprintf(stderr, "Failed to construct an arguement array for %s\n", str);
		
			} else {
				execvp(myargv[0], &myargv[0]);
			}
	//		return 1;
         	
	}
 


	do { //check to see if any of the children of finished.  decrement for each completed child
		endID = waitpid(childpid, &status, WNOHANG);
		if (endID != 0){
			pr_count =- 1;
		}		
	} while(!WIFEXITED(status) && !WIFSIGNALED(status));
	
};	
		for (i = 0; i < pr_count; i++){
			wait(NULL);
		}	

return 0;
}
