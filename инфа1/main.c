#include "vector.h"
#include "int_info.h"
#include "double_info.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Vector* read_vector(FILE* file, TypeInfo* type_info, unsigned int size) {
    Vector* vec = create_vector(size);
    for (int i = 0; i < size; i++) {
        void* data = type_info->allocate();
        if (type_info == &TypeInfoInt) {
            fscanf(file, "%d", (int*)data);
        } else if (type_info == &TypeInfoDouble) {
            fscanf(file, "%lf", (double*)data);
        }
        set_element(vec, i, data, type_info);
    }
    return vec;
}

int compare_vectors(Vector* vec1, Vector* vec2) {
    if (vec1->size != vec2->size) return 0;

    for (unsigned int i = 0; i < vec1->size; i++) {
        if (vec1->elements[i].type_info != vec2->elements[i].type_info) return 0;

        if (vec1->elements[i].type_info == &TypeInfoInt) {
            if (*(int*)vec1->elements[i].data != *(int*)vec2->elements[i].data) return 0;
        } else if (vec1->elements[i].type_info == &TypeInfoDouble) {
            if (*(double*)vec1->elements[i].data != *(double*)vec2->elements[i].data) return 0;
        }
    }
    return 1;
}

int main(void) {
    FILE* input = fopen("/Users/alexandratikhonova/Documents/jgy/nhfg/подготовка к лабе/инфа1/инфа1/input.txt", "r");
    FILE* output = fopen("/Users/alexandratikhonova/Documents/jgy/nhfg/подготовка к лабе/инфа1/инфа1/output.txt", "w");

    if (!input || !output) {
        perror("Failed to open file");
        return 1;
    }

    int operation;
    fscanf(input, "%d", &operation);

    char data_type[10];
    fscanf(input, "%s", data_type);

    TypeInfo* type_info = NULL;
    if (strcmp(data_type, "int") == 0) {
        type_info = &TypeInfoInt;
    } else if (strcmp(data_type, "double") == 0) {
        type_info = &TypeInfoDouble;
    } else {
        fprintf(output, "Error: Unknown data type '%s'. Use 'int' or 'double'.\n", data_type);
        fclose(input);
        fclose(output);
        return 1;
    }

    unsigned int size;
    fscanf(input, "%d", &size);

    Vector* vec1 = read_vector(input, type_info, size);
    Vector* vec2 = read_vector(input, type_info, size);
    Vector* expected_result = read_vector(input, type_info, size);

    Vector* result = NULL;
    void* scalar_result = NULL;

    switch (operation) {
        case 1: {  // Векторное сложение
            result = vector_add(vec1, vec2);
            if (result) {
                fprintf(output, "Result of vector addition: ");
                print_vector_to_file(output, result);

                if (compare_vectors(result, expected_result)) {
                    fprintf(output, "Test passed.\n");
                } else {
                    fprintf(output, "Error: Result does not match expected output.\n");
                }
            } else {
                fprintf(output, "Error: Vectors are incompatible.\n");
            }
            break;
        }
        case 2: {  // Скалярное произведение
            scalar_result = scalar_product(vec1, vec2);
            if (scalar_result) {
                fprintf(output, "Result of scalar product: ");
                if (type_info == &TypeInfoInt) {
                    fprintf(output, "%d\n", *(int*)scalar_result);
                } else if (type_info == &TypeInfoDouble) {
                    fprintf(output, "%f\n", *(double*)scalar_result);
                }

                if (type_info == &TypeInfoInt) {
                    if (*(int*)scalar_result == *(int*)expected_result->elements[0].data) {
                        fprintf(output, "Test passed.\n");
                    } else {
                        fprintf(output, "Error: Result does not match expected output.\n");
                    }
                } else if (type_info == &TypeInfoDouble) {
                    if (*(double*)scalar_result == *(double*)expected_result->elements[0].data) {
                        fprintf(output, "Test passed.\n");
                    } else {
                        fprintf(output, "Error: Result does not match expected output.\n");
                    }
                }
            } else {
                fprintf(output, "Error: Vectors are incompatible.\n");
            }
            break;
        }
//        case 3: {
//                    result = vector_cross(vec1, vec2);
//                    if (result) {
//                        fprintf(output, "Result of vector cross product: ");
//                        print_vector_to_file(output, result);
//
//                        if (compare_vectors(result, expected_result)) {
//                            fprintf(output, "Test passed.\n");
//                        } else {
//                            fprintf(output, "Error: Result does not match expected output.\n");
//                        }
//                    } else {
//                        fprintf(output, "Error: Vectors are incompatible or not 3D.\n");
//                    }
//                    break;
//                }
        default:
            fprintf(output, "Error: Unknown operation.\n");
            break;
    }

    free_vector(vec1);
    free_vector(vec2);
    free_vector(expected_result);
    if (result) free_vector(result);
    if (scalar_result) type_info->deallocate(scalar_result);

    fclose(input);
    fclose(output);

    return 0;
}

