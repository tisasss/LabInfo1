#include "int_info.h"
#include <stdio.h>
#include <stdlib.h>

void int_add(const void* a, const void* b, void* result) {
    *(int*)result = *(int*)a + *(int*)b;
}

void int_multiply(const void* a, const void* b, void* result) {
    *(int*)result = *(int*)a * *(int*)b;
}

void int_cross(const void* a, const void* b, void* result) {
    const int* va = (const int*)a;
    const int* vb = (const int*)b;
    int* vr = (int*)result;

    vr[0] = va[1] * vb[2] - va[2] * vb[1];
    vr[1] = va[2] * vb[0] - va[0] * vb[2];
    vr[2] = va[0] * vb[1] - va[1] * vb[0];
}

void int_print(const void* data, FILE* file) {
    fprintf(file, "%d", *(int*)data);
}

void* int_allocate(void) {
    return malloc(sizeof(int));
}

void int_deallocate(void* data) {
    free(data);
}
