#include "helpers.h"
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      RGBTRIPLE pixel = image[i][j];
      int gray = round((pixel.rgbtBlue + pixel.rgbtGreen + pixel.rgbtRed) / 3.0);

      pixel.rgbtBlue = gray;
      pixel.rgbtGreen = gray;
      pixel.rgbtRed = gray;

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
  if (copy == NULL) {
    return;
  }

  // Create a copy of the original image
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      copy[i][j] = image[i][j];
    }
  }

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      int redSum = 0;
      int greenSum = 0;
      int blueSum = 0;
      float pixelCount = 0.0;

      for (int row = i - 1; row <= i + 1; row++) {
        for (int col = j - 1; col <= j + 1; col++) {
          if (row >= 0 && row < height && col >= 0 && col < width) {
            RGBTRIPLE neighbor = copy[row][col];
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

      image[i][j] = blurred;
    }
  }

  free(copy);

  return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width]) {
  RGBTRIPLE (*copy)[width] = calloc(height, width * sizeof(RGBTRIPLE));
  if (copy == NULL) {
    return;
  }

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      copy[i][j] = image[i][j];
    }
  }

  int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
  int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      double sumGxRed = 0, sumGyRed = 0;
      double sumGxGreen = 0, sumGyGreen = 0;
      double sumGxBlue = 0, sumGyBlue = 0;

      for (int row = i - 1; row <= i + 1; row++) {
        for (int col = j - 1; col <= j + 1; col++) {
          if (row >= 0 && row < height && col >= 0 && col < width) {

            RGBTRIPLE neighbor = copy[row][col];
            
            int kernelRow = (row - i) + 1;
            int kernelCol = (col - j) + 1;

            sumGxRed += neighbor.rgbtRed * Gx[kernelRow][kernelCol];
            sumGyRed += neighbor.rgbtRed * Gy[kernelRow][kernelCol];
                  
            sumGxGreen += neighbor.rgbtGreen * Gx[kernelRow][kernelCol];
            sumGyGreen += neighbor.rgbtGreen * Gy[kernelRow][kernelCol];
                  
            sumGxBlue += neighbor.rgbtBlue * Gx[kernelRow][kernelCol];
            sumGyBlue += neighbor.rgbtBlue * Gy[kernelRow][kernelCol];

          } 
        }
      }

      int red = round(sqrt(pow(sumGxRed, 2) + pow(sumGyRed, 2)));
      if (red > 255) {
          red = 255;
      }
      
      int green = round(sqrt(pow(sumGxGreen, 2) + pow(sumGyGreen, 2)));
      if (green > 255) {
          green = 255;
      }

      int blue = round(sqrt(pow(sumGxBlue, 2) + pow(sumGyBlue, 2)));
      if (blue > 255) {
          blue = 255;
      }

      RGBTRIPLE edgePixel;
      edgePixel.rgbtRed = red;
      edgePixel.rgbtGreen = green;
      edgePixel.rgbtBlue = blue;

      image[i][j] = edgePixel;
    }
  }

  free(copy);
  return;
}