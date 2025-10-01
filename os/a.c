#include <stdio.h>
#include <unistd.h>   // for fork()
#include <sys/wait.h> //for wait()

int main()
{
    pid_t pid;

    // Create a new process
    pid = fork();

    if (pid < 0)
    {
        // fork failed
        printf("Fork failed!\n");
    }
    else if (pid == 0)
    {
        // Child process
        printf("Child process: Hello from child! (PID: %d)\n", getpid());
    }
    else
    {
        // Parent process
        wait(NULL); // wait for child to finish
        printf("Parent process: Hello from parent! (PID: %d)\n", getpid());
    }

    return 0;
}
