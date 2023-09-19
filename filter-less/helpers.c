#include "helpers.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //Para cada pixel crearé una nueva variable uint8_t,
    //la variable será igual a la media de cada color.
    //asignaré esa media a cada color
    uint8_t media;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            media = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = media;
            image[i][j].rgbtGreen = media;
            image[i][j].rgbtRed = media;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int blue;
    int red;
    int green;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            red = round(image[i][j].rgbtRed * 0.393 + image[i][j].rgbtGreen * 0.769 + image[i][j].rgbtBlue * 0.189);
            if (red > 255)
            {
                red = 255;
            }
            green = round(image[i][j].rgbtRed * 0.349 + image[i][j].rgbtGreen * 0.686 + image[i][j].rgbtBlue * 0.168);
            if (green > 255)
            {
                green = 255;
            }
            blue = round(image[i][j].rgbtRed * 0.272 + image[i][j].rgbtGreen * 0.534 + image[i][j].rgbtBlue * 0.131);
            if (blue > 255)
            {
                blue = 255;
            }
            image[i][j].rgbtBlue = blue;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtRed = red;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    uint8_t pr ;
    uint8_t pg ;
    uint8_t pb ;
    //uint8_t *pr2;
    //uint8_t *pg2;
    //uint8_t *pb2;

    for (int i = 0; i < height; i++)
    {
        int index_neg = 1;
        for (int j = 0; j < (int) width / 2; j++)
        {
            pr = image[i][width - index_neg].rgbtRed;
            pg = image[i][width - index_neg].rgbtGreen;
            pb = image[i][width - index_neg].rgbtBlue;


            image[i][width - index_neg].rgbtRed =  image[i][j].rgbtRed;
            image[i][width - index_neg].rgbtGreen =  image[i][j].rgbtGreen;
            image[i][width - index_neg].rgbtBlue =  image[i][j].rgbtBlue;

            image[i][j].rgbtRed = pr;
            image[i][j].rgbtGreen = pg;
            image[i][j].rgbtBlue = pb;
            index_neg++;
        }
    }
    //free(pr);
    //free(pg);
    //free(pb);
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE copia_imagen[height][width];


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int k = -1, l = 2, m = -1, n = 2;
            if (i == 0)
            {
                k = 0;
            }

            if (i == height - 1)
            {
                l = 1;
            }

            if (j == 0)
            {
                m = 0;
            }

            if (j == width - 1)
            {
                n = 1;
            }

            int sumador = 0;

            int red = 0;
            int green = 0;
            int blue = 0;

            for (int k2 = k; k2 < l; k2++)

            {
                for (int m2 = m; m2 < n; m2++)
                {
                    red += image[i + k2][j + m2].rgbtRed;
                    green += image[i + k2][j + m2].rgbtGreen;
                    blue += image[i + k2][j + m2].rgbtBlue;
                    sumador++;

                }
            }
            copia_imagen[i][j].rgbtRed = (int) round(red / (float)sumador);
            copia_imagen[i][j].rgbtGreen = (int) round(green / (float)sumador);
            copia_imagen[i][j].rgbtBlue = (int) round(blue / (float)sumador);
            

        }


    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = copia_imagen[i][j].rgbtRed;
            image[i][j].rgbtGreen = copia_imagen[i][j].rgbtGreen;
            image[i][j].rgbtBlue = copia_imagen[i][j].rgbtBlue;

        }


    }

    return;


}

