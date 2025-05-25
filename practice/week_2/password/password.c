// Check that a password has at least one lowercase letter, uppercase letter, number and symbol.

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int valid(char *password) {
    int lower = 0, upper = 0, number = 0, symbol = 0;
    // Loop through each character in the password
    for (int i = 0; password[i] != '\0'; i++) {
        // Check for uppercase letter
        if (isupper(password[i])) 
            upper = 1;
        // Check for lowercase letter
        if (islower(password[i]))
            lower = 1;
        // Check for number
        if (isdigit(password[i]))
            number = 1;
        // Check for symbol (any printable character that is not alphanumeric)
        if (!isalnum(password[i]) && isprint(password[i]))
            symbol = 1;
        // If all requirements are met, return true
        if (lower && upper && number && symbol)
            return 1;
    }
    // If password is missing any requirement, return false
    return 0;
}

int main(void) {
    char password[100];
    printf("Enter your password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';
    if (valid(password)) {
        printf("Your password is valid!\n");
    } else {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

