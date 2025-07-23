// Practice writing a function to find a max value

#include <stdio.h>

int max(int* array, int n) {
  int max_value = array[0];
  for (int i = 0; i < n; i++) {
    if (array[i] > max_value) {
      max_value = array[i];
    }
  }
  return max_value;
}

int main(void) {
    int n;
    do {
      printf ("Number of elements: ");
      scanf("%i", &n);
    } while (n < 1);
    int arr[n];
    for (int i = 0; i < n; i++) {
      printf("Element %i: ", i);
      scanf("%d", &arr[i]);
    }
    printf("The max value is %i.\n", max(arr, n));
}
