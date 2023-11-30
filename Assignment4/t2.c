#include "t2.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

char convert_to_char(int a)
{
    return (char)(a + 'A');
}
Graph* create_graph(int nodes)
{
    Graph* g = (Graph*)malloc(sizeof(Graph) * nodes);
    //Set the value of nodes
    g->nodes = nodes;
    //Set all values in the matrix to ZERO
    for (int i = 0; i < nodes; i++)
    {
        for (int j = 0; j < nodes; j++)
        {
            g->matrix[i][j] = 0;
        }
    }
    return g;
} // creates a graph with nodes nodes, assuming nodes are stored in alphabetical order (A, B, C..)
void add_edge(Graph *g, int from, int to, int weight) // adds an undirected weighted edge between from and to
{
    g->matrix[from][to] = g->matrix[to][from] = weight;
    return;
}

void dijkstra(Graph *g, int origin) {
    int distance[g->nodes];
    int visited[g->nodes];

    // Initialize distances and visited matrixay
    for (int i = 0; i < g->nodes; i++) {
        distance[i] = INT_MAX;
        visited[i] = 0;
    }

    // Distance to the origin is always 0
    distance[origin] = 0;

    // Main loop
    for (int count = 0; count < g->nodes; count++) {
        // Find the minimum distance vertex that is not yet processed
        int minDist = INT_MAX, minIndex = -1;

        for (int v = 0; v < g->nodes; v++) {
            if (!visited[v] && distance[v] < minDist) {
                minDist = distance[v];
                minIndex = v;
            }
        }

        // Mark the picked vertex as visited
        visited[minIndex] = 1;

        // Update distance values of the adjacent vertices of the picked vertex
        for (int v = 0; v < g->nodes; v++) {
            if (!visited[v] && g->matrix[minIndex][v] && distance[minIndex] != INT_MAX &&
                distance[minIndex] + g->matrix[minIndex][v] < distance[v]) {
                distance[v] = distance[minIndex] + g->matrix[minIndex][v];
            }
        }

        printf("%c ", convert_to_char(minIndex));
    }

    // Print the results
    printf("\n");
    for (int i = 0; i < g->nodes; i++) {
        printf("The length of the shortest path between %c and %c is %d\n", convert_to_char(origin), convert_to_char(i), distance[i]);
    }
}

void delete_graph(Graph* g)
{
    free(g);
    return;
}