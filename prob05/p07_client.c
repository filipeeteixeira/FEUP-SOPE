#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

typedef struct results{
    int sum;
    int sub;
    int mul;
    double div;
    int info;
}Results;

int main(void)
{
    int n1, n2, ints[2], fd, fd1;

    do{
      fd = open("/tmp/fifo_req",O_WRONLY);
      fd1 = open("/tmp/fifo_ans",O_RDONLY);
      if (fd==-1 || fd1==-1){
        printf("Waiting for server..\n");
        sleep(1);
      } 
    }while(fd==-1 || fd1==-1);

    while(1){
      write(STDOUT_FILENO,"Insert number: ",16);
      scanf("%d",&n1);
      write(STDOUT_FILENO,"Insert number: ",16);
      scanf("%d",&n2);
      ints[0]=n1;
      ints[1]=n2;

      if(n1==0 && n2==0){
        break;
      }
    
      write(fd,ints,sizeof(ints));
      
      Results results;
      read(fd1,&results,sizeof(Results));

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
    }
  close(fd);
  close(fd1);
  
  return 0;
}
