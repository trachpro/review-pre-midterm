#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../lib/libfdr/jrb.h"
#include "../lib/libfdr/dllist.h"

#define INFINITY_VALUE 99999999

typedef struct {
    JRB edges;
    JRB vertices;
} Graph;

typedef struct {
    int key;
    int val;
} OutType;

typedef struct {
    int id;
    int sum;
} Weight;

Graph make_graph();
void addVertex(Graph graph, char *name, int id);
JRB getJRBTree(JRB tree);
void addVertex(Graph graph, char *name, int id);
void addEdgeOneDirection(Graph graph, int id1, int id2, int weight);
void addEdge(Graph graph, int id1, int id2, int weight);
int getWeight(Graph graph, int id1, int id2);
void addMoreWeight(Graph graph, int id1, int id2);
char * getVertexName(Graph graph, int id);
int initArray(int * arr, int n);
void sortOut(OutType *arr, int n);
void copyArr(OutType *outArr, int * intArr, int n);
int getAdjList(Graph graph, int id, int *output);
Weight * make_weight(int id, int sum);
void Dijkstra(Graph graph, int start, JRB ow, JRB op);
int getIdOutput(JRB output, int start, int end, int arr[]);
void printOut(Graph graph, int arr[], int n);
void dropJRB(JRB g);
void printReverse(Graph graph, int id);
void convert(Graph graph,int start,int end);

// deproduct
void readProduct(Graph graph);
void readOrderHistory(Graph graph);

//de tepdulieu
void readTepDuLieu(Graph graph);
int tongNut(Graph graph);
int tongCung(Graph graph);
void congVietNgayTruoc(Graph graph, int id);
void tatCaCacViecTruoc(Graph, int id);
void convert2(Graph graph);
int  DFS(Graph graph, int start, int end); 
int  BFS(Graph graph, int start, int end);
int topologicalSort(Graph graph, int *output);
int DAG(Graph graph);

int readMeCung(Graph graph);
void listBB(Graph graph);