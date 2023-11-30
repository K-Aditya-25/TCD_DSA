#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "t1.h"

//--------------------------Queue Functions------------------------------------------------
Queue *front = NULL, *end = NULL;

//Adds an item to the queue
void enqueue(int data)
{
    Queue *temp = malloc(sizeof(Queue));
    temp->data = data;
    temp->next = NULL;
    if (isEmpty())
    {
        front = temp;
        end = temp;
    }
    else
    {
        end->next = temp;
        end = temp;
    }
}

//Removes an item from the queue
void dequeue()
{
    if (isEmpty())
    {
        return;
    }
    Queue *temp = front;
    front = front->next;
    free(temp);
}

//Checks if the queue is empty
int isEmpty()
{
    if (front == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//Retrieves data at front of queue
int frontData()
{
    if (front == NULL)
    {
        return -1;
    }
    return front->data;
}

// -------------------------List of Functions with functionality---------------------------
char convert_to_char(int num); //Convert an int to a char
AJList *addNewNode(int dest); //Add a node at destination
void dfs_visited(Graph *g, int v, int visited[]); //Utility Function for DFS to search recursively
void delete(AJList *ptr); //Recursively deletes a node and all the other nodes attached to it
Graph *create_graph(int num_nodes); // creates a graph with num_nodes nodes, assuming nodes are stored in alphabetical order (A, B, C..)
void add_edge(Graph *g, int from, int to); // adds a directed edge
void bfs(Graph *g, int origin); //implements BFS and prints the results
void dfs(Graph *g, int origin); //implements DFS using the dfs_visited function and prints the results
void delete_graph(Graph *g); // Deletes the entire graph and frees memory without leaks

// -------------------------------- Custom Functions --------------------------------------

char convert_to_char(int num)
{
    num = num + 'A';
    return (char)num;
}


AJList *addNewNode(int dest)
{
    AJList *newNode = malloc(sizeof(AJList));
    newNode->destination = dest;
    newNode->next = NULL;
    return newNode;
}

void dfs_visited(Graph *g, int v, int visited[])
{
    visited[v] = 1;
    printf(" %c ", convert_to_char(v));

    AJList *check_adj;
    for (check_adj = g->array[v].head; check_adj; check_adj = check_adj->next)
    {
        if (!visited[check_adj->destination])
        {
            dfs_visited(g, check_adj->destination, visited);
        }
    }
}

void delete(AJList *ptr)
{
    if (ptr == NULL)
    {
        return;
    }
    delete(ptr->next);
    free(ptr);
}

// -------------------------------- Program Functions -------------------------------------

Graph *create_graph(int num_nodes)
{
    Graph *graph = malloc(sizeof(Graph));
    graph->N = num_nodes;

    graph->array = (AJListHead *)malloc(num_nodes * sizeof(AJListHead));
    for (int i = 0; i < num_nodes; i++)
    {
        graph->array[i].head = NULL;
    }
    return graph;
}

void add_edge(Graph *g, int from, int to)
{
    struct AJList *newNode = addNewNode(to);
    newNode->next = g->array[from].head;
    g->array[from].head = newNode;
}

void bfs(Graph *g, int origin)
{
    AJList *check_adj;
    int *visited = (int *)malloc(sizeof(int) * g->N);
    printf("BFS ");

    for (int i = 0; i < g->N; i++)
    {
        visited[i] = 0;
    }
    visited[origin] = 1;
    enqueue(origin);
    while (!isEmpty())
    {
        origin = frontData();

        printf(" %c ", convert_to_char(origin));
        dequeue();
        for (check_adj = g->array[origin].head; check_adj; check_adj = check_adj->next)
        {
            if (!visited[check_adj->destination])
            {
                visited[check_adj->destination] = 1;
                enqueue(check_adj->destination);
            }
        }
    }
    free(visited);
    printf("\n");
}

void dfs(Graph *g, int origin)
{
    int *visited = (int *)malloc(sizeof(int) * g->N);
    printf("DFS:");
    for (int i = 0; i < g->N; i++)
    {
        visited[i] = 0;
    }
    dfs_visited(g, origin, visited);
    free(visited);
    printf("\n");
}

void delete_graph(Graph *g)
{
    for (int i = 0; i < g->N; i++)
    {
        if (g->array[i].head != NULL)
        {
            delete(g->array[i].head->next);
        }
    }
    for (int i = 0; i < g->N; i++)
    {
        free(g->array[i].head);
    }
    free(g->array);
    free(g);
}