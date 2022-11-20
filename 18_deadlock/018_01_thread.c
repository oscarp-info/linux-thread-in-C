/*
 * deadlock (simple)
 *
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

// recurso compartido
int counter = 50;
// mutex para el recurso compartido
pthread_mutex_t mutex_counter;

void *work(void *args);

int main(int argc, char *argv[])
{
    int i;
    pthread_t t1, t2;

    // sin prevenir el deadlock
    pthread_mutex_init(&mutex_counter, NULL);

    // para prevenir el deadlock
    // pthread_mutexattr_t attr;
    // pthread_mutexattr_init(&attr);
    // pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);
    // pthread_mutex_init(&mutex_counter, &attr);

    pthread_create(&t1, NULL, work, NULL);
    pthread_create(&t2, NULL, work, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&mutex_counter);

    printf("counter: %d\n", counter);

    return 0;
}

void *work(void *args)
{
    pthread_mutex_lock(&mutex_counter);
    // deadlock!
    pthread_mutex_lock(&mutex_counter);
    counter += 10;
    pthread_mutex_unlock(&mutex_counter);
}