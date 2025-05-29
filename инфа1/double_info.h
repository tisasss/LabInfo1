#ifndef DOUBLE_INFO_H
#define DOUBLE_INFO_H

#include "typeinfo.h"

void double_add(const void* a, const void* b, void* result);
void double_multiply(const void* a, const void* b, void* result);
void double_cross(const void* a, const void* b, void* result);
void double_print(const void* data, FILE* file);
void* double_allocate();
void double_deallocate(void* data);

static TypeInfo TypeInfoDouble = {
    .add = double_add,
    .multiply = double_multiply,
    .cross = double_cross,
    .print = double_print,
    .allocate = double_allocate,
    .deallocate = double_deallocate
};

#endif

