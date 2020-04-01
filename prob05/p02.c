#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>

typedef struct results{
    int sum;
    int sub;
    int mul;
    double div;
    int info;
}Results;

int main(void)
{
int n,n1,n2, fd[2], fd1[2];
pid_t pid;
int ints[2], receive_ints[2];
Results results;

if (pipe(fd) < 0) {
    fprintf(stderr, "pipe error\n");
    exit(1);
    }

if (pipe(fd1) < 0) {
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

    close(fd1[1]); /* fecha lado emissor do pipe */
    read(fd1[0],&results,sizeof(Results));

    printf("Soma: %d\n",results.sum);
    printf("Diferença: %d\n",results.sub);
    printf("Multiplicação: %d\n",results.mul);
    
    if(results.info == -1){
      printf("Invalido: divisão por 0\n");
    }
    else if(results.info == 0){
      printf("Divisão(inteiro): %d\n",(int)results.div);
    }
    else{
      printf("Divisão(não inteiro): %f\n",results.div);
    }

} else { /* filho */
    close(fd[1]); /* fecha lado emissor do pipe */
    n = read(fd[0], receive_ints, sizeof(receive_ints));
    
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

    close(fd1[0]); /* fecha lado receptor do pipe */
    write(fd1[1],&results,sizeof(Results));
    
    }
    exit(0);
} 