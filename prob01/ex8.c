#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <time.h>
#include <sys/times.h> 

int main(int argc,const char *argv[]){
    int i=0;
    time_t tc;
    int generatedNumber;
    clock_t start, end;
    struct tms t;
    long ticks;

    start = times(&t); /* início da medição de tempo */ 
    ticks = sysconf(_SC_CLK_TCK); //numero de ticks por segundo

    /* Intializes random number generator */
   srand((unsigned) time(&tc));

   /* Print 5 random numbers from 0 to arg2 */
   while(1){
    printf("iteration: %d\n", i);
    generatedNumber= rand() % atoi(argv[1]);
    printf("number: %d\n", generatedNumber );
    if(generatedNumber==atoi(argv[2])){
        break;
    }
    i++;
   }
    end = times(&t); /* fim da medição de tempo */
    printf("Clock: %4.2f \n", (double)(end-start)/ticks);
    printf("User time: %4.2f \n", (double)t.tms_utime/ticks);
    printf("System time: %4.2f \n", (double)t.tms_stime/ticks); 
}