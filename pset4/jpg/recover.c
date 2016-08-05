/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
 
 #include <stdio.h>
 #include <stdint.h>
 
 #define Block 512
 
 typedef uint8_t  BYTE;


int main(int argc, char* argv[])
{
    // open forensic image
    FILE* file = fopen("card.raw", "r");
    FILE* jpg[50];
    
    //create block buffer
    BYTE buffer[Block];
    
    //create name counter and buffer
    int jpgcount = -1;
    char jpgname[8];
    
    //create bool to see if image has been found
    char picturefound = 0;
    
    //read block of image
    while (fread(&buffer, sizeof(BYTE), Block, file))
    {
        // check to see if first three bytes follow jpg file format
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff)
        {
            // check to see if first half of fourth byte starts with e
            switch (buffer[3])
            {
                case 0xe0:
                case 0xe1:
                case 0xe2:
                case 0xe3:
                case 0xe4:
                case 0xe5:
                case 0xe6:
                case 0xe7:
                case 0xe8:
                case 0xe9:
                case 0xea:
                case 0xeb:
                case 0xec:
                case 0xed:
                case 0xee:
                case 0xef:
                {
                    // closes jpg if previosly found
                    if (picturefound == 1)
                        fclose(jpg[jpgcount]);
                     
                    // adds count to jpg
                    jpgcount++;
                        
                    //print jpgname into buffer
                    sprintf(jpgname, "%.3d.jpg", jpgcount);
                    
                    //mark picture found as true
                    picturefound = 1;
                    
                    //open new file
                    jpg[jpgcount] = fopen(jpgname, "w");
                }
            }
        } 
        
    if (picturefound != 0)
        fwrite(&buffer, sizeof(BYTE), Block, jpg[jpgcount]);

    }
    
    fclose(file);
    
    
    
}
