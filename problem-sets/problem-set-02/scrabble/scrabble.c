// Program that determines the winner of a short Scrabble-like game. 

#include <stdio.h>
#include <ctype.h>
#include <string.h>

int calculate_score(char *word) {
  int sum = 0;
  char *one = "AEILNORSTU", *two = "DG", *three = "BCMP", *four = "FHVWY", *eight = "JX", *ten = "QZ";
  char five = 'K';
  for (int i = 0; word[i] != '\0'; i++) {
    if (strchr(one, toupper(word[i])) != NULL)
      sum += 1;
    else if (strchr(two, toupper(word[i])) != NULL)
      sum += 2;
    else if (strchr(three, toupper(word[i])) != NULL)
      sum += 3;
    else if (strchr(four, toupper(word[i])) != NULL)
      sum += 4;
    else if (toupper(word[i]) == five)
      sum += 5;
    else if (strchr(eight, toupper(word[i])) != NULL)
      sum += 8;
    else if (strchr(ten, toupper(word[i])) != NULL)
      sum += 10;
  }
  return sum;
}

int main(){
  char player1[100], player2[100];
  int score1 = 0, score2 = 0;
  printf("Player 1: ");
  fgets(player1, sizeof(player1), stdin);
  player1[strcspn(player1, "\n")] = '\0';
  printf("Player 2: ");
  fgets(player2, sizeof(player2), stdin);
  player2[strcspn(player2, "\n")] = '\0';
  score1 = calculate_score(player1);
  score2 = calculate_score(player2);
  if (score1 > score2){
  printf("Player 1 wins!\n");
  } else if (score2 > score1){
  printf("Player 2 wins!\n");
  } else { 
  printf("Tie!\n");
  }
}