#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>

typedef struct numbers{
    int n,n1;
}Numbers;

int main(void)
{
int n, fd[2];
pid_t pid;
Numbers nbs;

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
    scanf("%d",&nbs.n);
    write(STDOUT_FILENO,"Insert number: ",16);
    scanf("%d",&nbs.n1);
    
    close(fd[0]); /* fecha lado receptor do pipe */
    write(fd[1],&nbs,sizeof(nbs));

} else { /* filho */
    Numbers received_nbs;
    close(fd[1]); /* fecha lado emissor do pipe */
    n = read(fd[0], &received_nbs, sizeof(received_nbs));
    int sum = received_nbs.n+received_nbs.n1;
    printf("Soma: %d \n",sum);
    }
    exit(0);
} 