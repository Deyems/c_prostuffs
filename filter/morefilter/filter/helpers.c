#include "helpers.h"
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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // RGBTRIPLE matrix[height][];
    RGBTRIPLE(*matrix)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    //Keep a Copy of image values
    for(int row = 0; row < height; row++){
        for(int col = 0; col < width; col++){
            matrix[row][col].rgbtRed = image[row][col].rgbtRed;
            matrix[row][col].rgbtGreen = image[row][col].rgbtGreen;
            matrix[row][col].rgbtBlue = image[row][col].rgbtBlue;
            // printf("Red Val: %i\n",matrix[row][col].rgbtRed);
        }
    }

    int kernelX[3][3] = {
        {-1,0,1},
        {-2,0,2},
        {-1,0,1}
    };

    int kernelY[3][3] = {
        {-1,-2,-1},
        {0,0,0},
        {1,2,1}
    };


    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){

            int xComponentR = 0; int yComponentR = 0;
            int xComponentG = 0; int yComponentG = 0;
            int xComponentB = 0; int yComponentB = 0;

            if(i+1 < height ){
                //Immediately beneath
                xComponentR = xComponentR + 0*matrix[i+1][j].rgbtRed;
                yComponentR = yComponentR + 2*matrix[i+1][j].rgbtRed;

                xComponentG = xComponentG + 0*matrix[i+1][j].rgbtGreen;
                yComponentG = yComponentG + 2*matrix[i+1][j].rgbtGreen;

                xComponentB = xComponentB + 0*matrix[i+1][j].rgbtBlue;
                yComponentB = yComponentB + 2*matrix[i+1][j].rgbtBlue;
            }

            if(i-1 >= 0 ){
                //Immediately Above
                xComponentR = xComponentR + 0*matrix[i-1][j].rgbtRed;
                yComponentR = yComponentR + -2*matrix[i-1][j].rgbtRed;

                xComponentG = xComponentG + 0*matrix[i-1][j].rgbtGreen;
                yComponentG = yComponentG + -2*matrix[i-1][j].rgbtGreen;

                xComponentB = xComponentB + 0*matrix[i-1][j].rgbtBlue;
                yComponentB = yComponentB + -2*matrix[i-1][j].rgbtBlue;
            }

            if(j-1 >= 0 ){
                //Immediately to the LEFT
                xComponentR = xComponentR + -2*matrix[i][j-1].rgbtRed;
                yComponentR = yComponentR + 0*matrix[i][j-1].rgbtRed;

                xComponentG = xComponentG + -2*matrix[i][j-1].rgbtGreen;
                yComponentG = yComponentG + 0*matrix[i][j-1].rgbtGreen;

                xComponentB = xComponentB + -2*matrix[i][j-1].rgbtBlue;
                yComponentB = yComponentB + 0*matrix[i][j-1].rgbtBlue;
            }

            if(j+1 < width ){
                //Immediately to the RIGHT
                xComponentR = xComponentR + 2*matrix[i][j+1].rgbtRed;
                yComponentR = yComponentR + 0*matrix[i][j+1].rgbtRed;

                xComponentG = xComponentG + 2*matrix[i][j+1].rgbtGreen;
                yComponentG = yComponentG + 0*matrix[i][j+1].rgbtGreen;

                xComponentB = xComponentB + 2*matrix[i][j+1].rgbtBlue;
                yComponentB = yComponentB + 0*matrix[i][j+1].rgbtBlue;
            }

            if(i-1 >=0 && j-1 >= 0 ){
                //Top Diagonal Left
                xComponentR = xComponentR + -1*matrix[i-1][j-1].rgbtRed;
                yComponentR = yComponentR + -1*matrix[i-1][j-1].rgbtRed;

                xComponentG = xComponentG + -1*matrix[i-1][j-1].rgbtGreen;
                yComponentG = yComponentG + -1*matrix[i-1][j-1].rgbtGreen;

                xComponentB = xComponentB + -1*matrix[i-1][j-1].rgbtBlue;
                yComponentB = yComponentB + -1*matrix[i-1][j-1].rgbtBlue;
            }

            if(i-1 >= 0 && j+1 < width ){
                //Top Diagonal Right
                xComponentR = xComponentR + 1*matrix[i-1][j+1].rgbtRed;
                yComponentR = yComponentR + -1*matrix[i-1][j+1].rgbtRed;

                xComponentG = xComponentG + 1*matrix[i-1][j+1].rgbtGreen;
                yComponentG = yComponentG + -1*matrix[i-1][j+1].rgbtGreen;

                xComponentB = xComponentB + 1*matrix[i-1][j+1].rgbtBlue;
                yComponentB = yComponentB + -1*matrix[i-1][j+1].rgbtBlue;
            }

            if(i+1 < height &&  j-1>=0 ){
                //Bottom Diagonal Left
                xComponentR = xComponentR + -1*matrix[i+1][j-1].rgbtRed;
                yComponentR = yComponentR + 1*matrix[i+1][j-1].rgbtRed;

                xComponentG = xComponentG + -1*matrix[i+1][j-1].rgbtGreen;
                yComponentG = yComponentG + 1*matrix[i+1][j-1].rgbtGreen;

                xComponentB = xComponentB + -1*matrix[i+1][j-1].rgbtBlue;
                yComponentB = yComponentB + 1*matrix[i+1][j-1].rgbtBlue;
            }

            if(i+1<height  && j+1<width ){
                //Bottom Diagonal Right
                xComponentR = xComponentR + 1*matrix[i+1][j+1].rgbtRed;
                yComponentR = yComponentR + 1*matrix[i+1][j+1].rgbtRed;

                xComponentG = xComponentG + 1*matrix[i+1][j+1].rgbtGreen;
                yComponentG = yComponentG + 1*matrix[i+1][j+1].rgbtGreen;

                xComponentB = xComponentB + 1*matrix[i+1][j+1].rgbtBlue;
                yComponentB = yComponentB + 1*matrix[i+1][j+1].rgbtBlue;
            }

                //Add up the Current Location too
                xComponentR = xComponentR + 0*matrix[i][j].rgbtRed;
                yComponentR = yComponentR + 0*matrix[i][j].rgbtRed;

                xComponentG = xComponentG + 0*matrix[i][j].rgbtGreen;
                yComponentG = yComponentG + 0*matrix[i][j].rgbtGreen;

                xComponentB = xComponentB + 0*matrix[i][j].rgbtBlue;
                yComponentB = yComponentB + 0*matrix[i][j].rgbtBlue;

                double realxComponentR = (double)xComponentR;
                double realxComponentG = (double)xComponentG;
                double realxComponentB = (double)xComponentB;

                double realyComponentR = (double)yComponentR;
                double realyComponentG = (double)yComponentG;
                double realyComponentB = (double)yComponentB;

                double sobelManR = sqrt(pow(realxComponentR,2) + pow(realyComponentR,2));
                double sobelManG = sqrt(pow(realxComponentG,2) + pow(realyComponentG,2));
                double sobelManB = sqrt(pow(realxComponentB,2) + pow(realyComponentB,2));

                sobelManR = round(sobelManR);
                sobelManG = round(sobelManG);
                sobelManB = round(sobelManB);

                if(sobelManR > 255) {sobelManR = 255;}
                if(sobelManG > 255) {sobelManG = 255;}
                if(sobelManB > 255) {sobelManB = 255;}

                image[i][j].rgbtRed = sobelManR;
                image[i][j].rgbtGreen = sobelManG;
                image[i][j].rgbtBlue = sobelManB;

        }
    }


    free(matrix);
    return;
}
