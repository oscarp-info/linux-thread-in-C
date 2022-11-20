/*
 * detached (threads)
 *  verificar que si uun thread esta detached, se liberarn los recursos
 *
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define THREAD_NUM 1

int *ptr = NULL;

void *work(void *args)
{
    sleep(1);
    ptr = malloc(sizeof(int));
    *ptr = 12345;
    printf("End thread\n");
}

int main(int argc, char *argv[])
{
    int i;
    pthread_t th[THREAD_NUM];

    // por default los threads son joinable
    // pero si a un thread lo detachamos, lo que estamos haciendo es que no permita join
    // al querer hacer un join nos da error
    // y en este caso no veremos los printf de los threads ya que al terminar main
    // terminan lso threads (no tienen join)
    for (i = 0; i < THREAD_NUM; i++)
    {
        pthread_create(&th[i], NULL, work, NULL);
        // pthread_detach(th[i]);
    }
    for (i = 0; i < THREAD_NUM; i++)
    {
        if (pthread_join(th[i], NULL) != 0)
        {
            printf("Failed to join thread\n");
        }
    }

    printf("El valor int es %d\n", *ptr);
    free(ptr);

    // return 0;

    // puedo esperarlos (pero no con join!)
    pthread_exit(0);
}