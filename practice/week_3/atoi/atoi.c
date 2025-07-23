// Program that converts a string of digits into its corresponding integer value

#include <ctype.h>
#include <stdio.h>
#include <string.h>

int convert(const char *input) {
  int len = strlen(input);
  //// Base case: empty string returns 0
  if (len == 0) {
    return 0;
  }
  // Get the value of the last digit
  int last_digit = input[len - 1] - '0';
  // Create a new string without the last character
  char remaining[len];
  strcpy(remaining, input);
  remaining[len - 1] = '\0';
  // Recursively call for the rest of the string and add the current digit
  return convert(remaining) *  10 + last_digit;
}

int main(void) {
  char input[100];
  printf("Enter a positive integer: ");
  scanf("%s", input);
  for (int i = 0, n = strlen(input); i < n; i++) {
    if (!isdigit(input[i])) {
      printf("Invalid Input!\n");
      return 1;
    }
  }
  // Convert string to int
  printf("%i\n", convert(input));
}
