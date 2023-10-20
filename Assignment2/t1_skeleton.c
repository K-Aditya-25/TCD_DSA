#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "t1.h"

//Fills the array with ascending, consecutive numbers, starting from 0.
void fill_ascending(int *array, int size)
{
    //TODO
    // array = (int*)(malloc(sizeof(int) * size));
    for (int i = 0; i < size; i++)
    {
        array[i] = i;
    }
    return;
}
//Fills the array with descending numbers, starting from size-1
void fill_descending(int *array, int size)
{
    //TODO
    for (int i = size - 1; i >= 0; i--)
    {
        array[size - i - 1] = i;
    }
    return;
}

//Fills the array with uniform numbers.
void fill_uniform(int *array, int size)
{
    //TODO
    srand(time(NULL));
    int n = rand() % size;
    for (int i = size - 1; i >= 0; i--)
    {
        array[i] = n;
    }
    return;
    
}

//Fills the array with random numbers within 0 and size-1. Duplicates are allowed.
void fill_with_duplicates(int *array, int size)
{
    //TODO
    srand(time(NULL) + (int)array);
    int n = 0;
    for (int i = 0; i < size; i++)
    {
        n = rand() % size;
        array[i] = n;
    }
    return;
    
}


//Fills the array with unique numbers between 0 and size-1 in a shuffled order. Duplicates are not allowed.
void fill_without_duplicates(int *array, int size)
{
    //TODO
    srand(time(NULL) + (int)array);
    for (int i = 0; i < size; i++)
    {
        int n = rand() % size;
        int j = i - 1;
        while (j >= 0)
        {
            if (array[j] == n)
            {
                j = i - 1;
                n = rand() % size;
                continue;
            }
            j--;
        }
        array[i] = n;
    }
    return;
    
}

void printArray(int* arr, int size){
  int i;
  for(i=0; i<size;i++){
    printf("%d ", arr[i]);
  }
  printf("\n");
}

