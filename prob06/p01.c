// PROGRAMA p01.c
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#define STDERR 2
#define NUMITER 10000

void * thrfunc(void * arg)
{
    int i;
    int nmr = *((int *) arg);
    char buf[2];
    fprintf(stderr, "Starting thread %d\n", nmr);
    sprintf(buf,"%d",nmr);
    for (i = 1; i <= NUMITER; i++) 
        write(STDERR,buf,sizeof(buf));
    return NULL;
}
int main()
{
    pthread_t ta, tb;
    int *nmr = malloc(sizeof(int));
    *nmr = 1;
    pthread_create(&ta, NULL, thrfunc,nmr);
    int *nmr1 = malloc(sizeof(int));
    *nmr1 = 2;
    pthread_create(&tb, NULL, thrfunc,nmr1);
    pthread_join(ta, NULL);
    pthread_join(tb, NULL);
    return 0;
}
