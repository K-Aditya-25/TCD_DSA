#include "t3.h"

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#define MAX_SIZE 50

Graph* g;
Vertex* bus_stops[MAX_VERTICES];
void initialise_graph()
{
    g = (Graph*)malloc(sizeof(Graph));
    for (int i = 0; i < MAX_VERTICES; i++)
    {
        for (int j = 0; j < MAX_VERTICES; j++)
        {
            g->matrix[i][j] = 0;
        }
    }
}
// The CSV parser
int next_field(FILE *f, char *buf, int max)
{
    int i = 0, end = 0, quoted = 0;

    for (;;)
    {
        // fetch the next character from file
        buf[i] = fgetc(f);
        // if we encounter quotes then flip our state and immediately fetch next char
        if (buf[i] == '"')
        {
            quoted = !quoted;
            buf[i] = fgetc(f);
        }
        // end of field on comma if we're not inside quotes
        if (buf[i] == ',' && !quoted)
        {
            break;
        }
        // end record on newline or end of file
        if (feof(f) || buf[i] == '\n')
        {
            end = 1;
            break;
        }
        // truncate fields that would overflow the buffer
        if (i < max - 1)
        {
            ++i;
        }
    }

    buf[i] = 0; // null terminate the string
    return end; // flag stating whether or not this is end of the line
}
Vertex* get_vertex(FILE* csv)
{
    char buffer[MAX_SIZE];
    Vertex* v = (Vertex*)malloc(sizeof(Vertex));

    next_field(csv, buffer, MAX_SIZE);
    v->id = atoi(buffer);
    next_field(csv, v->name, MAX_SIZE);
    next_field(csv, buffer, MAX_SIZE);
    v->latitude = atof(buffer);
    next_field(csv, buffer, MAX_SIZE);
    v->longitude = atof(buffer);

    return v;
}

edge* get_edge(FILE* csv)
{
    edge* e = (edge*)malloc(sizeof(edge));
    char buffer[MAX_SIZE];

    next_field(csv, buffer, MAX_SIZE);
    e->from = atoi(buffer);
    next_field(csv, buffer, MAX_SIZE);
    e->to = atoi(buffer);
    next_field(csv, buffer, MAX_SIZE);
    e->weight = atoi(buffer);

    return e;
}

void add_edge(Graph *g, int from, int to, int weight) // adds an undirected weighted edge between from and to
{
    g->matrix[from][to] = g->matrix[to][from] = weight;
    return;
}

int load_edges ( char *fname ) //loads the edges from the CSV file of name fname
{
    FILE* f = fopen(fname, "r"); //open file
    //failsafe code
    if (!f)
    {
        printf("Can't open file\n");
        return -1;
    }
    //initialise from, to and weight variables
    int from, to, weight = 0;
    initialise_graph(); //initialise graph
    int num_edges = 0; //set number of edges
    
    get_edge(f);
    edge* temp = (edge*)malloc(sizeof(edge));
    while(!feof(f))
    {
        temp = get_edge(f);
        from = temp->from;
        to = temp->to;
        weight = temp->weight;
        add_edge(g, from, to, weight);
        num_edges++;
    }
    temp = NULL;
    free(temp);
    fclose(f);
    printf("Loaded %i edges\n", num_edges);
    return 1;
}
int load_vertices ( char *fname )  //loads the vertices from the CSV file of name fname
{
    FILE* f = fopen(fname, "r");
    if(!f)
    {
        printf("Can't open file\n");
        return -1;
    }
    Vertex* temp = (Vertex*)malloc(sizeof(Vertex));
    int num_vertices = 0;
    get_vertex(f);
    while (!feof(f))
    {
        temp = get_vertex(f);
        bus_stops[temp->id] = temp;
        num_vertices++;
    }
    temp = NULL;
    free(temp);
    fclose(f);
    printf("Loaded %i vertices\n", num_vertices);
    return 1;
}

int min_index(Graph *g, int dist[MAX_VERTICES], int bools[MAX_VERTICES])
{
    int min = INT_MAX;
    int min_index;
    for (int v = 0; v < MAX_VERTICES; v++)
    {
        if (bools[v] == 0 && dist[v] < min)
        {
            min = dist[v], min_index = v;
        }
    }
    return min_index;
}

void dijkstra(Graph *g, int from, int to) {
    int distance[MAX_VERTICES], shortestPath[MAX_VERTICES], prev[MAX_VERTICES];

    for (int i = 0; i < MAX_VERTICES; i++) {
        distance[i] = INT_MAX; // Set distance to infinity
        shortestPath[i] = 0;   // Set shortestPath to false
        prev[i] = 0;
    }

    distance[from] = 0; // Distance from 'from' to itself is 0;

    for (int eachNode = 0; eachNode < MAX_VERTICES; eachNode++) {
        int minIndex = min_index(g, distance, shortestPath);

        shortestPath[minIndex] = 1; // Set current index to true

        for (int Vertex = 0; Vertex < MAX_VERTICES; Vertex++) {
            if (!shortestPath[Vertex] && g->matrix[minIndex][Vertex] && distance[minIndex] != INT_MAX && distance[minIndex] + g->matrix[minIndex][Vertex] < distance[Vertex])
            {
                prev[Vertex] = minIndex;
                distance[Vertex] = distance[minIndex] + g->matrix[minIndex][Vertex];
            }
        }
    }

    // Print the shortest path from 'from' to 'to'
    while (prev[to] != from) {
        printf("%d %s\n", bus_stops[prev[to]]->id, bus_stops[prev[to]]->name);
        to = prev[to];
    }
}
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// prints the shortest path between startNode and endNode, if there is any
void shortest_path(int startNode, int endNode)
{
    swap(&startNode, &endNode);
    printf("%d %s\n", bus_stops[endNode]->id, bus_stops[endNode]->name);
    dijkstra(g, startNode, endNode);
    printf("%d %s\n", bus_stops[startNode]->id, bus_stops[startNode]->name);
}
void free_memory ( void ) // frees any memory that was used
{
    free(g);
    return;
}
