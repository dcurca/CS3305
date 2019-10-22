/* This program takes two command arguments and sends them through the pipe where the parent adds both numbers and outputs the resulting sum 
Dana Curca 250976773 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char* argv[]) {
	pid_t pid, i, j, k;
	int mypipe[2];
	char c[100]; //arbitrary character array for string written to pipe
	pipe(mypipe); //initializing the pipe
	int x = atoi(argv[1]);

// checking for pipe error - if true exit program
if (pipe(mypipe) < 0){
	perror("pipe error");
	exit(0);
	}

pid = fork();
wait(NULL);

// checking for fork erorr - if true exit program
if (pid < 0){
	perror("fork error");
	exit(0);
	}

	else if (pid > 0) { //parent process begins
		i = getpid();
		printf("\n A pipe is created for communication between parent (PID %d) and child\n", i);
		read(mypipe[0],c,10); //reading the second command line argument from the pipe
		printf("\n parent (PID %d) Reading X = %s from the user\n", i, argv[1]);
		printf("\n parent (PID %d) Reading Y from the pipe\n ", i);
		printf("\n parent (PID %d) adding X+Y = %d\n", i, x + atoi(c)); //adds the sum of both command line arguments 
	}

else { //child process begins
	j = getpid();
	k = getppid();
	printf("\n parent (PID %d) created a child (PID %d)\n", k, j);
	printf("\n child (PID %d) Reading Y = %s from the user\n", j, argv[2]);
	write(mypipe[1],argv[2],10); //writing the second command line argument to the pipe
	printf("\n child (PID %d) Writing Y into the pipe\n", j);
}

return 0;
}

