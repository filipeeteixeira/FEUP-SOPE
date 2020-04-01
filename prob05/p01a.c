#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
int main(void)
{
int n,n1,n2, fd[2];
pid_t pid;
int ints[2], receive_ints[2];
int sum, sub;
double div;

if (pipe(fd) < 0) {
    fprintf(stderr, "pipe error\n");
    exit(1);
    }
if ( (pid = fork()) < 0) {
    fprintf(stderr, "fork error\n");
    exit(2);
    }
else if (pid > 0) { /* pai */
    write(STDOUT_FILENO,"Insert number: ",16);
    scanf("%d",&n1);
    write(STDOUT_FILENO,"Insert number: ",16);
    scanf("%d",&n2);
    ints[0]=n1;
    ints[1]=n2;
    
    close(fd[0]); /* fecha lado receptor do pipe */
    write(fd[1],ints,sizeof(ints));

} else { /* filho */
    close(fd[1]); /* fecha lado emissor do pipe */
    n = read(fd[0], receive_ints, sizeof(receive_ints));
    sum = receive_ints[0]+receive_ints[1];
    printf("Soma: %d \n",sum);
    sub = receive_ints[0]-receive_ints[1];
    printf("Sub: %d \n",sum);
    if (receive_ints[1]==0){
        printf("Divisao invalida\n");
    }
    else{
        div = receive_ints[0]/(double)receive_ints[1];
        printf("Div: %f \n",div);
    }
    
    }
    exit(0);
} 