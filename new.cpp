#include <stdio.h>
#include <unistd.h>

int main() {
    printf("My Process ID: %d", getpid());
    printf("Press Enter and check my memory usage...");
    getchar();
    return 0;
}