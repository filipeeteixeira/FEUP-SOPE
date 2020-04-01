#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>

#define BUFFER_SIZE 512
#define WRITE       1
#define READ        0

int main(int agrc, char *argv[])
{
char buffer[255];
int fd[2],file_fd, nr, n_itens=0;
pid_t pid;
char * line = NULL;
size_t len = 0;

if (pipe(fd) < 0) {
    fprintf(stderr, "pipe error\n");
    exit(1);
    }

pid = fork();

if (pid> 0){
    close(fd[READ]);
    dup2(fd[WRITE],STDOUT_FILENO);
    execlp("cat","cat",argv[1],NULL);
}
else{
    close(fd[WRITE]);
    dup2(fd[READ],STDIN_FILENO); //ligar o standard input à saida do pipe
    execlp("sort","sort",NULL);
}

exit(0);
} 