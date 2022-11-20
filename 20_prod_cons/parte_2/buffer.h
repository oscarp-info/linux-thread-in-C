#ifndef _BUFFER_H
#define _BUFFER_H

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int value;
} slot_t;

typedef struct {
    slot_t *array;
    int capacity;
    int size;
    int head;
    int tail;
}buffer_t;

// API's para mi buffer
int buffer_init(buffer_t *, int capacity);
int buffer_insert(buffer_t*, slot_t *);
int buffer_remove(buffer_t*, slot_t *);
void buffer_destroy(buffer_t *);
void buffer_dump(buffer_t*);



#endif