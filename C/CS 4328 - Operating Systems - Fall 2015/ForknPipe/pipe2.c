#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
int main(int argc, char *argv[])
{
        int fd[2];
        pid_t pid;
 
        if(pipe(fd) == -1)
        {
                perror("pipe");
                return 1;
        }
 
        if((pid = fork()) == -1)
        {
                close(fd[0]);
                close(fd[1]);
                perror("fork");
                return 1;
        }
 
        // Child
        if(pid == 0)
        {
                // Close write end of pipe.
                close(fd[1]);
                // Make standard input the read end of the pipe.
                dup2(fd[0], STDIN_FILENO);
                // Execute child program.
                execlp("./sort", "sort", (void *) 0);
                // If exec fails...
                _exit(1);
        }
        // Parent
        else
        {
                // Close read end of pipe.
                close(fd[0]);
                // Make standard output the write end of the pipe.
                dup2(fd[1], STDOUT_FILENO);
                // Execute parent program.
                execlp("./find", "find", (void *) 0);
                // If exec fails...
                _exit(1);
        }
 
        return 0;
}