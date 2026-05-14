# Assignment 4: Searching With Graphs

This repository contains the C implementations for CS3D5A Assignment 4 at Trinity College Dublin. The assignment focuses on representing graphs, traversing them, and applying Dijkstra's algorithm to both small examples and Dublin Bus stop data.

## Contents

| File | Purpose |
| --- | --- |
| `t1.h`, `t1.c` | Directed unweighted graph using adjacency lists, with BFS and DFS traversal. |
| `t1_test.c` | Test driver for Task 1. |
| `t2.h`, `t2.c` | Undirected weighted graph using an adjacency matrix, with Dijkstra's shortest path algorithm. |
| `t2_test.c` | Test driver for Task 2. |
| `t3.h`, `t3.c` | Dublin Bus graph loader and shortest-path implementation. |
| `t3_test.c` | Interactive test driver for Task 3. |
| `vertices.csv` | Dublin Bus stop data: stop ID, name, latitude, and longitude. |
| `edges.csv` | Bus stop connections and edge weights in metres. |

## Task Summary

### Task 1: BFS and DFS

Task 1 builds a directed graph with adjacency lists. The implementation provides:

- `create_graph` to allocate and initialize the graph.
- `add_edge` to add directed edges.
- `dfs` to visit vertices recursively.
- `bfs` to visit vertices iteratively using a queue.
- `delete_graph` to release allocated graph memory.

The test graph starts at vertex `A` and prints the traversal order.

### Task 2: Dijkstra

Task 2 builds an undirected weighted graph with an adjacency matrix. The implementation provides:

- `create_graph` to allocate and initialize the graph.
- `add_edge` to add weighted undirected edges.
- `dijkstra` to print the order in which nodes become permanent and the shortest distance from the origin to every vertex.
- `delete_graph` to release the graph.

The provided test starts from vertex `A`.

### Task 3: Dublin Bus Shortest Path

Task 3 loads real Dublin Bus stop data from CSV files and models the transport network as an undirected weighted graph. The implementation provides:

- `load_vertices` to load bus stops from `vertices.csv`.
- `load_edges` to load route connections from `edges.csv`.
- `shortest_path` to print the bus stop sequence between two stop IDs.
- `free_memory` to release graph memory.

The assignment brief's sample route is from stop `300` at Eden Quay to stop `253` at Beaumont Hospital.

## Build and Run

Compile each task with its corresponding test driver:

```sh
gcc -Wall -Wextra -std=c11 t1.c t1_test.c -o t1
./t1
```

```sh
gcc -Wall -Wextra -std=c11 t2.c t2_test.c -o t2
./t2
```

```sh
gcc -Wall -Wextra -std=c11 t3.c t3_test.c -o bus
./bus vertices.csv edges.csv
```

For Task 3, enter the starting and destination bus stop IDs when prompted.

## Notes

- `edges.csv` stores undirected route connections with weights in metres.
- `vertices.csv` stores bus stop metadata used to print route names and coordinates.
- `t3.c` includes `t3.h`, so that header must be present when compiling Task 3.
- The implementations are intended for the assignment test drivers and the constraints described in the assignment brief.
