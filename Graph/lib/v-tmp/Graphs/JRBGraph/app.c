#include <stdio.h>
#include <stdlib.h>
#include "../../libs/libfdr/jrb.h"
#include "graph.h"



int main(int argc, char const *argv[])
{

	int i, n, output[100];
    Graph g = createGraph(10);
    addEdge(g, 0, 1);
    addEdge(g, 0, 2);
    addEdge(g, 1, 2);
    n = getAdjacentVertices(g, 1, output);
    if (n==0) printf("No adjacent vertices of node 1\n");
    else {   
       printf("Adjacent vertices of node 1:");
       for (i=0; i<n; i++) printf("%5d", output[i]);
    }

printf("\n");

	return 0;
}