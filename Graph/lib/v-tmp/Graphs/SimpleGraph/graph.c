#include <stdio.h>
#include <stdlib.h>
#include "graph.h"


Graph createGraph(int sizemax) {
	int i,j;
	Graph g;

	g.matrix = (int*)malloc(sizemax * sizemax * sizeof(int));
	if (g.matrix == NULL) {
		printf("Cannot allocate memory\n");
		exit(1);
	}

	for (i = 0; i < sizemax; i++) {
		for (j = 0; j < sizemax; j++) {
			g.matrix[i*sizemax + j] = 0;
		}
	}

	g.sizemax = sizemax;

	return g;
}

void addEdge(Graph g, int v1, int v2) {
	g.matrix[v1 * g.sizemax + v2] = 1;
	g.matrix[v2 * g.sizemax + v1] = 1;
}

int isAjacent(Graph g, int v1, int v2) {
	return g.matrix[v1 * g.sizemax + v2];
}

// return the number of ajacent verticles
int getAjacentVertices(Graph g, int vertex, int * output) {
	int numOfAjacent = 0;
	int i;

	for (i = 0; i < g.sizemax; ++i) {
		if (isAjacent(g, vertex, i)) {
			output[numOfAjacent] = i;
			numOfAjacent++;
		}
	}

	return numOfAjacent;
}

void dropGraph(Graph g) {
	free(g.matrix);
	g.sizemax = 0;
}