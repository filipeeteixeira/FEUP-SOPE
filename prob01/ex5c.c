#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,const char *argv[], char *envp[])
{
 int i=0;
 char *user = getenv("USER");
 printf("Hello %s\n",user);
}
