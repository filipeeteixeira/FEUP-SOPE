// PROGRAMA p04.c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#define NUM_THREADS 10

void *threadFunc(void *threadnum)
{
    sleep(1);
    printf("Hello my TID is: %ld!\n", pthread_self());
    return threadnum;
}
int main()
{
    pthread_t threads[NUM_THREADS];
    int t;
    void *ret;
    int thrArg[NUM_THREADS];
    for(t=0; t< NUM_THREADS; t++){
        thrArg[t] = t;
        pthread_create(&threads[t], NULL, threadFunc, &thrArg[t]);
        pthread_join(threads[t],&ret);
        printf("Waited for thread %d\n", *((int*)ret));
    }
    exit(0); //para todos os threads
}