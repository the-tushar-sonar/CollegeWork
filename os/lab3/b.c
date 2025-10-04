#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    pid_t parent = getpid(); // store parent PID
    pid_t pid = fork();      // create child process

    if (pid == -1)
    {
        // fork failed
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    else if (pid > 0)
    {
        // Parent process
        printf("Parent (PID: %d) is running...\n",parent);

        // Getting input
        int n=5,i,j,temp;
        int arr[n];

        printf("Enter the 5 numbers");
        for(i=0;i<n;i++)
        {
            scanf("")

        }







      
        printf("waiting for child...\n");
        
        int status;
        waitpid(pid, &status, 0); // wait for child to finish

        printf("Parent (PID: %d) detected child finished.\n", parent);
    }
    else
    {
        // Child process
        printf("Child (PID: %d) running...\n", getpid());
        // Instead of execve, just print message
        _exit(EXIT_SUCCESS); // exit child
    }

    return 0;
}
