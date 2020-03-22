// PROGRAMA p8.c
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <wait.h>

#define BUF_SIZE 256

int main(int argc, char *argv[], char *envp[])
{
 pid_t pid,fatherpid;
 int fd, status, index=0;
 char line[BUF_SIZE];
 char * pch;
 char* commands[10];

 while(1){
    fatherpid=getpid();
    pid=fork();
    if (pid > 0){
        write(STDOUT_FILENO,"minish >",9);
      wait(&status);
      if(WEXITSTATUS(status)==2){
        exit(0);
      }
      else
        printf("(COMMAND EXECUTED!) Child with pid %d terminated\n", pid);
    }
    else{
      fgets(line,BUF_SIZE,stdin);

      if (strncmp(line,"quit",4)==0){
          exit(2);
      }

      pch = strtok (line," ");
      while (pch != NULL)
      {
          commands[index]=pch;
          pch = strtok (NULL, " ");
          index++;
      }
      char *pos;
      if ((pos=strchr(commands[index-1], '\n')) != NULL) //procura por \n
          *pos = '\0'; //remove \n do ultimo argumento

      if (strncmp(commands[index-2],"-o",2)==0){
        fd = open(commands[index-1],O_WRONLY | O_CREAT,0666);
        dup2(fd,STDOUT_FILENO);
        commands[index-2]=NULL;
        execvp(commands[0],commands);
      }
      else{
        execvp(commands[0],commands);
      }
      
    }
 }
    
 exit(0);
} 