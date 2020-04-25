// PROGRAMA p03.c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 10

void *PrintHello(void *threadnum)
{
    printf("Hello from thread no. %d!\n", *(int *) threadnum);
    pthread_exit(NULL);
}
int main()
{
    pthread_t threads[NUM_THREADS];
    int t;
    int thrArg[NUM_THREADS];
    for(t=0; t< NUM_THREADS; t++){
        printf("Creating thread %d\n", t);
        thrArg[t] = t;
        pthread_create(&threads[t], NULL, PrintHello, &thrArg[t]);
        //pthread_join(threads[t],NULL);
    }
    for(t=0; t< NUM_THREADS; t++){
        pthread_join(threads[t],NULL);
    }

    pthread_exit(NULL);
    //exit(0); //para todos os threads
}