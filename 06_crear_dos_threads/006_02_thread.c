// gcc -Wall <file> -o t -lpthread

/*
 * creacion y join de dos thread (cada thread con funcion diferente)
 *
 */
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *work1();
void *work2();

int main(int argc, char **argv)
{

    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, work1, NULL);
    // (1) crear el segundo thread
    pthread_create(&thread2, NULL, work2, NULL);

    pthread_join(thread1, NULL);
    // (2) esperar a que termine el thread2
    pthread_join(thread2, NULL);

    return 0;
}

void *work1()
{
    printf("== Informatica I work1 ==\n");
    // (3) para simular el "paralelismo"
    sleep(3);
    printf("== Fin work1 ==\n");

    return NULL;
}

void *work2()
{
    printf("== Informatica I work2 ==\n");
    // (3) para simular el "paralelismo"
    sleep(3);
    printf("== Fin work2 ==\n");

    return NULL;
}
