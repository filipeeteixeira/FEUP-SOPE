#include <stdio.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/wait.h>

int main(void) {
 if(fork() > 0) {
    printf("Hello");
 } else {
    printf(" world !");
 }
    return 0;
}
