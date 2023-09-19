#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // verificar que hoy dos argumento (argc = 2).
    // retornar 1 si no.
    if (argc != 2)
    {
        printf("Usage: ./recover [archivo]\n");
        return 1;
    }


    //meto el archivo en pointer file, si este es igual a null, le informo al usuario y retorno 1.

    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        printf("Could not open the file %s\n", argv[1]);
        return 1;
    }

    uint8_t buffer[256];
    /* if (buffer == NULL)
    {
        printf("Not enough memory\n");
        return 1;
    } */

    char *nombre = malloc(sizeof(char) * 8);
    if (nombre == NULL)
    {
        printf("Not enough memory\n");
        return 1;
    }

    int contador_nombre = -1;


    sprintf(nombre, "%03i.jpg", contador_nombre + 1);
    FILE *outptr = fopen(nombre, "w");

    while (fread(&buffer, sizeof(uint8_t), 256, inptr) == 256)
    {


        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] >= 0xe0 && buffer[3] <= 0xef))
        {
            if (contador_nombre < 0)
            {
                fwrite(&buffer, sizeof(uint8_t), 256, outptr);
                contador_nombre++;
                continue;

            }

            else
            {
                fclose(outptr);
                //(contador_nombre != 1) && (contador_nombre++);
                contador_nombre++;
                sprintf(nombre, "%03i.jpg", contador_nombre);
                outptr = fopen(nombre, "w");
                fwrite(&buffer, sizeof(uint8_t), 256, outptr);

            }
        }

        else if (contador_nombre >= 0)
        {
            fwrite(&buffer, 1, 256, outptr);
        }



    }
    fclose(outptr);
    fclose(inptr);
    free(nombre);
    //free(buffer);
    return 0;







    //Usar la función para crear el archivo.



}


//función para crear el archivo.