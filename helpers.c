#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
        // Take averaage of rgb
        //update pixel value
        BYTE average = (int) ((image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3.0);
        image[i][j].rgbtRed = average;
        image[i][j].rgbtGreen = average;
        image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            
            float originalRed = image[i][j].rgbtRed;
            float originalGreen = image[i][j].rgbtGreen;
            float originalBlue = image[i][j].rgbtBlue;
            
            int sepiaRed = (int) (.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            int sepiaGreen = (int) (.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int sepiaBlue = (int) (.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

            if(sepiaRed > 255) sepiaRed = 255;
            if(sepiaGreen > 255) sepiaGreen = 255;
            if(sepiaBlue > 255) sepiaBlue = 255;

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width / 2; j++) {

            int oppositeIndex = width - j - 1;

            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][oppositeIndex];
            image[i][oppositeIndex] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //create copy
    RGBTRIPLE copy[height][width];
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            copy[i][j] = image[i][j];
        }
    }

    //loop every pixel in image
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            int total_red = 0, total_green = 0, total_blue = 0;
            int count = 0;

            for(int di = -1; di <= 1; di++) {
                for(int dj = -1; dj <= 1; dj++) {
                    int ni = i + di;
                    int nj = j + dj;

                    if (ni >= 0 && ni < height && nj >= 0 && nj < width) {
                    total_red += copy[ni][nj].rgbtRed;
                    total_green += copy[ni][nj].rgbtGreen;
                    total_blue += copy[ni][nj].rgbtBlue;
                    count++;                
                    }
                }
            }

            image[i][j].rgbtRed = total_red / count;
            image[i][j].rgbtGreen = total_green / count;
            image[i][j].rgbtBlue = total_blue / count;
        }
    }
    return;
}
