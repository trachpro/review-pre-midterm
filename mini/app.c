#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../lib/libfdr/jrb.h"
#include "main.h"

int main() {

    Graph graph = create_graph();
    JRB node, subNode, subTree;

    readFile(graph);
    addValue(graph);

    jrb_traverse(node, graph.edges) {
        
        subTree = getTree(node);
        // if(subTree == NULL) continue;
        jrb_traverse(subNode, subTree) {

            Weight *x = jval_v(subNode->val);
            printf("%-10d-%-10d-%d\n",jval_i(node->key),x->id, x->length);
        }
    }
    
    findPath(graph, "441-Nguyen-Tam-Trinh","SVD-Quoc-Gia");

    dropGraph(graph);
    return 0;
}