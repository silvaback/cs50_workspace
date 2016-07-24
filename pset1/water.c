#include <stdio.h>
#include <cs50.h>

int main(void)
{
    printf("minutes: ");
    int m = GetInt();
    printf("bottles: %i\n", m * 12);
}