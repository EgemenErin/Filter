#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i <height; i++)
    {
        for(int j = 0; j<width; j++)
        {
            float avarage = (image[i][j].rgbtBlue+image[i][j].rgbtRed+image[i][j].rgbtGreen)/3.0;
            avarage = round(avarage);
            image[i][j].rgbtBlue = avarage;
            image[i][j].rgbtRed = avarage;
            image[i][j].rgbtGreen = avarage;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i <height; i++)
    {
        for(int j = 0; j<width; j++)
        {
            float originalRed = image[i][j].rgbtRed;
            float originalBlue = image[i][j].rgbtBlue;
            float originalGreen = image[i][j].rgbtGreen;
            float sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue;
            float sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue;
            float sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue;
            if(sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if(sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if(sepiaBlue > 255)
            {
                sepiaBlue = 255;
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
      for(int i = 0; i <height; i++)
    {
        int sayac = width;
        for(int j = 0; j<width/2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][sayac-(j+1)];
            image[i][sayac - (j+1)] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE yedek[height][width];
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            yedek[i][j] = image[i][j];
        }
    }
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            float kirmizi;
            float mavi;
            float yesil;
            kirmizi = mavi = yesil = 0;
            float sayac = 0.00;

            for(int z = -1; z < 2; z++)
            {
                for(int x = -1; x < 2; x++) // mentall rn
                {
                    int currenchan = i + z;
                    int currenchan2 = j + x;
                    if(currenchan < 0 || currenchan > (height-1) || currenchan2 <0 || currenchan2 > (width -1))
                    {
                        continue;
                    }
                    kirmizi += image[currenchan][currenchan2].rgbtRed;
                    mavi += image[currenchan][currenchan2].rgbtBlue;
                    yesil += image[currenchan][currenchan2].rgbtGreen;
                    sayac++;
                }
                //calculating avarage
                yedek[i][j].rgbtRed = round(kirmizi/sayac);
                yedek[i][j].rgbtGreen = round(yesil/sayac);
                yedek[i][j].rgbtBlue = round(mavi/sayac);
            }
        }
    }
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = yedek[i][j].rgbtRed;
            image[i][j].rgbtGreen = yedek[i][j].rgbtGreen;
            image[i][j].rgbtBlue = yedek[i][j].rgbtBlue;
        }
    }
    return;
}
