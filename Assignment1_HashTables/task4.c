#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_ARRAY_SIZE 59
#define MAX_STRING_SIZE 20

int collisions = 0;

typedef struct Element{
    int p_id;
    char* d_id;
    char* surname;
    char* forename;
    int age;
    char* p_type;
    char* gender;
    char* nationality;
    char* religion;
    char* occupation;
    struct Element* next;
}Element;

Element* table[MAX_ARRAY_SIZE] = {NULL};



//functions used
int hash1(char* s);
Element* create(int p_id,char* d_id,char* surname,char* forename,int age,char* p_type,char* gender,char* nationality,char* religion,char* occupation);
Element* search(char* name);
void insert_or_update(char* name, Element* new);
float count_terms();
void next_field(FILE *csv, char *buffer, int max_len);
void add_node(Element** list, Element* new);

int main(int argc, char* argv[])
{
    //create buffer array and open file
    char* buffer = (char*)(malloc(sizeof(char) * MAX_STRING_SIZE));
    if(buffer == NULL){
        return -1;
    }
    FILE* f = fopen(argv[1], "r");
    if(f == NULL){
        printf("Can't open file\n");
        return -1;
    }
    //creating variables to store attributes
    int p_id = 0;
    char* d_id = (char*)(malloc(sizeof(char)*MAX_STRING_SIZE));
    if(d_id == NULL){return -1;}
    char* surname = (char*)(malloc(MAX_STRING_SIZE*sizeof(char)));
    if(surname == NULL){return -1;}
    char* forename = (char*)(malloc(MAX_STRING_SIZE*sizeof(char)));
    if(forename == NULL){return -1;}
    int age = 0;
    char* p_type = (char*)(malloc(MAX_STRING_SIZE*sizeof(char)));
    if(p_type == NULL){return -1;}
    char* gender = (char*)(malloc(MAX_STRING_SIZE*sizeof(char)));
    if(gender == NULL){return -1;}
    char* nationality = (char*)(malloc(MAX_STRING_SIZE*sizeof(char)));
    if(nationality == NULL){return -1;}
    char* religion = (char*)(malloc(MAX_STRING_SIZE*sizeof(char)));
    if(religion == NULL){return -1;}
    char* occupation = (char*)(malloc(MAX_STRING_SIZE*sizeof(char)));
    if(occupation == NULL){return -1;}
    
    //parse each row and copy values into the above created variables
    while (!feof(f)){
        next_field(f, buffer, MAX_STRING_SIZE);
        p_id = atoi(buffer);
        next_field(f,buffer,MAX_STRING_SIZE);
        strcpy(d_id, buffer);
        next_field(f,buffer,MAX_STRING_SIZE);
        strcpy(surname, buffer);
        next_field(f,buffer,MAX_STRING_SIZE);
        strcpy(forename, buffer);
        next_field(f,buffer,MAX_STRING_SIZE);
        age = atoi(buffer);
        next_field(f,buffer,MAX_STRING_SIZE);
        strcpy(p_type, buffer);
        next_field(f,buffer,MAX_STRING_SIZE);
        strcpy(gender, buffer);
        next_field(f,buffer,MAX_STRING_SIZE);
        strcpy(nationality, buffer);
        next_field(f,buffer,MAX_STRING_SIZE);
        strcpy(religion, buffer);
        next_field(f,buffer,MAX_STRING_SIZE);
        strcpy(occupation, buffer);
        Element* new = create(p_id, d_id, surname, forename, age, p_type, gender, nationality, religion, occupation);
        insert_or_update(surname, new);
        // *d_id = "\0";
        // *surname = "\0";
        // *forename = "\0";
        // *p_type = "\0";
        // *gender = "\0";
        // *nationality = "\0";
        // *religion = "\0";
        // *occupation = "\0";
    }   
    float terms = count_terms();
    printf("File %s loaded\n",argv[1]);
	printf(" Capacity: %i\n",MAX_ARRAY_SIZE);
    printf(" Num Terms: %0.0f\n",terms);
	printf(" Collisions: %d\n",collisions);
	float loadFactor=terms/MAX_ARRAY_SIZE;
	printf(" Load: %f\n",loadFactor);
    // char *userInput=(char*)(malloc(MAX_STRING_SIZE*sizeof(char)));
	// printf("Enter term to get frequency or type \"%s\" to escape\n","quit");
	// while(1){
	// 	printf(">>> ");
	// 	gets(userInput);
	// 	if(strcmp(userInput,"quit")==0){
	// 		break;
	// 	}
	// 	Element* curr=search(userInput);
	// 	if(curr!=NULL){
	// 		printf("%s - %d \n",userInput,curr->frequency);
	// 	} else{
	// 		printf("%s - 0 \n",userInput);
	// 	}
	// }
    free(buffer);
    free(d_id);
    free(surname);
    free(forename);
    free(p_type);
    free(gender);
    free(nationality);
    free(religion);
    free(occupation);
    fclose(f);
}

