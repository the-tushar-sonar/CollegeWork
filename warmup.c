// warmup.c
#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <errno.h>

int main(void) {
    pid_t pid = getpid();
    printf("PID: %d\n", pid);

    printf("\nPhase 1: no mmap yet.\n");
    printf("-> Open another terminal and run: ps -p %d -o pid,vsz,rss,cmd\n", pid);
    printf("Press Enter to create an anonymous mmap (Phase 2)...\n");
    getchar();

    size_t pagesize = (size_t) sysconf(_SC_PAGESIZE);
    void *p = mmap(NULL, pagesize, PROT_READ | PROT_WRITE,
                   MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (p == MAP_FAILED) {
        fprintf(stderr, "mmap failed: %s\n", strerror(errno));
        return 1;
    }
    printf("mmap returned %p (page size %zu bytes)\n", p, pagesize);

    printf("\nPhase 2: anonymous page mapped (not yet touched).\n");
    printf("-> Re-run: ps -p %d -o pid,vsz,rss,cmd   (or)   pmap -x %d\n", pid, pid);
    printf("Press Enter to write to the page (Phase 3)...\n");
    getchar();

    /* Touch the page: write to it so the kernel allocates physical RAM */
    printf("Writing to the mapped page (memset entire page)...\n");
    memset(p, 0xAB, pagesize);

    printf("\nPhase 3: page touched (written).\n");
    printf("-> Re-run: ps -p %d -o pid,vsz,rss,cmd   (or)   pmap -x %d\n", pid, pid);
    printf("Press Enter to unmap and exit...\n");
    getchar();

    if (munmap(p, pagesize) == -1) {
        perror("munmap");
    }
    printf("Unmapped and exiting.\n");
    return 0;
}
