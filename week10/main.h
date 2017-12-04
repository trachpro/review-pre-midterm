#include<stdio.h>
#include<stdlib.h>
#include "../lib/libfdr/jrb.h"
#include "../lib/libfdr/dllist.h"
#include "string.h"

typedef struct {
    JRB edges;
    JRB vertices;
} Graph;

typedef struct {
    int id;
    int sum;
} Weight;

Graph make_graph();
void addVertex(Graph graph, int id, char *name);
char *getVertex(Graph graph, int id);
void addEgde(Graph graph, int v1, int v2, int w);
int hasEdge(Graph graph, int v1, int v2);
int indegree(Graph graph, int v, int *output);
int outdegree(Graph graph, int v, int *output);
int DAG(Graph graph);
void dropGraph(Graph graph);
void DJT(Graph graph, int start, JRB output);
void addEdge(Graph graph, char *name1, char *name2, int w);
void findWay(Graph graph, char *start, char * end);
void printOut(Graph graph, int arr[], int n);
int getIdOutput(JRB output, int start, int end, int arr[]);
void dropJRB(JRB g);