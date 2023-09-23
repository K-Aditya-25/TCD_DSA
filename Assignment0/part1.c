#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void)
{
    //declare the initial size of the string name
    int size = 1;

    //declare the name variable; assign one byte to it
    char *name = malloc(size*sizeof(char));

    //declare the age variable
    int age;

    //Resize the name string and store each characters in it one by one
    printf("Name >> ");
    while((name[size - 1] = getchar()) != '\n')
    {
        size++;
        name = realloc(name, size * sizeof(char));
    }

    //Explicitly end the string at name[size - 1], because it stores '\n\ as well in name[size-1]
    name[size - 1] = '\0';

    //Get age and print the answer
    printf("Age >> ");
    scanf("%i", &age);
    printf("Hello %s (%i)",name,age);

    //free the malloc name
    free(name);
}