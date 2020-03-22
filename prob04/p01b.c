// PROGRAMA p01a.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void sigint_handler(int signo)
{
 printf("In SIGINT handler ...\n");
}
int main(void)
{
int seconds_left;
 if (signal(SIGUSR1,sigint_handler) < 0)
 {
 fprintf(stderr,"Unable to install SIGINT handler\n");
 exit(1);
 }

 printf("Sleeping for 30 seconds ...\n");
 
 seconds_left = sleep(30);
    
    while (seconds_left != 0) {
        seconds_left = sleep(seconds_left); //sleep retorna o numero de segundos que faltam
    } 

 printf("Waking up ...\n");
 exit(0);
}