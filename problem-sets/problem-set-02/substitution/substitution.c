// Program that encrypts messages using a substitution cipher.

#include <ctype.h>
#include <stdio.h>
#include <string.h>

int check_length(const char *key) {
  if (strlen(key) != 26) {
    printf("Key must contain 26 characters.\n");
    return 1;
  }
  return 0;
}

int check_alpha(const char *key) {
  while (*key != '\0') {
    if (!isalpha(*key)) {
      printf("Key must contain only alphabetical characters.\n");
      return 1;
    }
    key++;
  }
  return 0;
}

int check_repeated(const char *key) {
  int used[26] = {0};
  while (*key != '\0') {
    if (used[toupper(*key) - 'A']) {
      printf("Key must contain each letter exactly once.\n");
      return 1;
    } else
      used[toupper(*key) - 'A'] = 1;
    key++;
  }
  return 0;
}

void encrypt(const char *key, const char *text, char *encrypted) {
  int i;
  for (i = 0; text[i] != '\0'; i++) {
    if (isalpha(text[i])) {
      if (islower(text[i]))
        encrypted[i] = tolower(key[(text[i]) - 'a']);
      else
        encrypted[i] = toupper(key[text[i] - 'A']);
    } else
      encrypted[i] = text[i];
  }
  encrypted[i] = '\0';
}

int main(int argc, char *argv[]) {
  char plaintext[1000], encrypted[1000];
  if (argc != 2) {
    printf("You must provide exactly one key as argument.\n");
    return 1;
  }
  if (check_length(argv[1]) || check_alpha(argv[1]) ||
      check_repeated(argv[1])) {
    return 1;
  }
  printf("plaintext: ");
  fgets(plaintext, sizeof(plaintext), stdin);
  plaintext[strcspn(plaintext, "\n")] = '\0';
  encrypt(argv[1], plaintext, encrypted);
  printf("ciphertext: %s\n", encrypted);
  return 0;
}