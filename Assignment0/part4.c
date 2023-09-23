#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 200
int next_field(FILE *csv, char *buffer, int max_len);
typedef struct Pokemon
{
    int s_no;
    char Name[20];
    char Type_1[10];
    char Type_2[10];
    int Total;
    int HP;
    int Attack;
    int Defense;
    int Sp_Atk;
    int Sp_Def;
    int Speed;
    int Generation;
    char Legendary[10];
    char Pokedex_Entry[200];
}Pokemon;


int main(int argc, char *argv[])
{
    FILE *csv = fopen(argv[1], "r");
    if (csv == NULL)
    {
        return -1;
    }
    char buffer[MAX_LEN] = {'\0'};
    struct Pokemon pokemons[649];
    int i = 0;
    //ignore the first line
    int ans = next_field(csv, buffer, MAX_LEN);
    while (ans != 1)
    {
        ans = next_field(csv, buffer, MAX_LEN);
    }
    //go till the end of file
    while(!feof(csv))
    {
        ans = next_field(csv, buffer, MAX_LEN); // 0
        pokemons[i].s_no = atoi(buffer);

        ans = next_field(csv, buffer, MAX_LEN); // 0
        strcpy(pokemons[i].Name, buffer);

        ans = next_field(csv, buffer, MAX_LEN); // 0
        strcpy(pokemons[i].Type_1, buffer);

        ans = next_field(csv, buffer, MAX_LEN); // 0
        strcpy(pokemons[i].Type_2, buffer);

        ans = next_field(csv, buffer, MAX_LEN); // 0
        pokemons[i].Total = atoi(buffer);

        ans = next_field(csv, buffer, MAX_LEN); // 0
        pokemons[i].HP = atoi(buffer);

        ans = next_field(csv, buffer, MAX_LEN); // 0
        pokemons[i].Attack = atoi(buffer);

        ans = next_field(csv, buffer, MAX_LEN); // 0
        pokemons[i].Defense = atoi(buffer);

        ans = next_field(csv, buffer, MAX_LEN); // 0
        pokemons[i].Sp_Atk = atoi(buffer);

        ans = next_field(csv, buffer, MAX_LEN); // 0
        pokemons[i].Sp_Def = atoi(buffer);

        ans = next_field(csv, buffer, MAX_LEN); // 0
        pokemons[i].Speed = atoi(buffer);

        ans = next_field(csv, buffer, MAX_LEN); // 0
        pokemons[i].Generation = atoi(buffer);

        ans = next_field(csv, buffer, MAX_LEN); // 0
        strcpy(pokemons[i].Legendary, buffer);

        ans = next_field(csv, buffer, MAX_LEN); // 1
        strcpy(pokemons[i].Pokedex_Entry, buffer);
        i++;
        
    }
    fclose(csv);
    //Find Average Attack Strength
    float sum = 0;
    for(int j = 0; j < 649; j++)
    {
        sum += pokemons[j].Attack;
    }
    printf("%.6f", sum / 649);
    return 0;
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