#include "t1.h"
#include <stdio.h>
#include <stdlib.h>


struct queue_node* front = NULL;
struct queue_node* rear = NULL;

void enqueue(int data) {
    struct queue_node* temp = (struct queue_node*)malloc(sizeof(struct queue_node));
    if (temp == NULL) {
        return;
    }
    temp->data = data;
    temp->link = NULL;

    if (isEmpty_queue()) {
        front = rear = temp;
    } else {
        rear->link = temp;
        rear = temp;
    }
}

void dequeue() {
    if (isEmpty_queue()) {
        return;
    }
    struct queue_node* temp = front;
    front = front->link;
    free(temp);
}

int isEmpty_queue() {
    return (front == NULL);
}

int frontData() {
    if (front == NULL) {
        // printf("Queue is empty.\n");
        return -1; // Return a sentinel value
    }
    return front->data;
}




Graph* create_graph(int num_nodes); // creates a graph with num_nodes nodes, assuming nodes are stored in alphabetical order (A, B, C..)
void add_edge(Graph *g, int from, int to); // adds a directed edge
void bfs(Graph* g, int origin); //implements breath first search and prints the results
void dfs(Graph* g, int origin); //implements depth first search and prints the results
void delete_graph(Graph* g); // delete the graph and all its data structures
Node* create_node(int n); //creates a new node
void dfs_recursive(Graph* g, int v, int visited[]); //Recursively performs DFS
int convert_to_char(int a); //Converts alphabet to number. Eg: A -> 0, B -> 1 etc..

//----------------------------------- Custom Function Definitions --------------------------------------------
Node* create_node(int n)
{
    Node* new = (Node*)malloc(sizeof(Node));

    new->value = n;
    new->next = NULL;

    return new;
}

int convert_to_char(int a)
{
    return (char)(a + 'A');
}

void dfs_recursive(Graph* g, int v, int visited[])
{
    visited[v] = 1;
    printf(" %c ", convert_to_char(v));
    Node* temp = g->list[v].head;
    while(temp)
    {
        if (!visited[temp->value])
        {
            dfs_recursive(g, temp->value, visited);
        }
        temp = temp->next;
    }
}

//----------------------------------- Header File Function Definitions ---------------------------------------

Graph* create_graph(int num_nodes)
{
    //allocate memory to graph
    Graph* g = (Graph*)malloc(num_nodes * sizeof(Graph));

    //Initialize values of num_vertices and head of the adjacencyList
    g->num_vertices = num_nodes;
    g->list = (list_head*)malloc(sizeof(list_head) * num_nodes);
    for (int i = 0; i < num_nodes; i++)
    {
        g->list[i].head = NULL;
    }

    //return pointer to created graph
    return g;
}

void add_edge(Graph *g, int from, int to) {
  // Allocate a new node for the neighbor
    Node* new_node = create_node(to);

    new_node->next = g->list[from].head;
    g->list[from].head = new_node;
}

void bfs(Graph* g, int origin) {
    int* visited = (int*)malloc(sizeof(int) * g->num_vertices);
    for (int i = 0; i < g->num_vertices; ++i) {
        visited[i] = 0; // Mark all vertices as not visited
    }

    // Initialize the queue for BFS
    enqueue(origin);
    visited[origin] = 1;
    printf("BFS ");
    while (!isEmpty_queue()) {
        origin = frontData();
        printf(" %c ", convert_to_char(origin));
        dequeue();

        Node* temp = g->list[origin].head;
        while (temp != NULL) {
            if (!visited[temp->value]) {
                enqueue(temp->value);
                visited[temp->value] = 1;
            }
            temp = temp->next;
        }
    }

    printf("\n");

    // Free allocated memory
    free(visited);
}

void dfs(Graph* g, int origin) {
    int* visited = (int*)malloc(sizeof(int) * g->num_vertices);
    for (int i = 0; i < g->num_vertices; i++)
    {
        visited[i] = 0;
    }
    printf("DFS:");
    dfs_recursive(g, origin, visited);
    printf("\n");
    free(visited);
}

// Function to delete the entire graph
void delete_graph(Graph* g) {
    if (g == NULL) {
        return; // Graph is already empty or not initialized
    }

    for (int i = 0; i < g->num_vertices; ++i) {
        struct Node* current = g->list[i].head;
        while (current != NULL) {
            struct Node* temp = current;
            current = current->next;
            free(temp); // Deallocate memory for each node
        }
        g->list[i].head = NULL; // Set the head pointer to NULL
    }

    free(g->list); // Deallocate memory for the array of pointers
    g->list = NULL;
    // g->num_vertices = 0;
    free(g);
    return;
}

void print(Graph* g, int from)
{
    Node* temp = g->list[from].head;
    while (temp)
    {
        printf("%c ", convert_to_char(temp->value));
        printf("\n");
        temp = temp->next;
    }
}