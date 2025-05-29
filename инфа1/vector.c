#include "vector.h"
#include <stdio.h>
#include <stdlib.h>

Vector* create_vector(unsigned int size) {
    Vector* vec = (Vector*)malloc(sizeof(Vector));
    vec->elements = (VectorElement*)malloc(size * sizeof(VectorElement));
    vec->size = size;
    return vec;
}

void free_vector(Vector* vec) {
    for (unsigned int i = 0; i < vec->size; i++) {
        vec->elements[i].type_info->deallocate(vec->elements[i].data);
    }
    free(vec->elements);
    free(vec);
}

void set_element(Vector* vec, unsigned int index, void* data, TypeInfo* type_info) {
    vec->elements[index].data = data;
    vec->elements[index].type_info = type_info;
}

Vector* vector_add(Vector* vec1, Vector* vec2) {
    if (vec1->size != vec2->size) return NULL;

    Vector* result = create_vector(vec1->size);
    for (int i = 0; i < vec1->size; i++) {
        if (vec1->elements[i].type_info != vec2->elements[i].type_info) return NULL;

        result->elements[i].data = vec1->elements[i].type_info->allocate();
        vec1->elements[i].type_info->add(vec1->elements[i].data, vec2->elements[i].data, result->elements[i].data);
        result->elements[i].type_info = vec1->elements[i].type_info;
    }
    return result;
}

void* scalar_product(Vector* vec1, Vector* vec2) {
    if (vec1->size != vec2->size) return NULL;

    void* result = vec1->elements[0].type_info->allocate();
    vec1->elements[0].type_info->multiply(vec1->elements[0].data, vec2->elements[0].data, result);

    for (int i = 1; i < vec1->size; i++) {
        if (vec1->elements[i].type_info != vec2->elements[i].type_info) return NULL;

        void* product = vec1->elements[i].type_info->allocate();
        vec1->elements[i].type_info->multiply(vec1->elements[i].data, vec2->elements[i].data, product);

        void* temp = vec1->elements[i].type_info->allocate();
        vec1->elements[i].type_info->add(result, product, temp);
        vec1->elements[i].type_info->deallocate(result);
        vec1->elements[i].type_info->deallocate(product);
        result = temp;
    }
    return result;
}

//Vector* vector_cross(Vector* vec1, Vector* vec2) {
//    if (vec1->size != 3 || vec2->size != 3) return NULL;
//    
//    Vector* result = create_vector(3);
//    for (int i = 0; i < 3; i++) {
//        result->elements[i].data = vec1->elements[i].type_info->allocate();
//    }
//    vec1->elements[0].type_info->cross(vec1->elements, vec2->elements, result->elements);
//    result->elements[0].type_info = vec1->elements[0].type_info;
//    return result;
//}

void print_vector_to_file(FILE* file, Vector* vec) {
    for (int i = 0; i < vec->size; i++) {
        vec->elements[i].type_info->print(vec->elements[i].data, file);
        fprintf(file, " ");
    }
    fprintf(file, "\n");
}
