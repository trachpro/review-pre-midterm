#include <stdio.h>
#include <stdlib.h>
#include "../../libs/libfdr/jrb.h"
#include "graph.h"


Graph createGraph() {
    Graph g = make_jrb();
    return g;
}


void addEdgeOneDirection(Graph g, int v1, int v2) {
    Graph node = jrb_find_int(g, v1);
    if (node == NULL) {
        Graph tree = make_jrb();
        jrb_insert_int(g, v1, new_jval_v(tree));
        jrb_insert_int(tree, v2, new_jval_i(1));
    } else {
        Graph tree = jval_v(node->val);
        jrb_insert_int(tree, v2, new_jval_i(1));
    }
}
void addEdge(Graph g, int v1, int v2) {
    addEdgeOneDirection(g, v1, v2);
    addEdgeOneDirection(g, v2, v1);
}

int isAdjacent(Graph g, int v1, int v2) {
	Graph result;
	Graph node = jrb_find_int(g, v1);
    if (node != NULL) {
        Graph tree = jval_v(node->val);
        result = jrb_find_int(tree, v2);
        if (result == NULL) {
        	return 0;
        } else {
        	return 1;
        }
    }
    return 0;
}

int getAdjacentVertices(Graph g, int v, int * output) {
    int total = 0;
    Graph node = jrb_find_int(g, v);
    if (node != NULL) {
        Graph tree = jval_v(node->val);
        jrb_traverse(node, tree) {
            output[total] = jval_i(node->key);
            total++;
        }
    }
    return total;
}

void printGraph(Graph g) {
    Graph node;
    jrb_traverse(node, g) {
        printf("%d: ", jval_i(node->key));
        Graph tree = jval_v(node->val);
        Graph temp;
        jrb_traverse(temp, tree) {
            printf("%d ", jval_i(temp->key));
        }
        printf("\n");
    }
}

void dropGraph(Graph g) {
    Graph node;
    jrb_traverse(node, g) {
        jrb_free_tree(jval_v(node->val));
    }
}