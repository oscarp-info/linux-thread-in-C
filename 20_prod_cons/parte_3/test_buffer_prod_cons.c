// gcc  -Wall -o test_prod_cons test_buffer_prod_cons.c buffer.c -lpthread

#include "buffer.h"
#include <pthread.h>
#include <unistd.h>


#define PRODUCER    10
#define CONSUMER    10

void random_ms_sleep(int min, int max);

buffer_t buffer;
pthread_mutex_t mutex;


void * producer(void*);
void * consumer(void*);

int main(){
    pthread_t tp[PRODUCER];
    pthread_t tc[CONSUMER];
    int i;

    buffer_init(&buffer, 10);
    pthread_mutex_init(&mutex, NULL);

    for(i=0;i<PRODUCER;i++){
        pthread_create(&tp[i], NULL, producer, NULL);
        pthread_detach(tp[i]);
    }
    for(i=0;i<CONSUMER;i++){
        pthread_create(&tc[i], NULL, consumer, NULL);
        pthread_detach(tc[i]);
    }

    while(1){
        sleep(3);
        buffer_dump(&buffer);
    }

    buffer_destroy(&buffer);
    pthread_mutex_destroy(&mutex);

    return 0;
}

void random_ms_sleep(int min, int max)
{
    usleep(1000 * (rand() % (max + 1 - min) + min));
}


void * producer(void* args){
    slot_t slot;
    int result;

    while(1){
        random_ms_sleep(100,500);
        slot.value = rand()%100;
        pthread_mutex_lock(&mutex);
        result = buffer_insert(&buffer, &slot);
        if (result != 0){
            fprintf(stderr, "producer:: skipped and spent cpu!\n");
        }
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void * consumer(void* args){
    slot_t slot;
    int result;

    while(1){
        random_ms_sleep(100,500);
        pthread_mutex_lock(&mutex);
        result = buffer_remove(&buffer, &slot);
        if (result != 0){
            fprintf(stderr, "consumer:: spent cpu!\n");
        }

        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

