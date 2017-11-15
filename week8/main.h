#include<stdio.h>
#include<stdlib.h>
#include "../lib/libfdr/jrb.h"
#include "../lib/libfdr/jval.h"
// #include "../lib/libfdr/dllist.h"

typedef JRB Graph;

Graph createGraph();
void addEdge(Graph g, int v1, int v2);
int adjacent(Graph g, int v1, int v2);
int getAdjacentVertices(Graph g, int vertice, int *output);
void dropGraph(Graph graph);