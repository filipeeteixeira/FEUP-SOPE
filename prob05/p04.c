#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <wait.h>
#define WRITE       1
#define READ        0
int main(int agrc, char *argv[])
{
    char buffer[255];
    int fd1[2], fd[2], fd2[2], file_fd, nr, n_itens=0;
    pid_t pid, pid1;
    char * line = NULL;
    size_t len = 0;
    int status;
    if (pipe(fd) < 0) {
        fprintf(stderr, "pipe error\n");
        exit(1);
    }
    if (pipe(fd1) < 0) {
        fprintf(stderr, "pipe error\n");
        exit(1);
    }
    pid = fork();
    if (pid> 0){
        close(fd[READ]);
        dup2(fd[WRITE],STDOUT_FILENO);
        execlp("ls", "ls", argv[1], "-laR", NULL);
        
    }
    else if (pid==0){
        sleep(5);
        close(fd[WRITE]);
        close(fd1[WRITE]);
        pid1 = fork();
        if (pid1==0){
            dup2(fd1[READ],STDIN_FILENO);
            execlp("sort","sort",NULL);
            close(fd1[READ]);
            exit(0);
        } else {
            waitpid(pid1,&status, 0);
            close(fd1[READ]);
            dup2(fd[READ],STDIN_FILENO);
            dup2(fd1[WRITE],STDOUT_FILENO);
            execlp("grep","grep",argv[2],NULL);
            exit(0);
        }
        
    }
    waitpid(pid, &status, 0);
    exit(0);
}