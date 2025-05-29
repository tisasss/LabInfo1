#ifndef VECTOR_H
#define VECTOR_H

#include "typeinfo.h"

typedef struct {
    void* data;
    TypeInfo* type_info;
} VectorElement;

typedef struct {
    VectorElement* elements;
    unsigned int size;
} Vector;

Vector* create_vector(unsigned int size);
void free_vector(Vector* vec);
void set_element(Vector* vec, unsigned int index, void* data, TypeInfo* type_info);
Vector* vector_add(Vector* vec1, Vector* vec2);
void* scalar_product(Vector* vec1, Vector* vec2);
Vector* vector_cross(Vector* vec1, Vector* vec2);
void print_vector_to_file(FILE* file, Vector* vec);

#endif
