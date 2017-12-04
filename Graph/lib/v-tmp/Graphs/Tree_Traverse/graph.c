#include <stdio.h>
#include <stdlib.h>
#include "../../libs/libfdr/jrb.h"
#include "../../libs/libfdr/dllist.h"
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


void BFS(Graph g, int start, int stop, void (*func)(int)) {
        Graph node, node_v, node_visited;
        Graph tree, tmp;

        int u, v;

        Dllist Q, tmpQ;

        // make visited tree
        Graph visited = make_jrb();

        // Find node "start" on graph
        node = jrb_find_int(g, start);

        // If node "start" is on the graph
        if (node != NULL) {
                tree = jval_v(node->val);
                jrb_traverse (tmp, tree) {
                        u = jval_i(tmp->key);
                        jrb_insert_int(visited, u, new_jval_i(0)); // 1: visited, 0:not visited 
                }

                // create a queue
                Q = new_dllist();

                // Enqueue
                // append new node to queue
                dll_append(Q, new_jval_i(start));

                // while the queue is not empty
                while (!dll_empty(Q)) {

                        // Dequeue
                        tmpQ = dll_first(Q);
                        u = jval_i(tmpQ->val);
                        dll_delete_node(tmpQ);

                        // Find the node "u" on the tree "visited"
                        node = jrb_find_int(visited, u);
                        
                        // if not visited
                        if (jval_i(node->val) == 0) {
                                printf("Visit: %d", u);

                                (*func)(u);

                                // change visited value - > 1
                                jrb_delete_node(node);
                                jrb_insert_int(visited, u, new_jval_i(1));

                                
                                 node_v = jrb_find_int(g, u);
                                 if (node_v != NULL) {
                                         tree = jval_v(node_v->val);
                                         jrb_traverse(node_v, tree) {
                                                 v = jval_i(node->key);

                                                 // Check visited
                                                 node_visited = jrb_find_int(visited, v);
                                                 if (jval_i(node_visited->val) == 0) {
                                                         // Enqueue
                                                         // append new node to queue
                                                         dll_append(Q, new_jval_i(v));
                                                 }
                                                 
                                                 
                                         }
                                 }
        
                                
                        }

                        

                        
                        
                        
                }
                
        }

        
}
