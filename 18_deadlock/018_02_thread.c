#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

struct account
{
    int id;
    int balance;
    pthread_mutex_t mutex_balance;
};
typedef struct account ACCOUNT;

struct transaction
{
    ACCOUNT *from;
    ACCOUNT *to;
    int value;
};
typedef struct transaction TRANSACTION;

void *transfer(void *);

int main(int argc, char *argv[])
{

    pthread_t t1, t2;
    ACCOUNT a, b;
    TRANSACTION from_a_to_b, from_b_to_a;

    a.id = 1;
    a.balance = 100;
    pthread_mutex_init(&a.mutex_balance, NULL);

    b.id = 2;
    b.balance = 500;
    pthread_mutex_init(&b.mutex_balance, NULL);

    from_a_to_b.from = &a;
    from_a_to_b.to = &b;
    from_a_to_b.value = 5;

    from_b_to_a.from = &b;
    from_b_to_a.to = &a;
    from_b_to_a.value = 10;

    pthread_create(&t1, NULL, transfer, &from_a_to_b);
    pthread_create(&t2, NULL, transfer, &from_b_to_a);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&a.mutex_balance);
    pthread_mutex_destroy(&a.mutex_balance);

    printf("== balance 'a' %d == \n", a.balance); // a = 100 -5 + 10 = 105
    printf("== balance 'b' %d == \n", b.balance); // b = 500 +5 - 10 = 495

    return 0;
}

void *transfer(void *args)
{

    TRANSACTION *t = (TRANSACTION *)args;

    if (t->from->id < t->to->id)
    {
        pthread_mutex_lock(&(t->from->mutex_balance));
        usleep(25000);
        pthread_mutex_lock(&(t->to->mutex_balance));
    }
    else
    {
        pthread_mutex_lock(&(t->to->mutex_balance));
        usleep(25000);
        pthread_mutex_lock(&(t->from->mutex_balance));
    }

    // tranferencia
    t->from->balance = t->from->balance - t->value; // falta verificar que tenga saldo por ejemplo
    t->to->balance = t->to->balance + t->value;

    pthread_mutex_unlock(&(t->to->mutex_balance));
    pthread_mutex_unlock(&(t->from->mutex_balance));

    return NULL;
}
