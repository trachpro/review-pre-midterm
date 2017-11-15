#include <stdio.h>
#include <stdlib.h>
#include "main.h"

int main()
{
    Graph g = createGraph();

    addEdge(g, 0, 1);
    addEdge(g, 1, 2);
    addEdge(g, 1, 3);
    addEdge(g, 2, 3);
    addEdge(g, 1, 4);
    addEdge(g, 4, 5);
    addEdge(g, 1, 6);
    addEdge(g, 3, 6);
    addEdge(g, 1, 5);
    addEdge(g, 2, 6);

    bfs(g, 0, -1, print);

    printf("\n");

    dfs(g, 0, -1, print);
    printf("\n");

    // free(g.matrix);
    dropGraph(g);

    return 0;
}