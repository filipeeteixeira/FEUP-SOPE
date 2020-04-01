#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
int v = 0;
void sig_handler(int signal){
    if (signal == SIGUSR1){
        v++;
    }
    else if (signal == SIGUSR2){
        v--;
    }
}
int main(void){
    struct sigaction a;
    a.sa_handler = sig_handler;
    a.sa_flags = 0;
    sigemptyset(&a.sa_mask);
    pid_t p1;
    p1 = fork();
    if(p1 == 0){
        if(sigaction(SIGUSR1, &a, NULL) < 0){
            fprintf(stderr,"Error hun and that's on SIGUSR1\n");
            exit(1);
        }
        if(sigaction(SIGUSR2, &a, NULL) < 0){
            fprintf(stderr,"Error hun and that's on SIGUSR2\n");
            exit(2);
        }
        pause();
        printf("Counter: %d\n", v);
    }
    else if(p1 > 0){
        printf("Start looping...\n");
        for(int i = 0; i < 50; i++){
            if(rand() % 2 == 0){
                kill(p1, SIGUSR1);
            }
            else{
                kill(p1, SIGUSR2);
            }
            sleep(1);
        }
        kill(p1, SIGTERM);
    }
    exit(0);
}