#include <stdio.h>


/*

4. Write a program to take a UNIX command from the command line
and fork() a child to execute it. The command can be a simple 
command like: $ls or $ps, Or it can be a command with options such as
$ls -t -l. Use argc and argv[] in the main function to pass parameters.
When the child process is executing the command, the parent process 
simply waits for the termination of the child process. The process 
id of the parent and the child should be printed out using getpid() and
getppid() functions.

*/
int main(int argc, char *argv[])
{
	int pid;
	pid = fork();

	if(pid < 0)
	{
		//error
		return -1;
	}
	else if(pid == 0) // child
	{
		system(argv[1]);
	}
	else // parent
	{
		wait(pid);
		printf("The Parent's PID is %d, while the Child's PID is %d \n", (int)getpid(), (int)getppid());
		printf("completed \n");
	}
}