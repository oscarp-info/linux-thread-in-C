/*
 * control de errores a la hora de crear o hacer join de threads
 */
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *work();

int main(int argc, char **argv)
{

    pthread_t thread1, thread2;

    if (pthread_create(&thread1, NULL, work, NULL) != 0)
        return 1;

    if (pthread_create(&thread2, NULL, work, NULL) != 0)
        return 2;

    if (pthread_join(thread1, NULL) != 0)
        return 3;

    if (pthread_join(thread2, NULL) != 0)
        return 4;

    return 0;
}

void *work()
{

	printf("== Informatica I ==\n");

    return NULL;
}
