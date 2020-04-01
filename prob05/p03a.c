#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>

#define BUFFER_SIZE 512

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

file_fd = open(argv[1],O_RDONLY,0644);

pid = fork();

if (pid> 0){
    close(fd[0]);
    while ((nr = read(file_fd, buffer, BUFFER_SIZE)) > 0){
        write(fd[1],buffer,BUFFER_SIZE); //enviar o conteudo do ficheiro para a entrada do pipe
        n_itens++;
    }
    close(fd[1]);
}
else{
    close(fd[1]);
    dup2(fd[0],STDIN_FILENO); //ligar o standard input à saida do pipe
    execlp("sort","sort",NULL);
    close(fd[0]);
}

exit(0);
} 