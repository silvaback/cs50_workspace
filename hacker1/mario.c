#include <stdio.h>
#include <cs50.h>

void prtspc(int x);
void prthash(int y);

int main(void)
{
   int height;
   
   do
   {
       printf("Height: ");
       height = GetInt();
   } 
   while (height < 0 || height > 23);
   
   for (int i = 1; i <= height; i++)
   {
       prtspc(height - i);
       prthash(i);
       printf("  ");
       prthash(i);
      // prtspc(height - i); I see now that this step is unnecessary
       printf("\n");
   }
   
}

void prtspc (int x)
{
    for (int j = 0; j < x; j++)
    {
        printf(" ");
    }
}

void prthash (int y)
{
    for (int j = 0; j < y; j++)
    {
        printf("#");
    }
}