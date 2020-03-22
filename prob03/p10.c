// PROGRAMA p8.c
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <wait.h>

int main(int argc, char *argv[], char *envp[])
{
 pid_t pid;
 int fd, status;
 if (argc != 2 && argc != 3) {
    printf("usage: %s dirname\n",argv[0]);
    exit(1);
 }
 pid=fork();
 if (pid > 0){
    printf("My child is going to execute command\"ls -laR %s\"\n", argv[1]);
   waitpid(pid, &status, 0);
   printf("Child with pid %d terminated\n", pid);
 }
 else if (pid == 0){
    if(argc==3){
       fd = open(argv[2],O_WRONLY | O_CREAT,0666);
          
       dup2(fd,STDOUT_FILENO);
    }

    char* commands[4];
    commands[0]="ls";
    commands[1]="-laR";
    commands[2]=argv[1];
    commands[3]=NULL;
    execvp("ls",commands);

    printf("Command not executed !\n");
    exit(1);
 }
    
 exit(0);
} 
