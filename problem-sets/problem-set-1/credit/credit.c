// Program that checks the validity of a given credit card number.

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int first_sum(int length, char *card){
  int i, digit, doubled, sum = 0; 
  for (i = length - 2; i >= 0; i -= 2) {
    digit = card [i] - '0';
    doubled = digit * 2;
    sum += (doubled/10) + (doubled % 10);
  }
  return sum;
}
int sec_sum(int length, char *card){
  int i, digit, sum = 0; 
  for (i = length -1; i >= 0; i -= 2) {
    digit = card[i] - '0';
    sum += digit;
  }
  return sum;
}
int main () {
  char card[20];
  int length, sum_1, sum_2, sum, i;
  printf("Insert the card number: ");
  gets(card);
  length = strlen(card);
  for (i = 0; i < length; i++) {
    if (!isdigit(card[i])) {
      printf("INVALID\n");
      return 0;
    }
  }
  if (length < 13 || length > 16) {
    printf("INVALID\n");
    return 0;
  }
  sum_1 = (first_sum(length, card));
  sum_2 = (sec_sum(length, card));
  sum = sum_1 + sum_2;
  if (sum % 10 != 0)
    printf("INVALID\n");
  else 
    if (length == 15 && card[0] == '3' && (card[1] == '4' || card[1] == '7'))
      printf("AMERICAN EXPRESS\n");
    else 
      if (length == 16 && card [0] == '5' && (card[1] == '1' || card[1] == '2' || card[1] == '3' || card[1] == '4' || card[1]== '5'))
        printf("MASTERCARD\n");
      else 
        if ((length == 13 || length == 16) && card[0] == '4')
         printf("VISA\n");
        else  
          printf("UNKNOWN\n");
  return 0;
}