#include <stdio.h>

int main(void) {
  int change = -1;
  do {
    printf("\nChange owed (in cents): ");
    scanf("%d", &change);

    if (change < 0) {
      printf("Please enter a non-negative amount.\n");
      continue;
    }

    //How many quarters are needed
    int quarters = change / 25;
    //Update change to reflect remaining cents
    change = change % 25;

    //How many dimes are needed
    int dimes = change / 10;
    change = change % 10;

    //How many nickels are needed
    int nickels = change / 5;
    change = change % 5;

    //Remaining cents are pennies
    int pennies = change;

    //Calculate total coins
    int totalCoins = quarters + dimes + nickels + pennies;

    printf("Total coins needed: %d\n", totalCoins);

  } while (change != 0);

  return 0;
}