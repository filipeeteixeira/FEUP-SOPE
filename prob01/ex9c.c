#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_LENGTH 256 

int main(){
    char buf[BUF_LENGTH];
    fgets(buf,BUF_LENGTH,stdin);
    char tokens[10][50]; //10 tokens de 50 chars
    int n=0;

    char* token = strtok(buf,"|;");

    printf("Tokens:\n");
    while(token != NULL){
        strcpy(tokens[n],token);
        token = strtok(NULL, "|;"); 
        n++;
    }

    for(int i=0;i<n;i++){
        printf("%s\n", tokens[i]);
    }
    return 0;
}