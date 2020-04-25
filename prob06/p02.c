// PROGRAMA p01.c
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#define STDERR 2

int N = 50000;

void * thrfunc(void * arg)
{
    int *counter=malloc(sizeof(*counter));
    fprintf(stderr, "Starting thread %s\n",(char*) arg);
    while (N>0){
        write(STDERR,"0",1);
        N--;
        *counter+=1;
    }
    return (counter);
}

int main()
{
    pthread_t ta, tb;
    void * ret1, *ret2;
    pthread_create(&ta, NULL, thrfunc,"0");
    pthread_create(&tb, NULL, thrfunc,"0");
    pthread_join(ta, &ret1);
    pthread_join(tb, &ret2);

    printf("\n%d\n",*((int*)ret1));  
    printf("%d\n",*((int*)ret2)); 
    return 0;
}

/*N decrementado pelas duas threads 50005 vezes (problemas de sincronização)*/