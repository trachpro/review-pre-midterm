#include<stdio.h>
#include<stdlib.h>
#include "../lib/libfdr/jrb.h"
#include "../lib/libfdr/dllist.h"
#include "main.h"

int main() {

    Graph graph = make_graph();

    addVertex(graph, 1,"mot");
    addVertex(graph, 2,"hai");
    addVertex(graph, 3,"ba");
    addVertex(graph, 4,"bon");
    addVertex(graph, 5,"nam");

    addEgde(graph, 1, 2, 4);
    addEgde(graph, 2, 4, 6);
    addEgde(graph, 2, 5, 6);
    addEgde(graph, 3, 4, 2);
    addEgde(graph, 3, 5, 6);
    addEgde(graph, 4, 5, 6);
    addEgde(graph, 1, 3, 3);

    JRB node;
    JRB output = make_jrb();
    // return 0;
    findWay(graph, "nam", "bon");

    
    // jrb_traverse(node, output) {

    //     Weight* x = jval_v(node->val);

    //     printf("%d-%d-%d\n",jval_i(node->key),x->id, x->sum);
    // }

    dropJRB(graph.vertices);
    dropJRB(graph.edges);

    return 0;
}