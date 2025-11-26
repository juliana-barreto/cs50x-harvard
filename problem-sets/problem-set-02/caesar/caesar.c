#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  // Check for correct number of command-line arguments
  if (argc != 2) {
    printf("Usage: ./caesar key\n");
    return 1;
  }

  // Check if the key is a non-negative integer
  for (int i = 0; argv[1][i] != '\0'; i++) {
    if (!isdigit(argv[1][i])) {
      printf("Usage: ./caesar key\n");
      return 1;
    }
  }

  // Convert key from string to integer
  int key = atoi(argv[1]);

  // Prompt user for plaintext and read input
  printf("plaintext: ");
  char plaintext[1000];
  fgets(plaintext, sizeof(plaintext), stdin);

  char ciphertext[1000];
  int i = 0;
  for (i = 0; plaintext[i] != '\0'; i++) {
    // Encrypt each character
    char c = plaintext[i];
    if (isalpha(c)) {
      // Convert to 0-25 range and apply the Caesar cipher
      char base = isupper(c) ? 'A' : 'a';
      int p = plaintext[i] - base;
      ciphertext[i] = ((p + key) % 26) + base;
      // Non-alphabetic characters remain unchanged
    } else {
      ciphertext[i] = c;
    }
  }

  // Null-terminate the ciphertext string
  ciphertext[i] = '\0';

  // Output the ciphertext
  printf("ciphertext: %s", ciphertext);

  return 0;
}