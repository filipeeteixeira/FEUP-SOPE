#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,const char *argv[], char *envp[])
{
 int i=0;
 while(envp[i]!=NULL){
	 if(strncmp(envp[i],"USER",4)==0){
		 printf("Hello %s\n", envp[i]);
		 return 0;
	 }
	 i++;
 }
}
