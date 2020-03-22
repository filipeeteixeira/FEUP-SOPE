// PROGRAMA p8.c
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[])
{
 pid_t pid;
 if (argc != 2) {
    printf("usage: %s dirname\n",argv[0]);
    exit(1);
 }
 pid=fork();
 if (pid > 0)
    printf("My child is going to execute command\"ls -laR %s\"\n", argv[1]);
 else if (pid == 0){
    //execlp("ls","ls","-laR",argv[1],NULL); //8a

    //execl("/bin/ls","ls","-laR",argv[1],NULL); 8b

    char* commands[4];
    commands[0]="ls";
    commands[1]="-laR";
    commands[2]=argv[1];
    commands[3]=NULL;
    //execvp("ls",commands); //8c

    //execv("/bin/ls",args);        //8d)

    //execve("/bin/ls",args, envp);   //8e)

    printf("Command not executed !\n");
    exit(1);
 }
 exit(0);
} 
