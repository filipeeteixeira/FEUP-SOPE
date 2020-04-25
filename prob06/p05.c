// PROGRAMA p05.c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#define NUM_THREADS 10

typedef struct numbs{
    double n1, n2;
}Ns;

void *sum(void *nums)
{
    Ns *ns = (Ns *) nums;
    double *sum = malloc(sizeof(double));
    *sum = (*ns).n1+(*ns).n2;
    return sum;
}

void *sub(void *nums)
{
    double *arr = (double *) nums;
    double *sub = malloc(sizeof(double));
    *sub = arr[0]-arr[1];
    printf("sub: %f\n",*sub);
    return sub;
}

void *mul(void *nums)
{
    double *arr = (double *) nums;
    double *mul = malloc(sizeof(double));
    *mul = arr[0]*arr[1];
    printf("mul: %f\n",*mul);
    return mul;
}

void *divv(void *nums)
{
    double *arr = (double *) nums;
    double *divv = malloc(sizeof(double));
    *divv = arr[0]/(double)arr[1];
    printf("div: %f\n",*divv);
    return div;
}

int main()
{
    pthread_t ta, tb, tc, td;
    void *ret;

    double n1, n2;
    printf("Insert number 1:\n");
    scanf("%lf",&n1);
    printf("Insert number 2:\n");
    scanf("%lf",&n2);

    double array[2]={n1,n2};

    Ns ns;
    ns.n1=n1;
    ns.n2=n2;

    pthread_create(&ta, NULL, sum, &ns);
    pthread_create(&tb, NULL, sub, &array);
    pthread_create(&tc, NULL, mul, &array);
    pthread_create(&td, NULL, divv, &array);
    pthread_join(ta,&ret);
    printf("sum(main): %f\n",*((double*)ret));
    pthread_join(tb,NULL);
    pthread_join(tc,NULL);
    pthread_join(td,NULL);
    exit(0); //para todos os threads
}