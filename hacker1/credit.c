#include <cs50.h>
#include <stdio.h>
#include <math.h>



int main(void)
{
    long long creditcard;
    int length;
    int digitsum = 0;
    bool valid;
    int firsttwo;
    
    //gets credit card number
    printf("Number: ");
    creditcard = GetLongLong();
    length = log10(creditcard) + 1; //gets length of credit card number
    
    //checks to make sure length is valid for a credit card
    if (length < 13 || length > 16 || length == 14)
    {
        printf("INVALID\n");
        return 0; //ends program if not valid length
    }
    
    //creates an int containing the first two digits of card
    firsttwo = (creditcard / (long long)pow(10, length - 2)) % 100;
    
    //sums the digits of every second digit * 2 starting right to left
    for (int i = 1; i <= length;i += 2)
    {
        int part1 = ((creditcard / (long long)pow(10, i)) % 10) * 2;
        int digits = 0;
        if (part1 >= 10)
        {
            //breaks numbers > 10 into its individual digits.
            for (int x = 0; x < 2; x++)
            {
                digits += (part1/(int)pow(10, x)) % 10;
            }
            digitsum += digits;
        }
        else
        {
        digitsum += part1;
        }
    }
    
    //same as the for loop above but starting from the first number on right
    for (int i = 0; i <= length;i += 2)
    {
        digitsum += (creditcard / (long long)pow(10, i)) % 10;
    }

    valid = !(digitsum % 10);//if the remainder is 0 assigns true

    if (valid)
    {
        //prints appropriate card type
        switch (firsttwo)
        {
            case 34:
                printf("AMEX\n");
                break;
            case 37:
                printf("AMEX\n");
                break;
            case 40:
            case 41:
            case 42:
            case 43:
            case 44:
            case 45:
            case 46:
            case 47:
            case 48:
            case 49:
                printf("VISA\n");
                break;
            case 51:
            case 52:
            case 53:
            case 54:
            case 55:
                printf("MASTERCARD\n");
                break;
            default:
                printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID");
    }
    
    return 0;

}


