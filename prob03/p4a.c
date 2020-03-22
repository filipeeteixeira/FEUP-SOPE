#include <stdio.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/wait.h>

int main(void) {
    pid_t pid, childpid;
    int status;
 if(fork() > 0) {
    childpid = wait(&status);
    printf(" world !\n");
 } else {
    printf("Hello");
 }
    return 0;
}
