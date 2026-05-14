#ifndef T3_H_
#define T3_H_
#define MAX_VERTICES 8000

typedef struct Graph Graph;
struct Graph
{
    int matrix[MAX_VERTICES][MAX_VERTICES];
};

typedef struct Vertex Vertex;
struct Vertex
{
    int id;
    char name[50];
    double latitude;
    double longitude;
};

typedef struct edge edge;
struct edge
{
    int from;
    int to;
    int weight;
};

int load_edges(char *fname);                    //loads the edges from the CSV file of name fname
int load_vertices(char *fname);                 //loads the vertices from the CSV file of name fname
void shortest_path(int startNode, int endNode); // prints the shortest path between startNode and endNode, if there is any
void free_memory(void);                         // frees any memory that was used

#endif
