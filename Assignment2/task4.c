#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//global variables
#define MAX_STRING_SIZE 40
#define MAX_ARRAY_SIZE 18626

//define Element struct
typedef struct Element{
    char title[MAX_STRING_SIZE];
    char platform[MAX_STRING_SIZE];
    int score;
    int year;
}Element;

//define functions
int next_field(FILE *csv, char *buffer, int max_len);
void swap_element(Element* a, Element* b);
int partition_element(Element arr[], int low, int high);
void quickSort_element(Element arr[], int p, int r);

//driver code
int main()
{
    FILE* f = fopen("t4_ign.csv", "r");
    char buffer[MAX_STRING_SIZE] = {'\0'};
    Element reviews[MAX_ARRAY_SIZE];
    //ignore the first line
    int ans = next_field(f, buffer, MAX_STRING_SIZE);
    while (ans != 1)
    {
        ans = next_field(f, buffer, MAX_STRING_SIZE);
    }
    //go till end
    int i = 0;
    while(!feof(f))
    {
        strcpy(reviews[i].title, "");
        strcpy(reviews[i].platform, "");
        ans = next_field(f, buffer, MAX_STRING_SIZE);
        strncpy(reviews[i].title, buffer, MAX_STRING_SIZE);

        ans = next_field(f, buffer, MAX_STRING_SIZE);
        strncpy(reviews[i].platform, buffer, MAX_STRING_SIZE);

        ans = next_field(f, buffer, MAX_STRING_SIZE);
        reviews[i].score = atoi(buffer);

        ans = next_field(f, buffer, MAX_STRING_SIZE);
        reviews[i].year = atoi(buffer);
        i++;
    }
    fclose(f);
    quickSort_element(reviews, 0, 18625);
    //print the names and scores of top 10 games
    for (int i = 0; i < 10; i++)
    {
        printf("%i %s: %i\n", i+1, reviews[0].title, reviews[0].score);
    }


    // free(buffer);
    return 0;
}

//actual function definitions
void swap_element(Element* a, Element* b)
{
    //create a temporary element and assign memory to it
    Element temp;
    //start storing values of a in temp
    temp.score = a->score;
    temp.year = a->year;
    strcpy(temp.platform, a->platform);
    strcpy(temp.title, a->title);
    //copy values of b into a
    a->score = b->score;
    a->year = b->year;
    strcpy(a->platform, b->platform);
    strcpy(a->title, b->title);
    //copy values of temp into a
    b->score = temp.score;
    b->year = temp.year;
    strcpy(b->platform, temp.platform);
    strcpy(b->title, temp.title);
}
int partition_element(Element arr[], int low, int high)
{
  int pivot = arr[low].score;
  int i = low;
  int j = high + 1;
  while (i < j)
  {
    do{
      i++;
    }while (arr[i].score < pivot);
    do{
      j--;
    }while(arr[j].score > pivot);
    if (i < j){swap_element(&arr[i], &arr[j]);}
  }
  
  swap_element(&arr[j], &arr[low]);
  return j;
}
void quickSort_element(Element arr[], int p, int r) 
{ 
 //TODO
 if (p < r)
 {
   int q = partition_element(arr, p, r);
   quickSort_element(arr, p, q - 1);
   quickSort_element(arr, q + 1, r);
 }
}

int next_field(FILE *csv, char *buffer, int max_len)
{
    char c = fgetc(csv);
    int fieldIndex = 0;
    int quotes = 0;
    if(feof(csv))
    {
        return 1;
    }
    while(1)
    {
        if(c == '"')
        {
            quotes = 1 - quotes;
            c = fgetc(csv);
            continue;
        }
        if(c == ',')
        {
            if(quotes == 0)
            {
                buffer[fieldIndex] = '\0';
                return 0;
            }
            
        }
        if(c == '\n' || feof(csv))
        {
            buffer[fieldIndex] = '\0';
            return 1;
        }
        if(fieldIndex < max_len)
        {
            buffer[fieldIndex] = c;
            fieldIndex++;
        }
        c = fgetc(csv);
    }
}
