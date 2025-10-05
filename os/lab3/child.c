#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    printf("Child process received array: \n");
    for (int i = 1; i < argc; i++)
    {
        printf("%s ", argv[i]);
    }
    printf("\n");

    printf("Child process is displaying the array in reversed order:\n");
    for (int i = argc - 1; i >= 1; i--)
    {
        printf("%s ", argv[i]);
    }
    printf("\n");

    return 0;
}
