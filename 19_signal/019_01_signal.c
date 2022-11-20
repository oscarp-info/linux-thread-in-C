/*
 * kill -l
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

int main()
{
    set_signal_handler();
    printf("pid = %d\n", getpid());
    while (1)
    {
        pause();
    }
}

void signal_handler(int signal_number)
{
    int i;
    for (i = 0; i < 3; i++)
    {
        printf("\tsignal(%d)\n", i);
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
