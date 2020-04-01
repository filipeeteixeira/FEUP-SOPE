#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>

int main(void)
{
int n, fd[2];
pid_t pid;
int sum, sub;
double div;
char n1[256], n2[256], nn1[256], nn2[256];

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
    scanf("%s",n1);
    write(STDOUT_FILENO,"Insert number: ",16);
    scanf("%s",n2);
    
    close(fd[0]); /* fecha lado receptor do pipe */
    write(fd[1],n1,sizeof(n1));
    write(fd[1],n2,sizeof(n1));

} else { /* filho */

    close(fd[1]); /* fecha lado emissor do pipe */
    n = read(fd[0],nn1, sizeof(nn1));
    n = read(fd[0],nn2, sizeof(nn2));

    printf("%s\n",nn1);
    printf("%s\n",nn2);
    
    sum = atoi(nn1)+atoi(nn2);
    printf("Soma: %d \n",sum);
    
    sub = atoi(nn1)-atoi(nn2);
    printf("Sub: %d \n",sum);
    
    if (atoi(nn1)==0){
        printf("Divisao invalida\n");
    }
    else{
        div = atoi(nn1)/(double)atoi(nn2);
        printf("Div: %f \n",div);
    }
    
    }
    exit(0);
} 