#include <stdio.h>

void bricksbuilder(int height){
  int i, j;
  for (i = 1; i <= height; i++)
      for (j = 1; j < height - i; j++)
          printf(" ");
      for (j = 1; j <= i; j++)
          printf("#");
      printf("  ");
      for (j = 1; j <= i; j++)
          printf("#");
      printf("\n");
}
int main(void){
  int height;
  printf("Height: ");
  scanf("%d", &height);
  if (height < 1 || height > 8)
    printf("Height must be between 1 and 8!\n");
  else
    bricksbuilder(height);
}