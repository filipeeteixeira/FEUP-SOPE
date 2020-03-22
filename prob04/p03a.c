// PROGRAMA p02a.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

bool increasing=true;

void user_handler(int signo){
    if(signo==SIGUSR1)
        increasing=true;
    else if (signo==SIGUSR2)
        increasing=false;
}

int main(void)
{
    int v=0;
    struct sigaction action;
    action.sa_handler = user_handler;
    sigemptyset(&(action.sa_mask));

    sigaction(SIGUSR1, &action, NULL); //o sinal recebido é acrescentado
    sigaction(SIGUSR2, &action, NULL); //automaticamente á mascara.

    while(1){
        printf("%d\n",v);
        if(increasing){
            v++;
        }
        else{
            v--;
        }
        sleep(1);
    }
} 
