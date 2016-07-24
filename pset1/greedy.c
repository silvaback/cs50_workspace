#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    printf("O hai! How much change is owed?\n");
    float change = GetFloat();
    int pennies;
    int coins = 0;
    
    while (change < 0)
    {
        printf("How much change is owed?\n");
        change = GetFloat();
    }
    
    change = change * 100.00;
    change = roundf(change);
    pennies = change;
    
    
    while (pennies >= 25)
    {
        pennies = pennies - 25;
        coins++;
    }
    while (pennies >= 10)
    {
        pennies = pennies - 10;
        coins++;
    }
    while (pennies >= 5)
    {
        pennies = pennies - 5;
        coins++;
    }
    while (pennies >= 1)
    {
        pennies--;
        coins++;
    }
    printf("%i\n", coins);
}