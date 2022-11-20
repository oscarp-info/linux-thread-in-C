#include "buffer.h"

int buffer_init(buffer_t * buffer, int capacity){
    // create dynamic array
    buffer->array = malloc(capacity*sizeof(slot_t));
    
    // TODO...check malloc
    // ...

    buffer->capacity = capacity;
    buffer->size = 0;
    buffer->head = 0;
    buffer->tail = 0;

    return EXIT_SUCCESS;

}

int buffer_insert(buffer_t* buffer, slot_t *slot){
    if ( buffer->size < buffer->capacity){
        buffer->array[buffer->head] = *slot;
        buffer->head = (buffer->head +1 )%buffer->capacity;
        buffer->size++;
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

int buffer_remove(buffer_t* buffer, slot_t * slot){
    if (buffer->size >0){
        *slot = buffer->array[buffer->tail];
        buffer->tail = (buffer->tail +1 )%buffer->capacity;
        buffer->size--;
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

void buffer_destroy(buffer_t * buffer){
    free(buffer->array);

}

void buffer_dump(buffer_t* buffer){
    int i,j;
    
    fprintf(stderr, "\n---- bounded buffer ---\n");
    fprintf(stderr, "size: %d\n", buffer->size);
    fprintf(stderr, "head: %d\n", buffer->head);
    fprintf(stderr, "tail: %d\n", buffer->tail);
    fprintf(stderr, "\n");

    j = buffer->tail;
    for(i=0; i< buffer->size; i++){
        fprintf(stderr, "buffer[%d]: (%d)\n", j, buffer->array[j].value);
        j = (j+1)%buffer->capacity;
    }
    fprintf(stderr, "--------------------------\n");

}