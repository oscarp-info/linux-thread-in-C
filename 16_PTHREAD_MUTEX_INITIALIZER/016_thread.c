/*
 * PTHREAD_MUTEX_INITIALIZER (MACRO, initializes a static mutex with default attributes,  no error checking is performed)
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define HACER

// declarar el mutex
// pthread_mutex_t mutex;

// declarar e inicializar
pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER;

// para simular un recurso compartido, primer version como variable global
int shared_resource = 0;
int read_shared_resource(void);
void write_shared_resource(int value);

// funcion que realiza un tarea sobre el recurso compartido
void *work(void *);

int main(int argc, char **argv)
{
    pthread_t t1, t2;
    int before, after;
    int valor1, valor2;

    // initialize the mutex
    // pthread_mutex_init(&mutex, NULL);

    before = read_shared_resource();
    printf("before: %d\n", before);

    valor1 = 100;
    valor2 = 200;
    pthread_create(&t1, NULL, work, (void *)&valor1);
    pthread_create(&t2, NULL, work, (void *)&valor2);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // destroy the mutex
    // pthread_mutex_destroy(&mutex);

    after = read_shared_resource();
    printf("after: %d\n", after);

    return 0;
}

void *work(void *arg)
{
    // simulamos una accion sobre el recurso compartido
    int valor;

    pthread_mutex_lock(&my_mutex);

    // zona critica == start ==
    // para proteger recursos del acceso concurrente
    valor = read_shared_resource();
    valor += *((int *)arg);
    write_shared_resource(valor);
    // zona critica == end ==

    pthread_mutex_unlock(&my_mutex);

    return NULL;
}

/*
 * API's para interactual con el recurso compartido
 */

int read_shared_resource(void)
{
    usleep(250000);
    return shared_resource;
}

void write_shared_resource(int value)
{
    usleep(250000);
    shared_resource = value;
}
