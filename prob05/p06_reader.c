// PROGRAMA p06_reader.c
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <wait.h>

int readline(int fd, char *str);
int main(void)
{
    int fd;
    char str[100];
    mkfifo("/tmp/myfifo",0660);
    fd=open("/tmp/myfifo",O_RDONLY);
    
    while(readline(fd,str)) printf("%s",str);
    close(fd);
    return 0;
}
int readline(int fd, char *str)
{
    int n;
    do {
        n = read(fd,str,1);
        printf("%c\n",*str);
    } while (n>0 && *str++ != '\0');
    return (n>0);
}

//The result is undefined if the flag O_RDWR is applied to a FIFO
//o open bloqueia ate que haja uma chamada open complementar