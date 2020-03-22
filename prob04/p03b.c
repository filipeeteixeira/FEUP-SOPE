// PROGRAMA p02a.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

bool increasing=true;

void user_handler(int signo){
    if(signo==SIGUSR1)
        increasing=true;
    else if (signo==SIGUSR2)
        increasing=false;
}

int main(void)
{
    int pid,v=0;
    struct sigaction action;
    action.sa_handler = user_handler;
    sigemptyset(&(action.sa_mask));

    sigaction(SIGUSR1, &action, NULL); //o sinal recebido é acrescentado
    sigaction(SIGUSR2, &action, NULL); //automaticamente á mascara.

    if((pid = fork()) > 0) {
        int signo;
        srand(time(NULL));
        for (int i = 0; i<50;i++){
            if (rand()% 2){
                signo = SIGUSR1;
            }
            else{
                signo = SIGUSR2;
            }
            kill(pid,signo); //pid do filho
            sleep(1);
        }
    } else { //child
        for (int i = 0; i<50;i++){
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
    exit(0);
} 
