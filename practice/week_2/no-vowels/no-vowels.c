// Write a function to replace vowels with numbers

#include <stdio.h>
#include <string.h>
#include <ctype.h>

char* replace(char *word) {
  for (int i = 0; i < strlen(word); i++) {
    switch(tolower(word[i])) {
      case 'a':
        word[i] = '6'; break;
      case 'e':
        word[i] = '3'; break;
      case 'i':
        word[i] = '1'; break;
      case 'o':
        word[i] = '0'; break;
      case 'u':
        word[i] = 'u'; break;
    }
  }
  return word;
}

int main(int argc, char *argv[]) {
  if (argc != 2){
    printf("You must provide one word as an argument.\n");
    return 1;
  }
  printf("%s\n", replace(argv[1]));
}
