/*
 * En un prograna multithreaded, el handler de la señal, se ejecuta en uno de los threads
 * No se puede predecir cual thread es el elegido.
 * En señales que son excepciones, el handler lo ejecuta el thread que la genero
 * kill -34 <pid>
 *
 */

#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h> // sleep
#include <string.h> //memset

void signal_handler(int signal_number);
void set_signal_handler(void);

void *work(void *p);

int main()
{
    pthread_t t1, t2, t3;
    int v1, v2, v3;

    v1 = 1;
    v2 = 2;
    v3 = 3;

    set_signal_handler();
    printf("pid = %d\n", getpid());

    pthread_create(&t1, NULL, work, &(v1));
    pthread_create(&t2, NULL, work, &(v2));
    pthread_create(&t3, NULL, work, &(v3));

    pthread_exit(NULL);
}

void *work(void *p)
{
    int *id = (int *)p;
    while (1)
    {
        printf("work %d tid=%lu\n", *id, pthread_self());
        sleep(1);
    }
    return 0;
}

void signal_handler(int signal_number)
{
    int i;
    for (i = 0; i < 3; i++)
    {
        printf("\tsignal tid=%lu\n", pthread_self());
        sleep(1);
    }
}

void set_signal_handler(void)
{
    struct sigaction action;

    memset(&action, 0, sizeof(action));
    action.sa_handler = &signal_handler;
    sigaction(SIGRTMIN, &action, NULL);
}
