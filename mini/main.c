#include "main.h"
int idx = 1;
Graph create_graph() {

    Graph x;
    x.edges = make_jrb();
    x.vertices = make_jrb();

    return x;
}

Weight *create_weight(int id, int sum) {

    Weight *weight = (Weight*)malloc(sizeof(Weight));

    weight->id = id;
    weight->length = sum;

    return weight;
}

OutType *create_outType(int id, int idBus, int sum) {

    OutType * out = (OutType*)malloc(sizeof(OutType));

    out->id = id;
    out->idBus = idBus;
    out->sum = sum;
}

JRB getKey(Graph graph, char *name) {
    
    JRB node;

    jrb_traverse(node, graph.vertices) {

        if(strcmp(name, jval_s(node->val)) == 0) {

            return node;
        }
    }

    return NULL;
}

JRB getTree(JRB node) {

    return (JRB)jval_v(node->val);
}

void addVertex(Graph graph, char *name) {

    if(!getKey(graph, name)){
        
        jrb_insert_int(graph.vertices, idx++,new_jval_s(name));
    }
}

void addEdge(Graph graph, char *name1, char *name2, int idBus, int distant) {

    addVertex(graph, name1);
    addVertex(graph, name2);

    JRB subTree;
    JRB node = getKey(graph, name1);
    JRB node2 = getKey(graph, name2);
    int key = jval_i(node->key);
    int key2 = jval_i(node2->key);

    node = jrb_find_int(graph.edges,key);

    if(!node) {
        
        subTree = make_jrb();
        jrb_insert_int(graph.edges, key, new_jval_v(subTree));
        // printf("\nadd ok with id: %d\n",key);
        // if(key == 25) {
        //     printf("-key: %d\n",key);
        // }
    } else {
        // printf("\n----------------id: %d---------\n", idx);
        subTree = getTree(node);
    }

    JRB subNode = jrb_find_int(subTree, idBus);

    if(subNode == NULL) {

        jrb_insert_int(subTree, idBus, new_jval_v(create_weight(key2,distant)));
    }
}

void traverse(Graph graph, int key, JRB output) {

    JRB tree = jrb_find_int(graph.edges, key);
    JRB node;
    if(tree == NULL) {
        printf("key: %d\n",key);
        return;
    }
    
    // return;
    tree = getTree(tree);
    OutType *wKey, *wKey2;
    
    JRB subNode = jrb_find_int(output, key);

    if(subNode == 0) {

        wKey = create_outType(key, 0, 0);
        jrb_insert_int(output, key,new_jval_v(wKey));
    } else {

        wKey = jval_v(subNode->val);
    }

    jrb_traverse(node, tree) {

        int idBus = jval_i(node->key);

        Weight *valueBus = jval_v(node->val);

        int nextKey = valueBus->id;
        JRB nextNode = jrb_find_int(output, nextKey);
        int sum = valueBus->length + wKey->sum;

        if(nextNode == NULL) {

            jrb_insert_int(output, nextKey, new_jval_v(create_outType(key, idBus, sum)));
        } else {

            wKey2 = jval_v(nextNode->val);
            if(sum < wKey2->sum) {

                wKey2->id = key;
                wKey2->idBus = idBus;
                wKey2->sum = sum;

            }
        }

        traverse(graph, nextKey, output);
    }
}

void findPath(Graph graph, char* name1, char* name2) {

    if(strcmp(name1, name2) == 0) {

        printf("you are standing where you want to go!\n");
        return;
    }

    JRB node = getKey(graph, name1);
    JRB node2 = getKey(graph, name2);

    if(!node || !node2) {
        printf("you enter wrong place's name! check please!\n");
        return;
    }

    JRB output = make_jrb();

    int key = jval_i(node->key);
    int key2 = jval_i(node2->key);
    // return;
    traverse(graph, key, output);

    // JRB nodeout;
    // jrb_traverse(nodeout, output){

    //     OutType *x = jval_v(nodeout->val);
    //     printf("----------nodeout->key: %d-%d-%d\n\n", jval_i(nodeout->key),x->idBus, x->sum);
    // }
    OutType arr[100];
    int nx = getArr(output, key2, arr);
    // print(key2,nx,arr);
}

int getArr(JRB output,int end, OutType arr[]) {

    int n = 0;
    JRB node = jrb_find_int(output, end);

    if(node == NULL) return 0;

    OutType *x = jval_v(node->val);

    while(x->sum) {

        arr[n++] = *x;
        node = jrb_find_int(output, x->id);
        printf("----------nodeout->key: %d-%d-%d\n\n", x->id,x->idBus, x->sum);
        x = jval_v(node->val);
    }

    return n;
}

void print(int end, int len, OutType arr[]) {

    printf("ok!---------------------%d\n",len);
    for(int i = len - 1; i >= 0; i++) {
        // printf()
        if(i!=0) {

            printf(" xe %d ------->", arr[i].idBus);
        } else {

            printf(" xe %d", arr[i].idBus);
        }
    }
}

void readFile(Graph graph) {

    FILE *f = fopen("station26.txt", "r");

    while(!feof(f)) {

        char s[80];

        fscanf(f,"%[^\n]",s); fscanf(f,"%*c");
        // printf("%s\n",s);
        // return;
        addVertex(graph, strdup(s));
    }

    fclose(f);
}

void addValue(Graph graph) {

    FILE *f = fopen("distance26.txt","r");

    while(!feof(f)) {

        char st[30];
        char end[30];
        int dis;

        fscanf(f,"%[^\n]",st); fscanf(f,"%*c");
        fscanf(f,"%[^\n]",end); fscanf(f,"%*c");
        fscanf(f,"%d",&dis); fscanf(f,"%*c");

        printf("%-20s-%-20s:%d\n",st,end,dis);
        int idBus = 26;
        addEdge(graph,st,end,idBus,dis);
    }

    fclose(f);
}

void dropGraph(Graph graph) {

    JRB node, subNode;

    // jrb_traverse(node, graph.vertices) {

    //     free(jval_s(node->val));
    // }

    jrb_free_tree(graph.vertices);

    jrb_traverse(node, graph.edges) {

        jrb_free_tree(jval_v(node->val));
    }
}