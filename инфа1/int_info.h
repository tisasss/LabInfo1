#ifndef INT_INFO_H
#define INT_INFO_H

#include "typeinfo.h"

void int_add(const void* a, const void* b, void* result);
void int_multiply(const void* a, const void* b, void* result);
void int_cross(const void* a, const void* b, void* result);
void int_print(const void* data, FILE* file);
void* int_allocate();
void int_deallocate(void* data);

static TypeInfo TypeInfoInt = {
    .add = int_add,
    .multiply = int_multiply,
    .cross = int_cross,
    .print = int_print,
    .allocate = int_allocate,
    .deallocate = int_deallocate
};

#endif
