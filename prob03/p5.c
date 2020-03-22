#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(void) {
 int status;
 pid_t pid, pid1;
 
 pid = fork();
 if (pid > 0){ //pai
    wait(&status);
     printf("friends!\n");
 }
 else{ //filho
     pid1 = fork();
     if(pid1==0){ //filho
         printf("Hello");
     }
     else{ //pai
        wait(&status);
         printf(" my ");
     }
 }
 return 0;
}
