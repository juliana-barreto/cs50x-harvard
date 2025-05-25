//Program that calculates the approximate grade level needed to comprehend some text.

#include <stdio.h>
#include <ctype.h>
#include <string.h>

int readability(char text[]) {
  int words = 1, sentences = 0, letters = 0;
  for (int i = 0; text[i] != '\0'; i++) {
     if (isalpha(text[i]))
      letters++;
    if (text[i] == ' ')
      words++;
    if (text[i] == '.' || text[i] == '!' || text[i] == '?')
      sentences++;
  }
  float L = (float) letters / words * 100;
  float S = (float) sentences / words * 100;
  float index = 0.0588 * L - 0.296 * S - 15.8;
  if (index - (int)index >= 0.5) {
    return (int)index + 1;
  } else {
    return (int)index;
  }
}

int main(){
  char text[1000];
  printf("Text: ");
  fgets(text, sizeof(text), stdin);
  text[strcspn(text, "\n")] = '\0';
  int index = readability(text);
  if (index < 1) {
    printf("Before Grade 1\n");
  } else if (index >= 16) {
    printf("Grade 16+\n");
  } else {
    printf("Grade %d\n", index);
  }
}