// alloc_test.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

#include "alloc.h" /* expected functions:
                     int init_alloc(void);
                     void *alloc(size_t);
                     void dealloc(void *);
                     int cleanup(void);
                   */

int main(void)
{
    if (init_alloc() != 0) {
        fprintf(stderr, "init_alloc() failed (mmap or setup failed)\n");
        return 1;
    }

    /* Elementary tests */
    char *s1 = alloc(512);
    char *s2 = alloc(512);

    if (s1 == NULL || s2 == NULL) {
        printf("alloc failed\n");
        cleanup();
        return 1;
    }

    strcpy(s1, "Hello, world!");
    if (strcmp("Hello, world!", s1) != 0)
        printf("Hello, world! test failed\n");
    else
        printf("Hello, world! test passed\n");

    dealloc(s1);
    dealloc(s2);

    printf("Elementary tests passed\n");
    printf("Starting comprehensive tests (see details in code)\n");

    /* === Test 1: allocate 4 chunks of 1KB and fill with 'a','b','c','d' respectively === */
    char stringA[1024], stringB[1024], stringC[1024], stringD[1024], stringX[1024];
    for (int i = 0; i < 1023; ++i) {
        stringA[i] = 'a';
        stringB[i] = 'b';
        stringC[i] = 'c';
        stringD[i] = 'd';
        stringX[i] = 'x';
    }
    stringA[1023] = stringB[1023] = stringC[1023] = stringD[1023] = stringX[1023] = '\0';

    char *strA = alloc(1024);
    char *strB = alloc(1024);
    char *strC = alloc(1024);
    char *strD = alloc(1024);

    if (!strA || !strB || !strC || !strD) {
        printf("Test 1 setup failed: one or more allocs returned NULL\n");
        cleanup();
        return 1;
    }

    for (int i = 0; i < 1023; ++i) {
        strA[i] = 'a';
        strB[i] = 'b';
        strC[i] = 'c';
        strD[i] = 'd';
    }
    strA[1023] = strB[1023] = strC[1023] = strD[1023] = '\0';

    if (strcmp(stringA, strA) == 0 &&
        strcmp(stringB, strB) == 0 &&
        strcmp(stringC, strC) == 0 &&
        strcmp(stringD, strD) == 0) {
        printf("Test 1 passed: allocated 4 chunks of 1KB each\n");
    } else {
        printf("Test 1 failed: A: %d, B: %d, C: %d, D: %d\n",
               strcmp(stringA, strA),
               strcmp(stringB, strB),
               strcmp(stringC, strC),
               strcmp(stringD, strD));
    }

    /* === Test 2: dealloc C, reallocate and replace with x's === */
    dealloc(strC);
    char *strXptr = alloc(1024);
    if (!strXptr) {
        printf("Test 2 setup failed: alloc returned NULL\n");
        cleanup();
        return 1;
    }
    for (int i = 0; i < 1023; ++i)
        strXptr[i] = 'x';
    strXptr[1023] = '\0';

    if (strcmp(stringX, strXptr) == 0)
        printf("Test 2 passed: dealloc and realloc worked\n");
    else
        printf("Test 2 failed: X: %d\n", strcmp(stringX, strXptr));

    /* === Test 3: dealloc B, allocate two 512-byte blocks and fill with y and z === */
    char stringY[512], stringZ[512];
    for (int i = 0; i < 511; ++i) {
        stringY[i] = 'y';
        stringZ[i] = 'z';
    }
    stringY[511] = stringZ[511] = '\0';

    dealloc(strB);
    char *strYptr = alloc(512);
    char *str2 = alloc(512);
    if (!strYptr || !str2) {
        printf("Test 3 setup failed: alloc returned NULL\n");
        cleanup();
        return 1;
    }

    for (int i = 0; i < 511; ++i) {
        strYptr[i] = 'y';
        str2[i] = 'z';
    }
    strYptr[511] = str2[511] = '\0';

    if (strcmp(stringY, strYptr) == 0 && strcmp(stringZ, str2) == 0)
        printf("Test 3 passed: dealloc and smaller realloc worked\n");
    else
        printf("Test 3 failed: Y: %d, Z: %d\n", strcmp(stringY, strYptr), strcmp(stringZ, str2));

    /* === Test 4: free two adjacent 512 blocks and allocate 1024 to check merge ===
       We used str2 and strYptr for these two 512 blocks; free them and allocate 1024
    */
    dealloc(str2);
    dealloc(strYptr);

    char *merged1024 = alloc(1024);
    if (!merged1024) {
        printf("Test 4 setup failed: alloc returned NULL\n");
        cleanup();
        return 1;
    }
    for (int i = 0; i < 1023; ++i)
        merged1024[i] = 'x';
    merged1024[1023] = '\0';

    if (strcmp(stringX, merged1024) == 0)
        printf("Test 4 passed: merge worked\n");
    else
        printf("Test 4 failed: X: %d\n", strcmp(stringX, merged1024));

    /* === Test 5: free two adjacent 1024 blocks and allocate 2048 to check larger merge ===
       We have strA (1KB), strD (1KB), and strXptr (1KB), merged1024 (1KB).
       For a safe test, free strXptr and merged1024 then allocate 2048.
    */
    dealloc(strXptr);
    dealloc(merged1024);

    char *str2048 = alloc(2048);
    if (!str2048) {
        printf("Test 5 setup failed: alloc returned NULL\n");
        cleanup();
        return 1;
    }

    char stringM[2048];
    for (int i = 0; i < 2047; ++i) {
        stringM[i] = 'z';
        str2048[i] = 'z';
    }
    stringM[2047] = str2048[2047] = '\0';

    if (strcmp(stringM, str2048) == 0)
        printf("Test 5 passed: merge alloc 2048 worked\n");
    else
        printf("Test 5 failed\n");

    /* cleanup */
    dealloc(strA);
    dealloc(strD);
    dealloc(str2048);

    if (cleanup() != 0) {
        fprintf(stderr, "cleanup() failed (munmap or teardown failed)\n");
        return 1;
    }

    return 0;