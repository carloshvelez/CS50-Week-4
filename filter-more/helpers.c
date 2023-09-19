#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int media;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            media = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtRed = media;
            image[i][j].rgbtGreen = media;
            image[i][j].rgbtBlue = media;
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
            int r = 0;
            int g = 0;
            int b = 0;
            int contador = 0;

            for (int k2 = k; k2 < l; k2++)
            {
                for (int m2 = m; m2 < n; m2++)
                {
                    r += image[i + k2][j + m2].rgbtRed;
                    g += image[i + k2][j + m2].rgbtGreen;
                    b += image[i + k2][j + m2].rgbtBlue;
                    contador++;
                }
            }
            copia_imagen[i][j].rgbtRed = (int) round(r / (float) contador);
            copia_imagen[i][j].rgbtGreen = (int) round(g / (float) contador);
            copia_imagen[i][j].rgbtBlue = (int) round(b / (float) contador);

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    /* Primero: poner en 0 todos los bordes.
    Segundo: En un loop hacer el cálculo para el resto de pixeles.
    - Encada índice i tendrá un subíndice k que va entre -1 y +1.
    - Cada índice j tendrá un sub índice m que va entre -1 y + 1.
    - El multiplicador gx será igual al índice k * l, el cual será 2 si el índice m es 0, y 1 de lo contrario.
    - El multiplicador gy será igual al índice m * n, el cual será 2 si el índice k es 0 y 1 de lo contrario.
    - Así, gx lo iré sumando de la siguiente forma imagen[i][j].color * indice k*l.
    - El gy es igual pero multiplicaré por el índice m * n.
    - Al final tendré que sumar los cuadrados de gx y gy al cuadrado, y luego sacarles raíz cuadrada. Esto redondeado.
    - Si es mayor que 255, entonces 255.  */
    RGBTRIPLE copia_image[height][width];




    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)

        {
            int k2 = -1, l2 = 2, m2 = -1, n2 = 2;
            if (i == 0)
            {
                k2 = 0;
            }
            if (i == height - 1)
            {
                l2 = 1;
            }
            if (j == 0)
            {
                m2 = 0;
            }
            if (j == width - 1)
            {
                n2 = 1;
            }

            int rx = 0, gx = 0, bx = 0, ry = 0, gy = 0, by = 0, l = 1, n = 1;
            for (int k = k2; k < l2; k++)
            {
                for (int m = m2; m < n2; m++)
                {
                    l = 1, n = 1;
                    if (m == 0)
                    {
                        l = 2;
                    }

                    if (k == 0)
                    {
                        n = 2;
                    }

                    rx += image[i + k][j + m].rgbtRed * (m * n);
                    gx += image[i + k][j + m].rgbtGreen * (m * n);
                    bx += image[i + k][j + m].rgbtBlue * (m * n);
                    ry += image[i + k][j + m].rgbtRed * (k * l);
                    gy += image[i + k][j + m].rgbtGreen * (k * l);
                    by += image[i + k][j + m].rgbtBlue * (k * l);

                }
            }

            float r2 = sqrt(pow(rx, 2.0) + pow(ry, 2.0));
            float g2 = sqrt(pow(gx, 2.0) + pow(gy, 2.0));
            float b2 = sqrt(pow(bx, 2.0) + pow(by, 2.0));

            (r2 > 255) ? (copia_image[i][j].rgbtRed = 255) : (copia_image[i][j].rgbtRed = round(r2));
            (g2 > 255) ? (copia_image[i][j].rgbtGreen = 255) : (copia_image[i][j].rgbtGreen = round(g2));
            (b2 > 255) ? (copia_image[i][j].rgbtBlue = 255) : (copia_image[i][j].rgbtBlue = round(b2));

            /* (sqrt(pow((double)rx, (double)2) + pow((double)ry, (double)2)) > 255) ? (copia_image[i][j].rgbtRed = 255) : (copia_image[i][j].rgbtRed =  round(sqrt(pow((double)rx, (double)2) + pow((double)ry, (double)2))));
            (sqrt(pow((double)gx, (double)2) + pow((double)gy, (double)2)) > 255) ? (copia_image[i][j].rgbtGreen = 255) : (copia_image[i][j].rgbtGreen = round(sqrt(pow((double)gx, (double)2) + pow((double)gy, (double)2))));
            (sqrt(pow((double)bx, (double)2) + pow((double)by, (double)2)) > 255) ? (copia_image[i][j].rgbtBlue = 255) : (copia_image[i][j].rgbtBlue =  round(sqrt(pow((double)bx, (double)2) + pow((double)by, (double)2)))); */
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = copia_image[i][j].rgbtRed;
            image[i][j].rgbtGreen = copia_image[i][j].rgbtGreen;
            image[i][j].rgbtBlue = copia_image[i][j].rgbtBlue;

        }
    }
    return;

}
