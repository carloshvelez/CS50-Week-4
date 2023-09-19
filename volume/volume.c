// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    // Para hacer esto, simplemente uso fread para leer los primeros 44 bytes, lo guardo en un array y luego esto lo copio en el nuevo archivo con y fwrite para escribirlos en el nuevo archivo.
    int i = 0;
    int *copia_header = malloc(44);
    fread(copia_header, 1, 44, input);
    fwrite(copia_header, 1, 44, output);
    free(copia_header);




    // TODO: Read samples from input file and write updated data to output file
    // para hacer esto: defino un array con memoria dinámica.
    // copio el archivo, desde 44 (usando seek) hasta el final.
    // por cada 2 bytes multiplico por el factor.
    // scribo en el archivo output mediante fput, desde 44 hasta el final.
    // libero la memoria que usé en el array.

    // Desde 45 hasta eof: copio en una variable, la multiplico por factor y pego en el nuevo archivo

    //fseek(input, 45, SEEK_SET);

    int16_t buffer;
    while (fread(&buffer, 1, 2, input) == 2)
    {
        buffer *= factor;
        fwrite(&buffer, 1, 2, output);
    }
    //free(buffer);


    // Close files
    fclose(input);
    fclose(output);
}
