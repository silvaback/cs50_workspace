#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char encode(char x, int y);

int main(int argc, string argv[])
{
    if(argc != 2)
        {
            printf("Usage: caesar <key>\n");
            return 1;
        }
        
    int key = atoi(argv[1]);
    if (key < 0)
        {
            printf("Key must be a non-negative integer.\n");
            return 1;
        }
    else
    {
        string text = GetString();
        for(int i = 0, j = strlen(text); i < j; i++)
        printf("%c", encode(text[i], key));
    }
    printf("\n");
}

char encode(char x, int y)
{
    if (!isalpha(x))
        return x;
    else if (isupper(x))
    {
        x -= 65;
        x = (x + y) % 26;
        x += 65;
        return x;
    }
    else
    {
        x -= 97;
        x = (x + y) % 26;
        x += 97;
        return x;
    }
}