Element* create(int p_id,char* d_id,char* surname,char* forename,int age,char* p_type,char* gender,char* nationality,char* religion,char* occupation){
    Element* curr = (Element*)(malloc(sizeof(Element)));
    curr->d_id = (char*)(malloc(sizeof((strlen(d_id)+1)*sizeof(char))));
    if(curr->d_id == NULL){return NULL;}
    curr->surname = (char*)(malloc(sizeof((strlen(surname)+1)*sizeof(char))));
    if(curr->surname == NULL){return NULL;}
    curr->forename = (char*)(malloc(sizeof((strlen(forename)+1)*sizeof(char))));
    if(curr->forename == NULL){return NULL;}
    curr->p_type = (char*)(malloc(sizeof((strlen(p_type)+1)*sizeof(char))));
    if(curr->p_type == NULL){return NULL;}
    curr->gender = (char*)(malloc(sizeof((strlen(gender)+1)*sizeof(char))));
    if(curr->gender == NULL){return NULL;}
    curr->nationality = (char*)(malloc(sizeof((strlen(nationality)+1)*sizeof(char))));
    if(curr->nationality == NULL){return NULL;}
    curr->religion = (char*)(malloc(sizeof((strlen(religion)+1)*sizeof(char))));
    if(curr->religion == NULL){return NULL;}
    curr->occupation = (char*)(malloc(sizeof((strlen(occupation)+1)*sizeof(char))));
    if(curr->occupation == NULL){return NULL;}
    curr->p_id = p_id;
    strcpy(curr->d_id, d_id);
    strcpy(curr->surname, surname);
    strcpy(curr->forename, forename);
    strcpy(curr->p_type, p_type);
    strcpy(curr->gender, gender);
    strcpy(curr->nationality, nationality);
    strcpy(curr->religion, religion);
    strcpy(curr->occupation, occupation);
    curr->age = age;
    curr->next = NULL;
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
int hash3(char* s){
    int hash = 0;
    while(*s){
        hash = 1+ (hash + *s - 'A') % (MAX_ARRAY_SIZE-1);
        s++;
    }
    return hash;
}

Element* search(char* surname){
    Element* curr = NULL;
    int j = 0;
    int index = hash1(surname) + (j * hash3(surname));
    while (table[index] != NULL){
        if (!strcmp(table[index]->surname, surname)){
            curr = table[index];
            return curr;
        }
        j++;
        index = (hash1(surname) + (j * hash3(surname))) % MAX_ARRAY_SIZE;
    }
    return NULL;
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

void next_field ( FILE *f, char* buf, int string_max) {
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

void add_node(Element** list, Element* new){
    new->next = (*list);
    (*list) = new;
}

void insert_or_update(char* surname, Element* new){
    int j = 0;
    int index = hash1(surname) + (j * hash3(surname));
    Element* curr = search(surname);
    if (curr != NULL){
        add_node(&(table[index]),curr);
        return;
    }
    curr = new;
    while (table[index] != NULL){
        j++;
        index = (hash1(surname) + (j * hash3(surname))) % MAX_ARRAY_SIZE;
        collisions++;
    }
    table[index] = curr;
}