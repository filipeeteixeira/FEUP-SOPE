#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

typedef struct results{
    int sum;
    int sub;
    int mul;
    double div;
    int info;
}Results;

int main(void)
{
    int fd,fd1, receive_ints[2];
    Results results;
    
    mkfifo("/tmp/fifo_req",0660);
    mkfifo("/tmp/fifo_ans",0660);

    fd = open("/tmp/fifo_req",O_RDONLY);
    fd1 = open("/tmp/fifo_ans",O_WRONLY);

    while(read(fd,&receive_ints,sizeof(Results))>0){
        

        results.sum = receive_ints[0]+receive_ints[1];
        results.sub = receive_ints[0]-receive_ints[1];
        results.mul = receive_ints[0]*receive_ints[1];

        if (receive_ints[1]==0){
            results.info=-1;
        }
        else if (receive_ints[0]%receive_ints[1]==0){
            results.info=0; //é inteiro
            results.div = receive_ints[0]/(double)receive_ints[1];
        }
        else{
            results.info=1; //não é inteiro
            results.div = receive_ints[0]/(double)receive_ints[1];
        }
       write(fd1,&results,sizeof(Results));
    };
    
    close(fd);
  close(fd1);
    unlink("/tmp/fifo_req"); unlink("/tmp/fifo_ans");
    return 0;
} 

/*the writer is trying to write() data 
(i.e. is blocked in the write()-syscall) now receive a SIGPIPE, 
which leads to program termination (if no other signal handling is specified).*/