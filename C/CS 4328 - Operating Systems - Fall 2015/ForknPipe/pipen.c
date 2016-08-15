/*

3. Write a c program to set up a parent-TO-child pipe; the parent 
should 'exec' to perform a "find" process and its output should be 
connected to the pipe connected to the child, which should 'exec' to 
perform a "sort" process.

*/
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int pid; 
	int fd[2];
	pipe(fd);
	pid = fork();

	if(pid < 0)
	{
		return -1; // Error Condition
	}
	else if(pid == 0) // Controled by the child
	{
 			close(1);
			dup(fd[1]);
			close(fd[0]);
			close(fd[1]);
			execlp(argv[1], argv[1], NULL);// Takes ./find and ./sort from cmd line
	}
	else // controled by the parent
	{

 		close(0);
  		dup(fd[0]);
  		close(fd[1]);
  		close(fd[0]);
  		execlp(argv[2],argv[2], NULL);

	}


	return 0; 
}
