//Program that collects user input for their name and location, then displays a personalized greeting.

#include <stdio.h>

main (void){
  char name[50], location[100];
  printf("What is your name? ");
  gets(name);
  printf("Where do you live? ");
  gets(location);
  printf("Hello, %s, from %s\n", name, location);
}