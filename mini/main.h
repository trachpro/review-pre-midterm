#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../lib/libfdr/jrb.h"
// #include "../lib/libfdr/dllist.h"

#define MAX 9999999;

typedef struct {
    JRB edges;
    JRB vertices;
} Graph;

typedef struct {
    int id;
    int length;
} Weight;

typedef struct {
    int id;
    int idBus;
    int sum;
} OutType;

Graph create_graph();
OutType *create_outType(int id, int idBus, int sum);
Weight *create_weight(int id, int sum);
JRB getKey(Graph graph, char *name);
void addVertex(Graph graph, char *name);
int getArr(JRB output,int end, OutType arr[]);
void readFile(Graph graph);
void dropGraph(Graph graph);
void addValue(Graph graph);
void findPath(Graph graph, char* name1, char* name2);