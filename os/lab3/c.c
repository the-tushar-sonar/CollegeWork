#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t parent = getpid();
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    } 
    else if (pid > 0) {
        // Parent process
        int status;
        printf("Parent (PID: %d) waiting for child to execute new program...\n", parent);
        waitpid(pid, &status, 0); // wait for child
        printf("Parent (PID: %d) detected child finished execution.\n", parent);
    } 
    else {
        // Child process
        const char *args[] = {"/bin/echo", "Hello from child using execve!", NULL};
        const char *envp[] = {NULL};  // environment variables, can be NULL

        printf("Child (PID: %d) executing new program...\n", getpid());
        if (execve("/bin/echo", (char *const *)args, (char *const *)envp) == -1) {
            perror("execve failed");
            _exit(EXIT_FAILURE); // exit if execve fails
        }
    }

    return 0;
}
