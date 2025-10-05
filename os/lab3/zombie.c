#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

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
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        exit(1);
    }
    else if (pid == 0)
    {
        // Child Process
        printf("Child (PID:%d) sorting the array ...\n", getpid());
        sortArray(arr, n);
        printf("Child Sorted Array : ");

        for (int i = 0; i < n; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("\n");
        printf("Child exiting...\n");
        exit(0);
    }
    else
    {
        // Parent Process
        printf("Parent (PID: %d) created child (PID: %d).\n", getpid(), pid);
        printf("Parent goes to sleep (10s)...\n");
        sleep(10);
        printf("Parent calling wait to clean up zombie.\n");
        wait(NULL);
        printf("Parent finished.\n");
    }

    return 0;
}