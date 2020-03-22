// PROGRAMA p8.c
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

int main(int argc, char *argv[], char *envp[])
{
 pid_t pid,childpid;
 int status;
 if (argc != 2) {
    printf("usage: %s dirname\n",argv[0]);
    exit(1);
 }
 pid=fork();
 if (pid > 0){
      printf("My child is going to execute command\"ls -laR %s\"\n", argv[1]);
      childpid=wait(&status);
      printf("CHild done executing!\n");
      if (WIFEXITED(status)) //terminou normalmente
            printf("Exited with status %d\n", WEXITSTATUS(status));

      else if (WIFSIGNALED(status)) //terminou anormalmente pq recebeu um sinal q nao tratou
            printf("Exited with status %d\n", WEXITSTATUS(status));
    }
    
    else if (pid == 0){
        
        execlp("ls","ls", "-laR", argv[1], NULL);
        printf("Command not executed !\n");      
        exit(1);    
    }    
    exit(0); 
}
