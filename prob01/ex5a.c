#include <stdio.h>
#include <stdlib.h>
int main(int argc,const char *argv[], char *envp[])
{
 int i=0;
 int j;
 while(envp[i]!=NULL){
	 printf("%s\n",envp[i]);
	 printf("\n");
	 i++;
 }
 return 0;
}
