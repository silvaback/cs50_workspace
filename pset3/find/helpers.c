/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

bool binarysearch(int value, int values[], int min, int max);
int midpoint(int min, int max);

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    if (n < 0)
        return false;
    else
    {
        //for(int i = 0; i < n; i++)
        //{
        return (binarysearch(value, values, 0, n - 1));
        //        return true;
        //}
        //return false;
    }
    
    
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    int sorted;
    int max = n - 1;
    int temp;
    
    do
    {
        sorted = 0;
        for (int i = 0; i < max; i++)
        {
            if (values[i] > values[i + 1])
            {
                temp = values[i + 1];
                values[i + 1] = values[i];
                values[i] = temp;
                sorted++;
            }
        }
        max--;
    }
    while (sorted != 0);
        
    return;
}

bool binarysearch(int value, int values[], int min, int max)
{
    if (min > max)
        return false;
    else
    {
        int mid = midpoint(min, max);
        
        if (value < values[mid])
            return binarysearch(value, values, min, mid - 1);
        else if (value > values[mid])
            return binarysearch(value, values, mid + 1, max);
        else
            return true;
    }
}

int midpoint(int min, int max)
{
    int x;
    x = min + ((max - min)/2);
    return x;
}