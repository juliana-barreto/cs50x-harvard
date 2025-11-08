#include "helpers.h"
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      RGBTRIPLE pixel = image[i][j];
      int gray =
          round((pixel.rgbtBlue + pixel.rgbtGreen + pixel.rgbtRed) / 3.0);

      pixel.rgbtBlue = gray;
      pixel.rgbtGreen = gray;
      pixel.rgbtRed = gray;

      image[i][j] = pixel;
    }
  }
  return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width]) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      RGBTRIPLE pixel = image[i][j];

      int sepiaRed = round(0.393 * pixel.rgbtRed + 0.769 * pixel.rgbtGreen +
                           0.189 * pixel.rgbtBlue);
      if (sepiaRed > 255) sepiaRed = 255;

      int sepiaGreen = round(0.349 * pixel.rgbtRed + 0.686 * pixel.rgbtGreen +
                             0.168 * pixel.rgbtBlue);
      if (sepiaGreen > 255) sepiaGreen = 255;

      int sepiaBlue = round(0.272 * pixel.rgbtRed + 0.534 * pixel.rgbtGreen +
                            0.131 * pixel.rgbtBlue);
      if (sepiaBlue > 255) sepiaBlue = 255;

      pixel.rgbtRed = sepiaRed;
      pixel.rgbtGreen = sepiaGreen;
      pixel.rgbtBlue = sepiaBlue;

      image[i][j] = pixel;
    }
  }
  return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width / 2; j++) {
      int rightIndex = width - j - 1;
      RGBTRIPLE tmp = image[i][j];
      image[i][j] = image[i][rightIndex];
      image[i][rightIndex] = tmp;
    }
  }
  return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]) {
  RGBTRIPLE (*copy)[width] = calloc(height, width * sizeof(RGBTRIPLE));
  if (copy == NULL)
    return;

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      int redSum = 0;
      int greenSum = 0;
      int blueSum = 0;
      float pixelCount = 0.0;

      for (int row = i - 1; row <= i + 1; row++) {
        for (int col = j - 1; col <= j + 1; col++) {
          if (row >= 0 && row < height && col >= 0 && col < width) {
            RGBTRIPLE neighbor = image[row][col];
            redSum += neighbor.rgbtRed;
            greenSum += neighbor.rgbtGreen;
            blueSum += neighbor.rgbtBlue;
            pixelCount++;
          }
        }
      }

      RGBTRIPLE blurred;
      blurred.rgbtRed = round(redSum / pixelCount);
      blurred.rgbtGreen = round(greenSum / pixelCount);
      blurred.rgbtBlue = round(blueSum / pixelCount);

      copy[i][j] = blurred;
    }
  }

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      image[i][j] = copy[i][j];
    }
  }

  free(copy);

  return;
}