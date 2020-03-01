#include <stdio.h>
#include <stdlib.h>

void handler1 () {
   printf("Executing exit handler 1\n");
   //exit(1);
}

void handler2 () {
   printf("Executing exit handler 2\n");
}

int main () {
   /* register the termination function */
   atexit(handler1 );
   atexit(handler2 );
   
   printf("Starting  main program...\n");
   //abort();
   printf("Main Done!...\n");

   return(0);
}