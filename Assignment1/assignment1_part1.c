/* Program that creates a two child process within a parent process, one child process 
Dana Curca 250976773 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

int main () {
pid_t pid, pid2, pid3, i, j, k, l;
pid = fork(); //fork creation 

if(pid<0) { //check to make sure fork was successfully created 
	printf("fork unsuccessful");
	exit(1);
	}
if(pid>0) { //parent process begins 
	wait(NULL);

	pid3= fork();
	if(pid3 > 0) { //check for parent process (parent) that waits for child 1 and child 2 to finish 
		wait(NULL);
		}
	if(pid3 == 0) { //second child process begins (child 2)
		l = getpid();
		j = getppid();
		printf("parent (PID %d) created child_2 (PID %d)\n", j, l);
		printf("child_2 (PID %d) is calling an external program and leaving child_2...\n", 1);
		execl("external_program.out", NULL); //child 2 replaces this program with contents of external_program.out
		}
	}

if (pid==0) { //first child process begins (child 1)
	i = getpid();
	j = getppid();
	printf("parent process (PID %d) created child_1 (PID %d)\n", j, i);


	pid2 = fork();
	if (pid2 > 0){ //check for parent process (child 1) that waits for child 1.1 to finish
		wait(NULL);
		}
	if (pid2 ==0) { //child of child 1 begins (child 1.1)
		k = getpid();
		printf("parent (PID %d) is waiting for child_1 (PID %d) to complete before creating child_2\n", j, i); 
		printf("child_1 (PID %d) created child_1.1 (PID %d)\n", i, k);
		}
	}
return 0;
}
