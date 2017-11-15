#include "main.h"

Graph createGraph() {

    return make_jrb();
}

void addEdgeOneDirection(Graph g, int v1, int v2) {

    JRB node = jrb_find_int(g,v1);

    if(node) {

        // JRB child = (JRB) jrb_find_int(node, v2);

        // if(child) return;

        jrb_insert_int((JRB)jval_v(node->val),v2,new_jval_i(1));
    } else {

        node = make_jrb();

        jrb_insert_int(node,v2,new_jval_i(1));

        jrb_insert_int(g, v1, new_jval_v(node));
    }
}

void addEdge(Graph g, int v1, int v2) {

    addEdgeOneDirection(g,v1,v2);
    addEdgeOneDirection(g,v2,v1);
}

int adjacent(Graph g, int v1, int v2) {

    JRB node = jrb_find_int(g,v1);

    if(node) {

        if(jrb_find_int((JRB)jval_v(node->val), v2)) return 1;

        return 0;
    } else {

        return 0;
    }
}

int getAdjacentVertices(Graph g, int vertice, int *output) {

    JRB node = jrb_find_int(g, vertice);

    if(!node) return 0;

    JRB tree = (JRB)jval_v(node->val);
    int count = 0;

    jrb_traverse(node,tree ) {

        output[count++] = jval_i(node->key);
    }

    return count;
}

void dropGraph(Graph graph) {
  JRB node;
  jrb_traverse(node, graph) {
    jrb_free_tree((JRB)jval_v(node->val));
  }
}