//Program that collects user input for their name and location, then displays a personalized greeting.

#include <stdio.h>
#include <string.h>

int main( ){
  char name[50], location[100];
  printf("What is your name? ");
  fgets(name, sizeof(name), stdin);
  name[strcspn(name, "\n")] = '\0';
  printf("Where do you live? ");
  fgets(location, sizeof(location), stdin);
  location[strcspn(location, "\n")] = '\0';
  printf("Hello, %s, from %s\n", name, location);
}