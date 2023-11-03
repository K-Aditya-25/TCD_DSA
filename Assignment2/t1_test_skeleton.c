#include "t1.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    //TODO test your functions here
    int size = 6;
    int* a = (int*)(malloc(sizeof(int) * size));
    int* b = (int*)(malloc(sizeof(int) * size));
    fill_with_duplicates(a, size);
    printArray(a, size);
    fill_with_duplicates(b, size);
    printArray(b, size);
    free(a);
    free(b);
}