#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define FAT_BLOCK_SIZE 512

int main(int argc, char *argv[]) {
  //Ensure proper usage
  if (argc != 2) {
    printf("Usage: ./recover FILE");
    return 1;
  }

  char* inFile = argv[1];

  // Open input file
  FILE* card = fopen(inFile, "r");
  if (card == NULL) {
    printf("Could not open %s.\n", inFile);
    return 1;
  }

  uint8_t buffer[FAT_BLOCK_SIZE];
  FILE* image = NULL;
  char filename[8] = {0};
  int fileCount = 0;
  size_t bytesRead;

  // While there's still data left to read from the memory card
  while ((bytesRead =
    fread(buffer, sizeof(uint8_t), FAT_BLOCK_SIZE, card)) > 0) {
    // Check for JPEG signature
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
      (buffer[3] & 0xf0) == 0xe0) {
      // Close previous file if it exists
      if (image != NULL) {
        fclose(image);
      }
      // Create new JPEG file
      sprintf(filename, "%03i.jpg", fileCount);
      image = fopen(filename, "wb");
      if (image == NULL) {
        printf("Could not open %s.\n", inFile);
        fclose(card);
        return 1;
      }
      fileCount++;
      }
    // Write to current JPEG file if it exists
    if (image != NULL) {
      fwrite(buffer, sizeof(uint8_t), bytesRead, image);
    }
    }
  // Close any remaining open files
  if (image != NULL) {
    fclose(image);
  }
  fclose(card);
}