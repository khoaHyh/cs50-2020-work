#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// FAT file system block size
#define BLOCK_SIZE 512

// New type to store a byte of data
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check usage
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Open file
    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        printf("Forensic image cannot be opened for reading\n");
        return 1;
    }

    // Memory card buffer
    BYTE buffer[BLOCK_SIZE];

    // JPEG name buffer
    char filename[8];

    // Initialize image file pointer
    FILE *img = NULL;

    // Counts how many JPEG files there are
    int jpeg_count = 0;

    // Read 512B chunks and repeat until end of file
    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        // If start of new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If not the first JPEG, close the current one and open up a new one
            if (jpeg_count != 0)
            {
                fclose(img);
            }
            // Make a new JPEG
            sprintf(filename, "%03i.jpg", jpeg_count);
            img = fopen(filename, "w");
            if (!img)
            {
                return 1;
            }
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, img);
            jpeg_count++;
        }
        // If already found JPEG
        else if (jpeg_count != 0)
        {
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, img);
        }
    }
    // Close files
    fclose(file);
    fclose(img);
}