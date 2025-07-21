// Program that recreates that pyramid, using hashes (#) for bricks

#include <stdio.h>

void bricksbuilder(int height) {
  int row, space, leftBlock, rightBlock;
  for (row = 1; row <= height; row++) {
    // Print spaces on the left
    for (space = 1; space <= height - row; space++)
      printf(" ");
    // Print left side blocks
    for (leftBlock = 1; leftBlock <= row; leftBlock++)
      printf("#");
    // Print space between the blocks
    printf("  ");
    // Print right side blocks
    for (rightBlock = 1; rightBlock <= row; rightBlock++)
      printf("#");
    // Line break
    printf("\n");
  }
}

int main(void) {
  int height;
  do {
    printf("Height: ");
    scanf("%d", &height);
    if (height < 1 || height > 8) {
      printf("Height must be between 1 and 8!\n");
    }
  } while (height < 1 || height > 8);
  bricksbuilder(height);
}