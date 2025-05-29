#include "double_info.h"
#include <stdio.h>
#include <stdlib.h>

void double_add(const void* a, const void* b, void* result) {
    *(double*)result = *(double*)a + *(double*)b;
}

void double_multiply(const void* a, const void* b, void* result) {
    *(double*)result = *(double*)a * *(double*)b;
}

void double_cross(const void* a, const void* b, void* result) {
    const double* va = (const double*)a;
    const double* vb = (const double*)b;
    double* vr = (double*)result;

    vr[0] = va[1] * vb[2] - va[2] * vb[1];
    vr[1] = va[2] * vb[0] - va[0] * vb[2];
    vr[2] = va[0] * vb[1] - va[1] * vb[0];
}

void double_print(const void* data, FILE* file) {
    fprintf(file, "%f", *(double*)data);
}

void* double_allocate() {
    return malloc(sizeof(double));
}

void double_deallocate(void* data) {
    free(data);
}
