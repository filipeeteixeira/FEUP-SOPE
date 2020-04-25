#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/file.h>
#include <wait.h>

int readlines(int fd, char *str) {
  int n;
  do {
      n = read(fd, str, 1);
  } while (n > 0 && *str++ != '\0');
  return (n > 0);
}

int main(void)
{
    int n1, n2, ints[2], fd, fd1;
    char command[256];

    write(STDOUT_FILENO,"Insert command: ",17);
    fgets(command,256,stdin);

    do{
      fd = open("/tmp/fifo.s",O_WRONLY);
      if (fd==-1){
        printf("Waiting for server..\n");
        sleep(1);
      } 
    }while(fd==-1);
    
    write(fd,command,strlen(command)+1); //+1 to include /0

    int client = open("/tmp/fifo.s1", O_RDONLY | O_NONBLOCK);

    char buffer[256];
    while (readlines(client, buffer)) printf("%s\n", buffer);
    close(client);
  
  return 0;
}
