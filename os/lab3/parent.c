#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Bubble sort
void sortArray(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main()
{
    int arr[] = {5, 2, 8, 1, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    pid_t pid;

    sortArray(arr, n);
    printf("Parent process (PID: %d) Sorted Array : \n", getpid());

    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        exit(1);
    }
    else if (pid == 0)
    {
        // Child process
        printf("Child process (PID: %d) is loading a new program.../n", getpid());
        // Prepare arguments for execve
        char *program = "./child";
        char *args[n + 2];
        args[0] = program;
        for (int i = 0; i < n; i++)
        {
            char *numstr = malloc(10 * sizeof(char));
            sprintf(numstr, "%d", arr[i]);
            args[i + 1] = numstr;
        }
        args[n + 1] = NULL;

        execve(program, args, NULL);
        perror("execve failed");
        exit(1);
    }
    else
    {
        // Parent Process

        wait(NULL);
        printf("Parent process is done waiting. Child process finished.\n");
    }

    return 0;
}