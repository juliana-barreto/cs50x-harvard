#include <stdio.h>
#define FALSE 0
#define TRUE 1

int prime(int number) {
  if (number == 1)
    return FALSE;
  for (int i = 2; i < number; i++) {
    if (number % i == 0)
      return FALSE;
  }
  return TRUE; 
}
main(void) {
  int min, max;
  do {
    printf("Minimum: ");
    scanf("%d", &min);
  } while (min < 1);
  do {
    printf("Maximum: ");
    scanf("%d", &max);
  } while (min >= max);
  for (int i = min; i <= max; i++){
    if (prime(i))
      printf("%i\n", i);
  }
}
