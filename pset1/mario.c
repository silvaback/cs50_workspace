#include <stdio.h>
#include <cs50.h>

int main(void)
{
    printf("Height: ");
    int height = GetInt();
    
    while (height < 0 || height > 23)
    {
        printf("Height: ");
        height = GetInt();
    }
    
    for (int row = height; row > 0; row--)
    {
        //we are breaking up the columns into two loops. one for the spaces and one for the hash tags.
        for (int space = row - 1; space > 0; space--)
        {
            printf(" ");
        }
        for (int hash = height - row; hash > 0; hash--)
        {
            printf("#");
        }
        
        printf("##\n");
    }
    
}

