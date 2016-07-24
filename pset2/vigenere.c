#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char encode(char x, string keyword, int klen);
bool notalpha(string x);
int getkey(char k);

int keycharind = 0;

int main(int argc, string argv[])
{
    if(argc != 2)
    {
        printf("Usage: caesar <keyword>\n");
        return 1;
    }
    else if (notalpha(argv[1]))
    {
        printf("Keyword must only contain letters A-Z and a-z.\n");
        return 1;
    }
    else
    {
        string text = GetString();
        for(int i = 0, j = strlen(text), klen = strlen(argv[1]); i < j; i++)
        printf("%c", encode(text[i], argv[1], klen));
    }
    printf("\n");
}



char encode(char x, string keyword, int klen)
{
    if (!isalpha(x))
        return x;
    else if (isupper(x))
    {
        x -= 65;
        x = (x + getkey(keyword[keycharind % klen])) % 26;
        x += 65;
        keycharind++;
        return x;
    }
    else
    {
        x -= 97;
        x = (x + getkey(keyword[keycharind % klen])) % 26;
        x += 97;
        keycharind++;
        return x;
    }
}


bool notalpha(string x)
{
    for (int i = 0, j = strlen(x); i < j; i++)
    {
        if (!isalpha(x[i]))
            return true;
    }
    
    return false;
}



int getkey(char k)
{
    if (isupper(k))
    {
        k -= 65;
        return k;
    }
    else
    {
        k -= 97;
        return k;
    }
} 