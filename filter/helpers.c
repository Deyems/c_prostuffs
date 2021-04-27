#include "helpers.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    int avgRGB = 0;
    int red; int blue; int green;

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){

            float avgPerPix = (float)(image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen)/3;
            avgPerPix = round(avgPerPix);

            image[i][j].rgbtRed = avgPerPix;
            image[i][j].rgbtBlue = avgPerPix;
            image[i][j].rgbtGreen = avgPerPix;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaRed; int sepiaGreen; int sepiaBlue;
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){

            sepiaRed = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            sepiaGreen = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            sepiaBlue = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);

            //RE-assign RGB VALUES
            if(sepiaRed >= 256) {sepiaRed = 255;}
            if(sepiaBlue >= 256 ) { sepiaBlue = 255; }
            if(sepiaGreen >= 256 ) { sepiaGreen = 255; }

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int reflectorPin = width - 1;;
    int midPoint = width/2;
    int oldred; int oldBlue; int oldGreen;

    for(int i = 0; i < height; i++){
        for(int j = 0; j < midPoint; j++){
            oldred = image[i][j].rgbtRed;
            oldBlue = image[i][j].rgbtBlue;
            oldGreen = image[i][j].rgbtGreen;

            image[i][j].rgbtRed = image[i][reflectorPin - j].rgbtRed;
            image[i][j].rgbtBlue = image[i][reflectorPin - j].rgbtBlue;
            image[i][j].rgbtGreen = image[i][reflectorPin - j].rgbtGreen;

            image[i][reflectorPin - j].rgbtRed = oldred;
            image[i][reflectorPin - j].rgbtGreen = oldGreen;
            image[i][reflectorPin - j].rgbtBlue = oldBlue;
        }

    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //findNeighbours
    // if(width>0  height >0)
    int counter;

    int totalRed = 0;
    int totalBlue = 0;
    int totalGreen = 0;

    float avgRed; float avgBlue; float avgGreen;

    // RGBTRIPLE matrix[height][];
    RGBTRIPLE(*matrix)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    //Keep a Store of image values
    for(int row = 0; row < height; row++){
        for(int col = 0; col < width; col++){
            matrix[row][col].rgbtRed = image[row][col].rgbtRed;
            matrix[row][col].rgbtGreen = image[row][col].rgbtGreen;
            matrix[row][col].rgbtBlue = image[row][col].rgbtBlue;
            // printf("Red Val: %i\n",matrix[row][col].rgbtRed);
        }
    }

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            //down
            int down = i+1; int up = i - 1;
            int left = j-1; int right = j + 1;
            counter = 0;

            if(down < height ){
                //Immediately beneath
                totalRed = totalRed + matrix[down][j].rgbtRed;
                totalBlue = totalBlue + matrix[down][j].rgbtBlue;
                totalGreen = totalGreen + matrix[down][j].rgbtGreen;
                counter++;
            }
            if(up>=0){
                //Immediately above
                totalRed = totalRed + matrix[up][j].rgbtRed;
                totalBlue = totalBlue + matrix[up][j].rgbtBlue;
                totalGreen = totalGreen + matrix[up][j].rgbtGreen;
                counter++;
            }
            if(left>=0){
                //Immmediate left
                totalRed = totalRed + matrix[i][left].rgbtRed;
                totalBlue = totalBlue + matrix[i][left].rgbtBlue;
                totalGreen = totalGreen + matrix[i][left].rgbtGreen;
                counter++;
            }
            if(right<width ){
                //Immediate right
                totalRed = totalRed + matrix[i][right].rgbtRed;
                totalBlue = totalBlue + matrix[i][right].rgbtBlue;
                totalGreen = totalGreen + matrix[i][right].rgbtGreen;
                counter++;
            }

            //Check Diagonals
            if(up>=0 && left>=0){
                //TopleftDiagonal
                totalRed = totalRed + matrix[up][left].rgbtRed;
                totalBlue = totalBlue + matrix[up][left].rgbtBlue;
                totalGreen = totalGreen + matrix[up][left].rgbtGreen;
                counter++;
            }
            if(up>=0 && right<width){
                //TopRightDiagonal
                totalRed = totalRed + matrix[up][right].rgbtRed;
                totalBlue = totalBlue + matrix[up][right].rgbtBlue;
                totalGreen = totalGreen + matrix[up][right].rgbtGreen;
                counter++;
            }
            if(down<height && right<width){
                //BottomRightDiagonal
                totalRed = totalRed + matrix[down][right].rgbtRed;
                totalBlue = totalBlue + matrix[down][right].rgbtBlue;
                totalGreen = totalGreen + matrix[down][right].rgbtGreen;
                counter++;
            }
            if(down<height && left>=0){
                //BottomLeftDiagonal
                totalRed = totalRed + matrix[down][left].rgbtRed;
                totalBlue = totalBlue + matrix[down][left].rgbtBlue;
                totalGreen = totalGreen + matrix[down][left].rgbtGreen;
                counter++;
            }

            counter++;

            totalRed = totalRed + matrix[i][j].rgbtRed;
            totalBlue = totalBlue + matrix[i][j].rgbtBlue;
            totalGreen = totalGreen + matrix[i][j].rgbtGreen;

            avgRed = (float)(totalRed)/counter;
            avgRed = round(avgRed);

            avgBlue = (float)(totalBlue)/counter;
            avgBlue = round(avgBlue);

            avgGreen = (float)(totalGreen)/counter;
            avgGreen = round(avgGreen);

            image[i][j].rgbtRed = avgRed;
            image[i][j].rgbtBlue = avgBlue;
            image[i][j].rgbtGreen = avgGreen;

            totalRed = 0;
            totalBlue = 0;
            totalGreen = 0;
        }
    }
    free(matrix);
    return;
}
