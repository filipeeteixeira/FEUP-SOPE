#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <wait.h>

//utilizador tipo C
int main(int agrc, char *argv[])
{
    char *username = argv[1];

    mkfifo("/tmp/fifo_chg",0660);

    int fd = open("/tmp/fifo_chg",O_WRONLY);

    write(fd,username,strlen(username));

    return 0;
}