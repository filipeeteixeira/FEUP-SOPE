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
    struct sigaction action;

    action.sa_handler = sigint_handler;

    sigemptyset(&(action.sa_mask));
    sigaddset(&(action.sa_mask),SIGTERM);

    if (sigaction(SIGINT, &action, NULL) == -1)
    {
    fprintf(stderr,"Unable to install SIGINT handler\n");
    exit(1);
    }
    printf("Sleeping for 30 seconds ...\n");
    sleep(30);
    printf("Waking up ...\n");
    exit(0);
}