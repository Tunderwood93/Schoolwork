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
		close(fd[1]);
		//dup(fd[0]);
		dup2(fd[0], 0);
		//close(fd[0]);
		//close(fd[1]);
		//execv("./sort");
		 execlp("./sort", "sort", (void *) 0);
	
		/*	aarons
 			close(1)
			dup(fd[1])
			close(fd[0])
			close(fd[1])
			execlp(argv[1], argv[1], null) // Takes ./find or ./sort from cmd line
		*/

	}
	else // controled by the parent
	{
		wait(NULL);
		close(fd[0]);
		//dup(fd[1]);
		dup2(fd[1], 1);
		//close(fd[1]);
		//close(fd[0]);
		 execlp("./find", "find", (void *) 0);
		//execv("./find");
		/* aarons
 * 		close(0)
 * 		dup(fd[0])
 * 		close(fd[1])
 * 		close(fd[0])
 * 		execlp(argv[2],argv[2], null);
 *		*/
	}


	return 0; 
}
