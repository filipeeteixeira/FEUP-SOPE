#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//export "USER_NAME=Luids Filipe"

int main(int argc,const char *argv[], char *envp[])
{
 int i=0;
 char *user = getenv("USER_NAME");
 printf("Hello %s\n",user);
}
