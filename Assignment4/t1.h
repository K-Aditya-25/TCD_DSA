#ifndef T1_H_
#define T1_H_

typedef struct queue_node {
    int data;
    struct queue_node* link;
}queue_node;

//definition of a general Linked List Node
typedef struct Node
{
    int value;
    struct Node *next;
}Node;

//definition of Head of each individual list
typedef struct list_head
{
    struct Node* head;
}list_head;

//definition of a general Graph
typedef struct Graph{
    int num_vertices;
    struct list_head* list; //A pointer to an array of pointers to Nodes
} Graph;

Graph* create_graph(int num_nodes); // creates a graph with num_nodes nodes, assuming nodes are stored in alphabetical order (A, B, C..)
void add_edge(Graph *g, int from, int to); // adds a directed edge
void bfs(Graph* g, int origin); //implements breath first search and prints the results
void dfs(Graph* g, int origin); //implements depth first search and prints the results
void delete_graph(Graph* g); // delete the graph and all its data structures
void print(Graph* g, int from); //prints the neighbours of a pointer


void enqueue(int data);
void dequeue();
int isEmpty_queue();
int frontData();
#endif