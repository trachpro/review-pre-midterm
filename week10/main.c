#include "main.h"

JRB getJRB(JRB a) {

    return (JRB)jval_v(a->val);
}

Weight * make_weight(int id, int sum) {

    Weight *a = (Weight*)malloc(sizeof(Weight));
    a->id = id;
    a->sum = sum;

    return a;
}

Graph make_graph() {

    Graph x;
    x.edges = make_jrb();
    x.vertices = make_jrb();

    return x;
}

void addVertex(Graph graph, int id, char *name) {
    
    if(!jrb_find_int(graph.vertices, id)) jrb_insert_int(graph.vertices, id, new_jval_s(name));
}

char *getVertex(Graph graph, int id) {

    return jval_s(jrb_find_int(graph.vertices, id)->val);
}

void addEgde(Graph graph, int v1, int v2, int w) {

    JRB tree = jrb_find_int(graph.edges, v1);

    if(tree) {

        tree = getJRB(tree);

        JRB node = jrb_find_int(tree, v2);

        if(!node) {

            jrb_insert_int(tree, v2, new_jval_i(w));
        }
    } else {

        tree = make_jrb();

        jrb_insert_int(tree, v2, new_jval_i(w));
        jrb_insert_int(graph.edges, v1, new_jval_v(tree));
    }
}

void addEdge(Graph graph, char *name1, char *name2, int w) {

    JRB node, node1, node2;

    jrb_traverse(node, graph.vertices) {

        if(strcmp(name1, jval_s(node->val)) == 0) {

            node1 = node;
        }

        if(strcmp(name2, jval_s(node->val)) == 0) {

            node2 = node;
        }
    }

    if(!node1 || !node2) {

        printf("add faild! can not found the vertex!\n");
        return;
    }

    addEgde(graph,jval_i(node1->key),jval_i(node2->key),w);
}

int hasEdge(Graph graph, int v1, int v2) {

    JRB tree = (JRB)jval_v(jrb_find_int(graph.edges, v1)->val);

    return jrb_find_int(tree, v2)? 1: 0; 
}

int indegree(Graph graph, int v, int *output) {

    JRB node;
    int n = 0;

    jrb_traverse(node, graph.edges) {

        JRB tree = getJRB(node);

        JRB tr = jrb_find_int(tree, v);

        if(tr) {

            output[n++] = jval_i(tr->val);
        }
    }

    return n;
}

int outdegree(Graph graph, int v, int *output) {

    JRB tree = getJRB(jrb_find_int(graph.edges, v));
    JRB node;

    int n = 0;

    jrb_traverse(node, tree) {

        output[n++] = jval_i(node->val);
    }

    return n;
}

int getWeight(JRB g, int a, int b) {

    JRB tree = getJRB(jrb_find_int(g, a));
    
    return jval_i(jrb_find_int(tree, b)->val);

    // return jval_i(node->val);
}

void DJT(Graph graph, int start, JRB output) {

    JRB tree = jrb_find_int(graph.edges, start);

    if(tree == NULL) return;
    tree = getJRB(tree);

    JRB node;
    JRB current = jrb_find_int(output, start);


    if(current == NULL) {

        jrb_insert_int(output, start, new_jval_v(make_weight(start, 0)));
    }
    current = jrb_find_int(output, start);
    
    jrb_traverse(node, tree) {

        int key = jval_i(node->key);
        //  if(key==5) return;

        Weight * a = jval_v(current->val);
        
        int s = getWeight(graph.edges, start, key) + a->sum;
        // return;
        JRB nn = jrb_find_int(output, key);
        if(nn) {
            
            Weight *b = jval_v(nn->val);
            
            if( s < b->sum) {

                // jrb_insert_int(output, key, new_jval_v(make_weight(start, s)));
                b->id = start;
                b->sum = s;
            } 

        }else {
            
            jrb_insert_int(output, key, new_jval_v(make_weight(start, s)));

            
        }

        printf("keey %d\n",key);
        // if(key==5) return;
        DJT(graph, key, output);
    }
}

void findWay(Graph graph, char *start, char * end) {

    JRB output = make_jrb();

    JRB node, node1, node2;

    jrb_traverse(node, graph.vertices) {

        if(strcmp(start, jval_s(node->val)) == 0) {

            node1 = node;
        }

        if(strcmp(end, jval_s(node->val)) == 0) {

            node2 = node;
        }
    }

    if(!node1 || !node2) {

        printf("add faild! can not found the vertex!\n");
        return;
    }

    int key1 = jval_i(node1->key);
    int key2= jval_i(node2->key);
    if(key1 == key2) {
        printf("%s",start);
        return;
    }
    // printf("key1: %d - key2: %d\n",key1, key2);
    DJT(graph, key1,output);
    
    int arr[100];
    
    int n = getIdOutput(output, key1, key2, arr);
    // return;
    dropJRB(output);
    printOut(graph,arr,n);
}

void printOut(Graph graph, int arr[], int n) {
    // return;
    if(n ==0) {
        printf("there is no path!\n");
        return;
    }
    char a[50];
    JRB x;
    for(int i = n - 1; i > 0; i--) {
        // break;
        x = jrb_find_int(graph.vertices,arr[i]);
        strcpy(a,jval_s(x->val));
        printf(" %s ----->",a); 
    }
    // return;
    x = jrb_find_int(graph.vertices,arr[0]);
    strcpy(a,jval_s(x->val));

    printf(" %s\n\n",a); 
} 

int getIdOutput(JRB output, int start, int end, int arr[]) {
   
    JRB node = jrb_find_int(output, end);
    
    if(!node) {
        // printf("error");
        // arr[0] = end;
        return 0;
    };

    int i = 1;
    arr[0] = end;

    Weight *a = jval_v(node->val);
    // return 0;
    if(a == NULL) return 0;

    while(a->sum) {

        arr[i++] = a->id;
        node = jrb_find_int(output, a->id);
        a = jval_v(node->val);
    }

    // arr[i++] = start;

    return i;
}

void dropJRB(JRB g) {
    JRB node;
    jrb_traverse(node, g) {
        jrb_free_tree(jval_v(node->val));
    }
}