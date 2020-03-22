// PROGRAMA p06.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include<sys/wait.h> 
#include <time.h>

int time_limit;
int alarmflag = 0;

void alarmhandler(int signo)
{
printf("Alarm received ...\n");
alarmflag = 1;
}

void childhandler(int signo){
    int status;
    pid_t pid;
    pid = wait(&status);
    printf("Child %d terminated within %d seconds.\n", pid, time_limit);
    exit(0); 
}

int main(int argc, char * argv[])
{
    pid_t pid;
    time_limit = atoi(argv[1]);
    signal(SIGCHLD,childhandler); //lidar com o sinal quando o processo filho termina/lança SIGCHLD
    signal(SIGALRM, alarmhandler);
    pid = fork();

    if(pid == 0){
        execvp(argv[2], &argv[2]); //processo filho é completamente substituído por prog
    }
    else{
       alarm(time_limit);
       while (! alarmflag) pause(); //espera pelo sinal do alarme
       printf("Program %s exceeded limit of %d seconds!\n",argv[2], time_limit);
       printf("Killing it...\n");
        kill(pid, SIGKILL); 
    }
    exit(0);
}


