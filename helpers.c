#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate average of pixel channel values
            double average = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/3.0;
           
            // Change old channel values to average
            image[i][j].rgbtBlue = (int) round(average);
            image[i][j].rgbtGreen = (int) round(average);
            image[i][j].rgbtRed = (int) round(average);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double sepiaBlue = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            
            double sepiaGreen = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            
            
            double sepiaRed = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            
            image[i][j].rgbtRed = round(sepiaRed);
            image[i][j].rgbtGreen = round(sepiaGreen);
            image[i][j].rgbtBlue = round(sepiaBlue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE swap[height][width];
    
    for (int k = 0; k < height; k++)
    {
        for (int i = 0; i < width / 2; i++)
        {
            for (int j = width - 1; j >= width / 2; j--)
            {
                swap[k][i] = image[k][i];
                image[k][i] = image[k][j];
                image[k][j] = swap[k][i];
                
                i++;
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE swap[height][width];
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            swap[i][j] = image[i][j];
        }
    }
    
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            if (h == 0 && w == 0)
            {
                image[h][w].rgbtRed = round((swap[h][w].rgbtRed + swap[h][w+1].rgbtRed + swap[h+1][w].rgbtRed + swap[h+1][w+1].rgbtRed)/4.0);
                image[h][w].rgbtGreen = round((swap[h][w].rgbtGreen + swap[h][w+1].rgbtGreen + swap[h+1][w].rgbtGreen + swap[h+1][w+1].rgbtGreen)/4.0);
                image[h][w].rgbtBlue = round((swap[h][w].rgbtBlue + swap[h][w+1].rgbtBlue + swap[h+1][w].rgbtBlue + swap[h+1][w+1].rgbtBlue)/4.0);
            }
            
            else if (h == 0 && w != 0 && w != width)
            {
                image[h][w].rgbtRed = round((swap[h][w-1].rgbtRed + swap[h][w].rgbtRed + swap[h][w+1].rgbtRed + swap[h+1][w-1].rgbtRed + swap[h+1][w].rgbtRed + swap[h+1][w+1].rgbtRed)/6.0);
                image[h][w].rgbtGreen = round((swap[h][w-1].rgbtGreen + swap[h][w].rgbtGreen + swap[h][w+1].rgbtGreen + swap[h+1][w-1].rgbtGreen + swap[h+1][w].rgbtGreen + swap[h+1][w+1].rgbtGreen)/6.0);
                image[h][w].rgbtBlue = round((swap[h][w-1].rgbtBlue + swap[h][w].rgbtBlue + swap[h][w+1].rgbtBlue + swap[h+1][w-1].rgbtBlue + swap[h+1][w].rgbtBlue + swap[h+1][w+1].rgbtBlue)/6.0);
            }
            
            else if (h == 0 && w == width - 1)
            {
                image[h][w].rgbtRed = round((swap[h][w-1].rgbtRed + swap[h][w].rgbtRed + swap[h+1][w-1].rgbtRed + swap[h+1][w].rgbtRed)/4.0);
                image[h][w].rgbtGreen = round((swap[h][w-1].rgbtGreen + swap[h][w].rgbtGreen + swap[h+1][w-1].rgbtGreen + swap[h+1][w].rgbtGreen)/4.0);
                image[h][w].rgbtBlue = round((swap[h][w-1].rgbtBlue + swap[h][w].rgbtBlue + swap[h+1][w-1].rgbtBlue + swap[h+1][w].rgbtBlue)/4.0);
            }
            
            else if (h == height - 1 && w == 0)
            {
                image[h][w].rgbtRed = round((swap[h-1][w].rgbtRed + swap[h-1][w+1].rgbtRed + swap[h][w].rgbtRed + swap[h][w+1].rgbtRed)/4.0);
                image[h][w].rgbtGreen = round((swap[h-1][w].rgbtGreen + swap[h-1][w+1].rgbtGreen + swap[h][w].rgbtGreen + swap[h][w+1].rgbtGreen)/4.0);
                image[h][w].rgbtBlue = round((swap[h-1][w].rgbtBlue + swap[h-1][w+1].rgbtBlue + swap[h][w].rgbtBlue + swap[h][w+1].rgbtBlue)/4.0);
            }
            
            else if (h == height - 1 && w != 0 && w != width -1)
            {
                image[h][w].rgbtRed = round((swap[h-1][w-1].rgbtRed + swap[h-1][w].rgbtRed + swap[h-1][w+1].rgbtRed + swap[h][w-1].rgbtRed + swap[h][w].rgbtRed + swap[h][w+1].rgbtRed)/6.0);
                image[h][w].rgbtGreen = round((swap[h-1][w-1].rgbtGreen + swap[h-1][w].rgbtGreen + swap[h-1][w+1].rgbtGreen + swap[h][w-1].rgbtGreen + swap[h][w].rgbtGreen + swap[h][w+1].rgbtGreen)/6.0);
                image[h][w].rgbtBlue = round((swap[h-1][w-1].rgbtBlue + swap[h-1][w].rgbtBlue + swap[h-1][w+1].rgbtBlue + swap[h][w-1].rgbtBlue + swap[h][w].rgbtBlue + swap[h][w+1].rgbtBlue)/6.0);
            }
            
            else if (h == height -1 && w == width -1)
            {
                image[h][w].rgbtRed = round((swap[h-1][w-1].rgbtRed + swap[h-1][w].rgbtRed + swap[h][w-1].rgbtRed + swap[h][w].rgbtRed)/4.0);
                image[h][w].rgbtGreen = round((swap[h-1][w-1].rgbtGreen + swap[h-1][w].rgbtGreen + swap[h][w-1].rgbtGreen + swap[h][w].rgbtGreen)/4.0);
                image[h][w].rgbtBlue = round((swap[h-1][w-1].rgbtBlue + swap[h-1][w].rgbtBlue + swap[h][w-1].rgbtBlue + swap[h][w].rgbtBlue)/4.0);
            }
            
            else if (h != 0 && h != height -1 && w == 0)
            {
                image[h][w].rgbtRed = round((swap[h-1][w].rgbtRed + swap[h-1][w+1].rgbtRed + swap[h][w].rgbtRed + swap[h][w+1].rgbtRed + swap[h+1][w].rgbtRed + swap[h+1][w+1].rgbtRed)/6.0);
                image[h][w].rgbtGreen = round((swap[h-1][w].rgbtGreen + swap[h-1][w+1].rgbtGreen + swap[h][w].rgbtGreen + swap[h][w+1].rgbtGreen + swap[h+1][w].rgbtGreen + swap[h+1][w+1].rgbtGreen)/6.0);
                image[h][w].rgbtBlue = round((swap[h-1][w].rgbtBlue + swap[h-1][w+1].rgbtBlue + swap[h][w].rgbtBlue + swap[h][w+1].rgbtBlue + swap[h+1][w].rgbtBlue + swap[h+1][w+1].rgbtBlue)/6.0);
            }
            
            else if (h != 0 && h != height -1 && w == width -1)
            {
                image[h][w].rgbtRed = round((swap[h-1][w-1].rgbtRed + swap[h-1][w].rgbtRed + swap[h][w-1].rgbtRed + swap[h][w].rgbtRed + swap[h+1][w-1].rgbtRed + swap[h+1][w].rgbtRed)/6.0);
                image[h][w].rgbtGreen = round((swap[h-1][w-1].rgbtGreen + swap[h-1][w].rgbtGreen + swap[h][w-1].rgbtGreen + swap[h][w].rgbtGreen + swap[h+1][w-1].rgbtGreen + swap[h+1][w].rgbtGreen)/6.0);
                image[h][w].rgbtBlue = round((swap[h-1][w-1].rgbtBlue + swap[h-1][w].rgbtBlue + swap[h][w-1].rgbtBlue + swap[h][w].rgbtBlue + swap[h+1][w-1].rgbtBlue + swap[h+1][w].rgbtBlue)/6.0);
            }
            
            else
            {
                image[h][w].rgbtRed = round((swap[h - 1][w - 1].rgbtRed + swap[h - 1][w].rgbtRed + swap[h - 1][w + 1].rgbtRed + swap[h][w - 
                1].rgbtRed + swap[h][w].rgbtRed + swap[h][w + 1].rgbtRed + swap[h + 1][w - 1].rgbtRed + swap[h+1][w].rgbtRed + swap[h + 1][w +1 ].rgbtRed) / 9.0);
                image[h][w].rgbtGreen = round((swap[h - 1][w - 1].rgbtGreen + swap[h -1 ][w].rgbtGreen + swap[h - 1][w + 1].rgbtGreen + swap[h][w - 1].rgbtGreen
                + swap[h][w].rgbtGreen + swap[h][w + 1].rgbtGreen + swap[h + 1][w - 1].rgbtGreen + swap[h + 1][w].rgbtGreen + swap[h + 1][w + 1].rgbtGreen) / 9.0);
                image[h][w].rgbtBlue = round((swap[h - 1][w - 1].rgbtBlue + swap[h - 1][w].rgbtBlue + swap[h - 1][w + 1].rgbtBlue + swap[h][w - 1].rgbtBlue + 
                swap[h][w].rgbtBlue + swap[h][w + 1].rgbtBlue + swap[h + 1][w - 1].rgbtBlue + swap[h +1 ][w].rgbtBlue + swap[h + 1][w + 1].rgbtBlue) / 9.0);
            }
        }
    }
    return;
}
