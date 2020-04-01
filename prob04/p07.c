// PROGRAMA p07.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include<sys/wait.h> 
#include <errno.h>
#include <string.h>
#include <time.h>

int main(int argc, char * argv[])
{
    pid_t pid, brokenChild;
    int i, status, child_n=0;

    for(i=1;i<argc;i++){
        pid = fork();
        if (pid==0){
            execvp(argv[i],&argv[i]);
        }
    }

    for (i=1;i<argc;i++){
        printf("PARENT: waiting for child %d to finish\n", i); 
        pid = wait(&status);
        if(pid!=-1){
            printf("PARENT: (PROGRAM %d) child with PID=%d terminated with exit code %d\n",i,pid,WEXITSTATUS(status));
            sleep(5);
            brokenChild=pid;
        }
        if (WEXITSTATUS(status)!=0){
            kill(0,SIGTERM);
        }
    }
    exit(0);
}


