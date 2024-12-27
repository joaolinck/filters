#include <math.h>

#include "helpers.h"

int isCapped (int color_value);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++){

        for (int j = 0; j < width; j++){

            int avrg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);

            image[i][j].rgbtBlue = avrg;
            image[i][j].rgbtGreen = avrg;
            image[i][j].rgbtRed = avrg;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++){

        for (int j = 0; j < width; j++){

            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            image[i][j].rgbtRed = isCapped(sepiaRed);
            image[i][j].rgbtGreen = isCapped(sepiaGreen);
            image[i][j].rgbtBlue = isCapped(sepiaBlue);
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++){

        for (int j = 0; j < width; j++){

            if (j >= width - j - 1)
                break;

            int temp_red = image[i][j].rgbtRed;
            int temp_green = image[i][j].rgbtGreen;
            int temp_blue = image[i][j].rgbtBlue;

            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;

            image[i][width - 1 - j].rgbtRed = temp_red;
            image[i][width - 1 - j].rgbtGreen = temp_green;
            image[i][width - 1 - j].rgbtBlue = temp_blue;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++){

        for (int j = 0; j < width; j++){

            copy[i][j] = image[i][j];

        }
    }

    for (int i = 0; i < height; i++){

        for (int j = 0; j < width; j++){

            float sumRed = 0;
            float sumGreen = 0;
            float sumBlue = 0;
            float counter = 0;

            for (int n = -1; n < 2; n++){

                for (int m = -1; m < 2; m++){

                    if (i + n < 0 || i + n > height-1)
                        continue;

                    if (j + m < 0 || j + m > width-1)
                        continue;


                    sumRed += copy[i+n][j+m].rgbtRed;
                    sumGreen += copy[i+n][j+m].rgbtGreen;
                    sumBlue += copy[i+n][j+m].rgbtBlue;
                    counter++;

                }
            }

        image[i][j].rgbtRed = round(sumRed / counter);
        image[i][j].rgbtGreen = round(sumGreen / counter);
        image[i][j].rgbtBlue = round(sumBlue / counter);

        }
    }

    return;
}

int isCapped (int color_value){

    if (color_value > 255){

        return 255;
    }
    else{

        return color_value;
    }
}
