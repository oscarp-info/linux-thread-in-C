/*
 * pthread_t vs gettid (linux specific, kernel mode)
 *
 *
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/syscall.h>

#define THREAD_NUM 2

void *work(void *args);

int main(int argc, char *argv[])
{
    pthread_t arr_t[THREAD_NUM];
    int i;

    printf("main:: main pid: %d\n", getpid());
    printf("main:: main tid: %lu\n", pthread_self());
    printf("main:: main tid(kernel): %d\n", (pid_t)syscall(SYS_gettid)); // linux specific!

    for (i = 0; i < THREAD_NUM; i++)
    {
        pthread_create(&arr_t[i], NULL, work, NULL);
        printf("main:: work tid: %lu\n", arr_t[i]);
    }

    for (i = 0; i < THREAD_NUM; i++)
    {
        pthread_join(arr_t[i], NULL);
    }

    return 0;
}

void *work(void *args)
{
    printf("\twork:: main pid: %d\n", getpid());
    printf("\twork:: work tid: %lu\n", pthread_self());
    printf("\twork:: work tid: %d\n", (pid_t)syscall(SYS_gettid)); // linux specific!

    return NULL;
}
