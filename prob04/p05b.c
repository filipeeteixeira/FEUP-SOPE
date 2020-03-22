// PROGRAMA p02a.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include<sys/wait.h> 
#include <time.h>

void childhandler(int signo)
{
    int status;
    pid_t pid;
    pid = wait(&status);
    if (pid ==-1){
        printf("All childs done\n"); //never executed 
    }
    printf("Child %d terminated.\n", pid);
}

int main(void)
{
    pid_t pid;
    int i, n, status;
    signal(SIGCHLD,childhandler); //ignore SIGCHILD
    for (i=1; i<=10; i++) {
        pid=fork(); 

        if (pid == 0){
            printf("CHILD no. %d (PID=%d) working ... \n",i,getpid());
            sleep(15); // child working ...
            printf("CHILD no. %d (PID=%d) exiting ... \n",i,getpid());
            exit(0);
        }
    }
    
    printf("PARENT: working hard ...\n");
    n=30; 
        while((n=sleep(n))!=0);
    exit(0);
    printf("PARENT: end of task\n");
} 

//esta opção não é viável pq ignora processos zombie


