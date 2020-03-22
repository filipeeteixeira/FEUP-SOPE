// PROGRAMA p06.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include<sys/wait.h> 
#include <time.h>

int main(int argc, char * argv[])
{
    int elapsed_time = 0;
    while(elapsed_time<30){
        printf("RUNNING PROG\n");
        sleep(5);
        elapsed_time+=5;
    }
    exit(0);
}


