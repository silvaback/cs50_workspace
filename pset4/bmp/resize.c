/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize factor infile outfile\n");
        return 1;
    }
    
    //remember resize factor
    int factor = atoi(argv[1]);

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];
    
    //checks to make sure that factor in a positive integer between 1 and 100
    if (factor < 1 || factor > 100)
    {
        printf("Your factor for resizing should be between 0 and 100 inclusive\n");
        return 2;
    }

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    // find original padding
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // creating new variable for output file and info header
    BITMAPINFOHEADER biout = bi;
    BITMAPFILEHEADER bfout = bf;
    
    // changing width and length 
    biout.biWidth *= factor;
    biout.biHeight *= factor;
    
    // determine padding for scanlines
    int paddingout = (4 - (biout.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    bfout.bfSize = 54 + ((biout.biWidth * abs(biout.biHeight)) * 3) + (abs(biout.biHeight) * paddingout);
    biout.biSizeImage = bfout.bfSize - 54;
 

    // write outfile's BITMAPFILEHEADER
    fwrite(&bfout, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&biout, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        //array for a copy of the whole line
        RGBTRIPLE tripleline[biout.biWidth];
        int l = 0;
        
        //array for the padding of the whole line.
        BYTE padline[paddingout];
        
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;
            RGBTRIPLE tripleout[factor];

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                        
            //copying each pixel factor times to tripleout
            for (int x = 0; x < factor; x++)
            {
                tripleout[x] = triple;
                tripleline[l] = triple;
                l++;
            }

            // write RGB tripleout to outfile
            fwrite(&tripleout, sizeof(RGBTRIPLE), factor, outptr);
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how) and adding it to padline
        for (int k = 0; k < paddingout; k++)
        {
            fputc(0x00, outptr);
            padline[k] = 0x00;
        }
        
        //iterating over the number of scanlines that we need to copy.
        for (int p = 1; p < factor; p++)
        {
            fwrite(&tripleline, sizeof(RGBTRIPLE), biout.biWidth, outptr);
            fwrite(&padline, sizeof(BYTE), paddingout, outptr);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
