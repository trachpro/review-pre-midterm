#include "main.h"

Graph createGraph() {

    return make_jrb();
}

void addEdgeOneDirection(Graph g, int v1, int v2) {

    JRB node = jrb_find_int(g,v1);

    if(node) {

        jrb_insert_int((JRB)jval_v(node->val), v2, new_jval_i(1));
    } else {

        node = make_jrb();

        jrb_insert_int(g, v1, new_jval_v(node));
        jrb_insert_int(node, v2, new_jval_i(1));

        printf("ad %d\n", v1);
    }
}

void addEdge(Graph g, int v1, int v2) {

    addEdgeOneDirection(g, v1, v2);
    addEdgeOneDirection(g, v2, v1);
}

int getAdjacentVertices(Graph g, int vertice, int *output) {

    JRB node = jrb_find_int(g, vertice);

    if(node) {

        int count = 0;

        JRB tree = (JRB)jval_v(node->val);

        jrb_traverse(node, tree) {

            output[count++] = jval_i(node->key);
        }

        return count;
    }

    return 0;
}

void print(int n) {

    printf("\n%5d",n);
}

void initArr(int *n,int size) {

    for(int i = 0; i < size; i++) n[i] = 0;
}

void bfs(Graph g, int start, int end, void (*report)(int)) {

    int visited[1000] = {}, output[100];
    Dllist queue = new_dllist();
    

    initArr(visited,1000);
    
    dll_append(queue, new_jval_i(start));

    while(!dll_empty(queue)) {

        Dllist node = dll_first(queue);
        int u = jval_i(node->val);
        dll_delete_node(node);

        visited[u] = 1;
        report(u);

        if(u == end) return;

        int n = getAdjacentVertices(g, u, output);

        for(int i = 0; i < n; i++) {

            if(visited[output[i]] != 1) {

                dll_append(queue, new_jval_i(output[i]));
            }
        }
    }
}

void dfs(Graph g, int start, int end, void (*report)(int)) {

    int visited[1000] = {}, output[100];

    Dllist stack = new_dllist();
    
    initArr(visited,1000);

    dll_append(stack, new_jval_i(start));

    while(!dll_empty(stack)) {

        Dllist node = dll_last(stack);
        int u = jval_i(node->val);
        dll_delete_node(node);

        if(u == end) return;

        visited[u] = 1;
        report(u);

        

        int n = getAdjacentVertices(g, u, output);
        printf("--\n");
        for(int i = 0; i < n; i++) {
            printf("%-3d",output[i]);

            if(visited[output[i]] != 1) {

                dll_append(stack, new_jval_i(output[i]));
            }
        }
    }
}


void dropGraph(Graph graph) {
  JRB node;
  jrb_traverse(node, graph) {
    jrb_free_tree((JRB)jval_v(node->val));
  }
}