#include <stdio.h>
#include <stdlib.h>
#include "graph.h"



void printGraph(Graph g){
	int i, j;
	for (i = 0; i < g.sizemax; ++i) {
		for (j = 0; j < g.sizemax; ++j) {
			printf("%d ", g.matrix[i*g.sizemax + j]);
		}
		printf("\n");
	}
}

int main(int argc, char const *argv[])
{

	int i, n, output[100];
    Graph g = createGraph(10);
    addEdge(g, 0, 1);
    printGraph(g);
    addEdge(g, 0, 2);
    printGraph(g);
    addEdge(g, 1, 2);
    printGraph(g);
    addEdge(g, 1, 3);
    printGraph(g);
    n = getAjacentVertices (g, 1, output);
    if (n==0) printf("No adjacent vertices of node 1\n");
    else {   
       printf("Adjacent vertices of node 1:");
       for (i=0; i<n; i++) printf("%5d", output[i]);
    }

	return 0;
}