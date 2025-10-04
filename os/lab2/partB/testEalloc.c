// test_ealloc.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#include "eAlloc.h"

/* Print a small hint and the current VSZ from /proc/<pid>/stat */
void printvsz(const char *hint) {
    char buf[256];
    int pid = (int)getpid();
    snprintf(buf, sizeof(buf), "echo -n \"%s \" && echo -n VSZ: && cut -d' ' -f23 /proc/%d/stat", hint, pid);
    system(buf);
    putchar('\n');
}

int main(void) {
    printf("\nInitializing memory manager\n\n");
    if (init_alloc() != 0) {
        fprintf(stderr, "init_alloc failed\n");
        return 1;
    }

    /* ----- Test 1: heap expansion ----- */
    printf("Test1: checking heap expansion; allocate 4 x 4KB chunks\n");
    printvsz("start test 1:");
    char *a[4];

    for (int i = 0; i < 4; ++i) {
        a[i] = alloc(4096);
        if (!a[i]) {
            fprintf(stderr, "alloc(4096) failed at i=%d\n", i);
            return 1;
        }
    }

    /* write to each chunk */
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4096; ++j) {
            a[i][j] = 'a';
        }
    }

    printvsz("should increase by ~4KB each (depending on allocator):");

    /* verify */
    int mismatch = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4096; ++j) {
            char x = a[i][j];
            if (x != 'a') {
                mismatch = 1;
                break;
            }
        }
        if (mismatch) break;
    }

    if (mismatch) {
        fprintf(stderr, "ERROR: Test1 - Chunk contents did not match\n");
        return 1;
    }

    for (int i = 0; i < 4; ++i) dealloc(a[i]);

    printvsz("after free (may or may not change VSZ):");
    printf("Test1: complete\n\n");

    /* ----- Test 2: splitting free chunks into 64 x 256B ----- */
    printf("Test2: Check splitting of existing free chunks: allocate 64 x 256B chunks\n");
    printvsz("start test 2:");

    char *b[64];
    for (int i = 0; i < 64; ++i) {
        b[i] = alloc(256);
        if (!b[i]) {
            fprintf(stderr, "alloc(256) failed at i=%d\n", i);
            return 1;
        }
        for (int j = 0; j < 256; ++j) b[i][j] = 'b';
    }

    printvsz("after allocations for test 2:");

    mismatch = 0;
    for (int i = 0; i < 64 && !mismatch; ++i) {
        for (int j = 0; j < 256; ++j) {
            if (b[i][j] != 'b') {
                mismatch = 1;
                break;
            }
        }
    }

    if (mismatch) {
        fprintf(stderr, "ERROR: Test2 - Chunk contents did not match\n");
        return 1;
    }

    for (int i = 0; i < 64; ++i) dealloc(b[i]);
    printvsz("after free of 64x256:");

    printf("Test2: complete\n\n");

    /* ----- Test 3: merging free chunks ----- */
    printf("Test3: checking merging of existing free chunks; allocate 4 x 4KB chunks\n");
    printvsz("start test 3:");

    char *c[4];
    for (int i = 0; i < 4; ++i) {
        c[i] = alloc(4096);
        if (!c[i]) {
            fprintf(stderr, "alloc(4096) failed at i=%d\n", i);
            return 1;
        }
    }

    /* write to them */
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4096; ++j)
            c[i][j] = 'c';

    printvsz("after allocations for test 3:");

    mismatch = 0;
    for (int i = 0; i < 4 && !mismatch; ++i) {
        for (int j = 0; j < 4096; ++j) {
            if (c[i][j] != 'c') {
                mismatch = 1;
                break;
            }
        }
    }

    if (mismatch) {
        fprintf(stderr, "ERROR: Test3 - Chunk contents did not match\n");
        return 1;
    }

    for (int i = 0; i < 4; ++i) dealloc(c[i]);
    printvsz("after free of 4x4KB (merged region expected):");
    printf("Test3: complete\n\n");

    /* cleanup */
    if (cleanup() != 0) {
        fprintf(stderr, "cleanup failed\n");
        return 1;
    }

    printf("All tests complete\n");
    return 0;
}