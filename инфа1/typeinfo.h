#ifndef TYPEINFO_H
#define TYPEINFO_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void (*add)(const void*, const void*, void*);     
    void (*multiply)(const void*, const void*, void*);
    void (*cross)(const void*, const void*, void*);     // Векторное произведение
    void (*print)(const void*, FILE*);
    void* (*allocate)(void);
    void (*deallocate)(void*);
} TypeInfo;

#endif
