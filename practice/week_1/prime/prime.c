//Tests if a number is prime, and returns true if it is, and false if it is not.

#include <stdio.h>

int prime(int number) {
    // 1 is not considered a prime number
    if (number == 1)
        return 0;
    // Check if number is divisible by any integer from 2 to number-1
    for (int i = 2; i < number; i++) {
        if (number % i == 0)
            return 0;
    }
    // If no divisors found, number is prime
    return 1; 
}

int main(void) {
    int min, max;
    // Get minimum number (must be at least 1)
    do {
        printf("Minimum: ");
        scanf("%d", &min);
    } while (min < 1);
    // Get maximum number (must be greater than minimum)
    do {
        printf("Maximum: ");
        scanf("%d", &max);
    } while (min >= max);
    // Print all prime numbers in the range
    for (int i = min; i <= max; i++) {
        if (prime(i))
            printf("%i\n", i);
    }
}
