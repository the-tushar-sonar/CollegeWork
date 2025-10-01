#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t parent = getpid();    // store parent PID
    pid_t pid = fork();         // create child process

    if (pid == -1) {
        // fork failed
        perror("fork failed");
        exit(EXIT_FAILURE);
    } 
    else if (pid > 0) {
        // Parent process
        int status;
        printf("Parent (PID: %d) waiting for child...\n", parent);
        printf("Status: %d",status);
        waitpid(pid, &status, 0); // wait for child to finish
        
        printf("Parent (PID: %d) detected child finished.\n", parent);
    } 
    else {
        // Child process
        printf("Child (PID: %d) running...\n", getpid());
        // Instead of execve, just print message
        _exit(EXIT_SUCCESS);      // exit child
    }

    return 0;
}