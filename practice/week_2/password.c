// Check that a password has at least one lowercase letter, uppercase letter, number and symbol.

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int valid(char *password) {
  int lower = 0, upper = 0, number = 0, symbol = 0;
  for (int i = 0; password[i] != '\0'; i++) {
    if (isupper(password[i])) 
      upper = 1;
    if (islower(password[i]))
      lower = 1;
    if (isdigit(password[i]))
      number = 1;
    if (!isalnum(password[i]) && isprint(password[i]))
      symbol = 1;
    if (lower && upper && number && symbol)
      return 1;
  }
    return 0;
}
int main(void) {
    char password[100];
    printf("Enter your password: ");
    fgets(password, sizeof(password), stdin);
    strcspn (password, "\n");
    if (valid(password)) {
        printf("Your password is valid!\n");
    } else {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

