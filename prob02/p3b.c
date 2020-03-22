//FOLHA 2 - p2b.c
//FILE COPY
//USAGE: copy source destination

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define BUFFER_SIZE 512

int main(int argc, char *argv[])
{
 int fd1, fd2, nr, nw;
 unsigned char buffer[BUFFER_SIZE];

 if (argc == 2) {
  fd1 = open(argv[1], O_RDONLY); //fd1 é o descritor do ficheiro
  if (fd1 == -1) {
    perror(argv[1]);
    return 2;
  }

  while ((nr = read(fd1, buffer, BUFFER_SIZE)) > 0)
    if ((nw = write(STDOUT_FILENO, buffer, nr)) <= 0 || nw != nr) {
      perror(argv[2]);
      close(fd1);
      close(fd2);
      return 4;
    }
    close(fd1);
    close(fd2);
    return 0;
 }

 else if (argc == 3) {
  fd1 = open(argv[1], O_RDONLY); //fd1 é o descritor do ficheiro
  if (fd1 == -1) {
    perror(argv[1]);
    return 2;
  }
  fd2 = open(argv[2], O_WRONLY); //fd1 é o descritor do ficheiro
  if (fd2 == -1) {
    perror(argv[2]);
    return 2;
  }
  dup2(fd2,STDOUT_FILENO); //redirecionamento de STDOUT-FILENO para fd2
  while ((nr = read(fd1, buffer, BUFFER_SIZE)) > 0)
    if ((nw = write(STDOUT_FILENO, buffer, nr)) <= 0 || nw != nr) {
      perror(argv[2]);
      close(fd1);
      close(fd2);
      return 4;
    }
    close(fd1);
    close(fd2);
    return 0;
 }
}