/*
 * envio de señales entre threads pthread_kill()
 * solo puede hacerse dentro del mismo proceso
 */

#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h> // sleep
#include <string.h> //memset

void signal_handler(int signo, siginfo_t *info, void *extra);
void set_signal_handler(void);
void set_signal_mask(void);

void *work(void *p);

int main()
{
    pthread_t t1, t2, t3;
    int v1, v2, v3;

    v1 = 1;
    v2 = 2;
    v3 = 3;

    set_signal_handler();

    pthread_create(&t1, NULL, work, &v1);
    pthread_create(&t2, NULL, work, &v2);
    pthread_create(&t3, NULL, work, &v3);

    sleep(3);

    // envio de señales
    pthread_kill(t3, SIGRTMIN);
    // sleep(10);
    pthread_kill(t1, SIGRTMIN);
    // sleep(10);
    pthread_kill(t2, SIGRTMIN);

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

void signal_handler(int signo, siginfo_t *info, void *extra)
{
    printf("\tsignal tid=%lu\n", pthread_self());
}

void set_signal_handler(void)
{
    struct sigaction action;

    // memset(&action, 0, sizeof(action));
    // action.sa_handler = &signal_handler;

    action.sa_flags = SA_SIGINFO;
    action.sa_sigaction = signal_handler;

    sigaction(SIGRTMIN, &action, NULL);
}
