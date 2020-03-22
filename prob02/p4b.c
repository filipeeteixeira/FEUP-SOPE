#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define BUFFER_SIZE 512

typedef struct Student{
    char name[50];
    int grade;
}Student;

int main(int argc, char *argv[])
{
    int fd, nr, nw, nr1, nw1;
    unsigned char buffer[BUFFER_SIZE];
    struct Student student;

    if (argc != 2) {
        printf("Usage: %s <destination>\n", argv[0]);
        return 1;
    }

    fd = open(argv[1], O_WRONLY | O_TRUNC, 0644);
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
        strncpy(student.name, buffer, nr);

        write(STDOUT_FILENO, "Grade: ", 8);
        nr1 = read(STDIN_FILENO,buffer,BUFFER_SIZE);

        student.grade = atoi(buffer);
        
        write(fd,&student,sizeof(Student));
    }
    close(fd);
    return 0;
}