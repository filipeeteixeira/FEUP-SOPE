#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <wait.h>
#include <time.h> 

//utilizador tipo S
int main(int agrc, char *argv[])
{
    int fd;
    char * username = argv[1];
    char message[256];

    fd = open("/tmp/fifo_chg", O_RDONLY);
    time_t secs = 60; // 1 minute

    time_t startTime = time(NULL); //in seconds
    while (time(NULL) - startTime < secs)
    {
        if (read(fd,&message,sizeof(message))>0)
            printf("CHEGOU: %s\n",message);
        //sleep(1);
    }
    
    unlink("/tmp/fifo_chg");
    return 0;
}