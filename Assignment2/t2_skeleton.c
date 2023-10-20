#include <stdio.h> 
#include "t2.h"

int number_comparisons = 0;
int number_swaps = 0;

void swap(int* a, int* b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}
void selectionSort(int arr[], int size) 
{ 
  //TODO
  for(int i = 0; i < size; i++)
  {
    int min_index = i;
    for (int j = i + 1; j < size; j++)
    {
      number_comparisons++;
      if (arr[j] < arr[min_index])
      {
        min_index = j;
        
      }
    }
    swap(&arr[i], &arr[min_index]);
    if (i != min_index)
    {
      number_swaps++;
    }
  }
} 

void insertionSort(int arr[], int size) 
{ 
  //TODO
  for (int i = 1; i < size; i++)
  {
    int key = arr[i];
    int j = i - 1;
    while (j >= 0 && arr[j] > key)
    {
      number_comparisons++;
      arr[j + 1] = arr[j];
      number_swaps++;
      j--;
    }
    number_comparisons++;
    if (arr[j + 1] == key)
    {
      continue;
    }
    arr[j + 1] = key;
  }
  
}

int partition(int arr[], int low, int high)
{
  int pivot = arr[low];
  int i = low;
  int j = high + 1;
  while (i < j)
  {
    do{
      i++;
      number_comparisons++;
    }while (arr[i] < pivot);
    do{
      j--;
      number_comparisons++;
    }while(arr[j] > pivot);
    if (i < j){swap(&arr[i], &arr[j]); number_swaps++;}
  }
  
  swap(&arr[j], &arr[low]);
  number_swaps++;
  return j;

}

void quickSort(int arr[], int size)
{
  quickSort_recursive(arr, 0, size - 1);
}
void quickSort_recursive(int arr[], int p, int r) 
{ 
 //TODO
 if (p < r)
 {
   int q = partition(arr, p, r);
   quickSort_recursive(arr, p, q - 1);
   quickSort_recursive(arr, q + 1, r);
 }
}



