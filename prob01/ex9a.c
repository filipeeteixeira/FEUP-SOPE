#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_LENGTH 256 

int main(){
    char buf[BUF_LENGTH];
    fgets(buf,BUF_LENGTH,stdin);

    char* token = strtok(buf," ");

    printf("Tokens:\n");
    while(token != NULL){
        printf("%s\n", token); 
        token = strtok(NULL, " "); 
    }
    return 0;
}