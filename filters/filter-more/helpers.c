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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE copy[height][width];

    int Gx_array[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int Gy_array[3][3] = {
        {-1,-2,-1},
        { 0, 0, 0},
        { 1, 2, 1}
    };

    for (int i = 0; i < height; i++){

        for (int j = 0; j < width; j++){

            copy[i][j] = image[i][j];

        }
    }

    for (int i = 0; i < height; i++){

        for (int j = 0; j < width; j++){

            int Gx_red = 0;
            int Gx_green = 0;
            int Gx_blue = 0;

            int Gy_red = 0;
            int Gy_green = 0;
            int Gy_blue = 0;

            int y_index = 0;

            for (int y = -1; y < 2; y++){
                int x_index = 0;

                for (int x = -1; x < 2; x++){

                    if (i + y < 0 || i + y > height-1 || j + x < 0 || j + x > width-1){

                        Gx_red += 0;
                        Gx_green += 0;
                        Gx_blue += 0;

                        Gy_red += 0;
                        Gy_green += 0;
                        Gy_blue += 0;
                    }

                    else{

                        Gx_red += Gx_array[y_index][x_index] * copy[i+y][j+x].rgbtRed;
                        Gx_green += Gx_array[y_index][x_index] * copy[i+y][j+x].rgbtGreen;
                        Gx_blue += Gx_array[y_index][x_index] * copy[i+y][j+x].rgbtBlue;

                        Gy_red += Gy_array[y_index][x_index] * copy[i+y][j+x].rgbtRed;
                        Gy_green += Gy_array[y_index][x_index] * copy[i+y][j+x].rgbtGreen;
                        Gy_blue += Gy_array[y_index][x_index] * copy[i+y][j+x].rgbtBlue;
                    }

                    x_index++;
                }

                y_index++;
            }

            image[i][j].rgbtRed = isCapped(round(sqrt(Gx_red*Gx_red + Gy_red*Gy_red)));
            image[i][j].rgbtGreen = isCapped(round(sqrt(Gx_green*Gx_green + Gy_green*Gy_green)));
            image[i][j].rgbtBlue = isCapped(round(sqrt(Gx_blue*Gx_blue + Gy_blue*Gy_blue)));
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
