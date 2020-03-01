#include <stdio.h>
#include <stdlib.h>
int main(int argc,const char *argv[])
{
 int counter;
 int saud=atoi(argv[1]);
 for (int i=0;i<saud;i++){
	printf("Hello ");
	for(counter=2;counter<argc;counter++) 
		printf("%s",argv[counter]);
	printf("\n");
 }
 return 0;
}
