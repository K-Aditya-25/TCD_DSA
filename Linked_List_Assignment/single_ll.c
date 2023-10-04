#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    char c;
    struct node* next;
} Node;

void add_node(Node** list, char data)
{
    Node* new = (Node*)malloc(sizeof(Node));
    if(new == NULL)
    {
        printf("Couldn't create Node\n");
    }
    new->next = (*list);
    new->c = data;
    *list = new;
}

void print_list(Node* list)
{
    Node* temp = list;
    while(temp != NULL)
    {
        if (temp->next == NULL)
        {
            printf("%c->NULL", temp->c);
            break;
        }
        printf("%c->", temp->c);
        temp = temp->next;
    }
    printf("\n");
}

void remove_node(Node** list, char data)
{
    //iterative
    Node* prev = *list;
    Node* temp = prev->next;
    while(temp != NULL)
    {
        if (prev->c == data)
        {
            free(prev);
            *list = temp;
            break;
        }
        if (temp->c == data)
        {
            prev->next = temp->next;
            free(temp);
            break;
        }
        prev = temp;
        temp = temp->next;
    }
    //recursive: to do
}
int main(void)
{
    Node* head = NULL;
    add_node(&head, 'A');
    add_node(&head, 'Y');
    add_node(&head, 'T');
    add_node(&head, 'I');
    add_node(&head, 'D');
    add_node(&head, 'A');
    print_list(head);
    remove_node(&head, 'I');
    print_list(head);
    remove_node(&head, 'A');
    print_list(head);
    remove_node(&head, 'A');
    print_list(head);
}