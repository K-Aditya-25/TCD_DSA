#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 200
int next_field(FILE *csv, char *buffer, int max_len);

int main(int argc, char *argv[])
{
    FILE *csv = fopen(argv[1], "r");
    if (csv == NULL)
    {
        return -1;
    }
    char buffer[MAX_LEN] = {};
    int count = 1;
    while(!feof(csv))
    {
        int ans = next_field(csv, buffer, MAX_LEN);
        if(ans == 0)
        {
            if (count == 1)
            {
                continue;
            }
            printf("%s \n", buffer);
            strcpy(buffer, "");
        }
        if(ans == 1)
        {
            if (count == 1)
            {
                count++;
                continue;
            }
            printf("%s\n\n", buffer);
            strcpy(buffer, "");
        }
    }
    fclose(csv);
    return 0;
}

int next_field(FILE *csv, char *buffer, int max_len)
{
    char c = fgetc(csv);
    int fieldIndex = 0;
    int quotes = 0;
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