// PROGRAMA p6a.c
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#define BUF_LENGTH 256

int main(int argc,const char *argv[])
{
 FILE *src, *dst;
 char buf[BUF_LENGTH];

 if(argv[1]==NULL){
     printf("usage: a.out file1 file2\n");
     exit(1);
 }

 if ( ( src = fopen( argv[1], "r" ) ) == NULL )
 {
    printf("Value of errno: %d\n", errno);
    perror("Error printed by perror");
    printf("Error printed by strerror: %s\n", strerror(errno));
    exit(1);
 }
 if ( ( dst = fopen( argv[2], "w" ) ) == NULL )
 {
    perror("Error opening writing file");
    exit(2);
 }
 while( ( fgets( buf, BUF_LENGTH, src ) ) != NULL )
 {
 fputs( buf, dst );
 }
 fclose( src );
 fclose( dst );
 exit(0); // zero é geralmente indicativo de "sucesso"
}

//echo $? para ver o código de retorno do
//ultimo comando executado