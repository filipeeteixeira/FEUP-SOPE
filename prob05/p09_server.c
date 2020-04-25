#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/file.h>
#include <wait.h>

void parse_commands(char string[64], char* arr[256]) {
  int i = 0;
  int init_size = strlen(string);
	char delim[] = " ";

	char *ptr = strtok(string, delim);

	while(ptr != NULL)
	{
		arr[i]=ptr;
		ptr = strtok(NULL, delim);
    i++;
	}
  arr[i]=NULL;
}

int readline(int fd, char *str) {
  int n;
  do {
      n = read(fd, str, 1);
  } while (n > 0 && *str++ != '\0');
  *(str-2)='\0';
  return (n > 0);
}

int main(void)
{
    int fd,fd1;
    char message[256];
    
    mkfifo("/tmp/fifo.s",0660);
    mkfifo("tmp/fifo.s1",0660);

    fd = open("/tmp/fifo.s",O_RDONLY);

    while(1){
        while(readline(fd,message)) printf("%s",message);
        
        char* command[256];
        parse_commands(message, command);
        pid_t pid;
        if ((pid = fork()) == 0) {  /* child */
          int filefd = open("file.txt", O_WRONLY | O_CREAT, 0666);
          
          if(execvp(command[0], command) < 0){
                printf("Error in execution.");
                return(0);
            }
          sleep(10);
          exit(0);
        }
        else if (pid < 0) {
          printf("Error on fork\n");
          exit(1);
        }

        waitpid(pid,NULL,0);

        char fileData[256];
        FILE *f = fopen("/tmp/file.txt", "rb");
        fgets(fileData,256,f);
        fclose(f);

        int client = open("/tmp/fifo.s1", O_WRONLY);
        write(client, fileData, strlen(fileData) + 1);
        close(client);
        }

  close(fd);
  unlink("/tmp/fifo.s"); unlink("/tmp/fifo.s1");
  return 0;
} 
