#include "t1.h"
#include "t2.h"
#include <stdio.h>
#include <stdlib.h>


int main()
{
    //TODO test your functions here
    int size = 10;
    int *a = (int*)(malloc(sizeof(int)*size));
    fill_without_duplicates(a, size);
    printArray(a, size);
    selectionSort(a, size);
    printArray(a, size);
    free(a);
}