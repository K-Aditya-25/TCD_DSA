#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_ARRAY_SIZE 59
#define MAX_STRING_SIZE 20

int collisions = 0;

typedef struct Element{
    char* name;
    int frequency;
}Element;

Element* table[MAX_ARRAY_SIZE] = {NULL};

//functions used
int hash1(char* s);
Element* create(char* name);
Element* search(char* name);
void insert_or_update(char* name);
float count_terms();
void next_field(FILE *csv, char *buffer, int max_len);

int main(int argc, char* argv[]){
    char* buffer = (char*)(malloc(sizeof(char) * MAX_STRING_SIZE));
    if(buffer == NULL){
        return -1;
    }
    FILE* f = fopen(argv[1], "r");
    if(f == NULL){
        printf("Can't open file\n");
        return -1;
    }
    while (!feof(f)){
        next_field(f, buffer, MAX_STRING_SIZE);
        insert_or_update(buffer);
    }   
    float terms = count_terms();
    printf("File %s loaded\n",argv[1]);
	printf(" Capacity: %i\n",MAX_ARRAY_SIZE);
    printf(" Num Terms: %0.0f\n",terms);
	printf(" Collisions: %d\n",collisions);
	float loadFactor=terms/MAX_ARRAY_SIZE;
	printf(" Load: %f\n",loadFactor);
    char *userInput=(char*)(malloc(MAX_STRING_SIZE*sizeof(char)));
	printf("Enter term to get frequency or type \"%s\" to escape\n","quit");
	while(1){
		printf(">>> ");
		gets(userInput);
		if(strcmp(userInput,"quit")==0){
			break;
		}
		Element* curr=search(userInput);
		if(curr!=NULL){
			printf("%s - %d \n",userInput,curr->frequency);
		} else{
			printf("%s - 0 \n",userInput);
		}
	}
    free(buffer);
    fclose(f);
}

Element* create(char* name){
    Element* curr = (Element*)(malloc(sizeof(Element)));
    curr->frequency = 1;
    curr->name = (char*)(malloc(sizeof(char) * MAX_STRING_SIZE));
    strcpy(curr->name, name);
    return curr;
}

int hash1(char* s){
    int hash = 0;
    while(*s){
        hash = (hash + *s - 'A') % MAX_ARRAY_SIZE;
        s++;
    }
    return hash;
}

Element* search(char* name){
    Element* curr = NULL;
    int index = hash1(name);
    while (table[index] != NULL){
        if (!strcmp(table[index]->name, name)){
            curr = table[index];
            return curr;
        }
        index = (index + 1) % MAX_ARRAY_SIZE;
    }
    return NULL;
}

void insert_or_update(char* name){
    int index = hash1(name);
    Element* curr = search(name);
    if (curr != NULL){
        curr->frequency++;
        return;
    }
    curr = create(name);
    while (table[index] != NULL){
        index = (index + 1) % MAX_ARRAY_SIZE;
        collisions++;
    }
    table[index] = curr;
}

float count_terms(){
    float terms = 0;
    for (int i = 0; i < MAX_ARRAY_SIZE; i++){
        if (table[i] != NULL){
            terms += 1.0;
        }
    }
    return terms;
}

void next_field ( FILE *f, char* buf, int string_max ) {
	// start by skipping any characters we're not interested in
	buf[0] = fgetc(f);
	while ( !isalnum(buf[0]) && !feof(f) ) { buf[0] = fgetc(f); }
	// read string of alphanumeric characters
	int i=1;
	for (;;) {
		buf[i] = fgetc(f);                // get next character from file
		if( !isalnum(buf[i]) ) { 
            if(buf[i]!=' '){ // we still want to keep spaces
                break; // only load letters and numbers
            }
        } 
		if( feof(f) ) { break; }          // file ended?
		if( i < (string_max-1) ) { ++i; } // truncate strings that are too long
	}
	buf[i] = '\0'; // NULL terminate the string
}