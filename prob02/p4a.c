#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define BUFFER_SIZE 512

int main(int argc, char *argv[])
{
    int fd, nr, nw, nr1, nw1;
    unsigned char buffer[BUFFER_SIZE];

    if (argc != 2) {
        printf("Usage: %s <destination>\n", argv[0]);
        return 1;
    }

    fd = open(argv[1], O_WRONLY | O_CREAT | O_EXCL, 0644);
    if (fd == -1) {
        perror(argv[1]);
        return 2;
    }
    while(1){
        write(STDOUT_FILENO,"Name (CTR-D to end): ", 22);
        nr = read(STDIN_FILENO,buffer,BUFFER_SIZE);
        if ( nr == 0){
            break;
        }

        nw = write(fd, buffer, nr);
        if (nw <= 0) {
            perror(argv[1]);
            close(fd);
            return 4;
        }
        write(STDOUT_FILENO, "Grade: ", 8);
        nr1 = read(STDIN_FILENO,buffer,BUFFER_SIZE);
        
        nw1 = write(fd,buffer,nr1);
        if (nw <= 0) {
            perror(argv[1]);
            close(fd);
            return 4;
        }
    }
    close(fd);
    return 0;
}