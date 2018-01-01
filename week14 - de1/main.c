#include "main.h"

Graph make_graph() {

    Graph g;

    g.edges = make_jrb();
    g.vertices = make_jrb();

    return g;
}

JRB getJRBTree(JRB tree) {

    return (JRB)jval_v(tree->val);
}

void addVertex(Graph graph, char *name, int id) {

    JRB tree = jrb_find_str(graph.vertices, name);

    if(!tree) {

        jrb_insert_str(graph.vertices, strdup(name) , new_jval_i(id));

        jrb_insert_int(graph.edges, id, new_jval_v(make_jrb()));
    } else {

        // printf("trung roif\n");
    }
}

void addEdgeOneDirection(Graph graph, int id1, int id2, int weight) {

    JRB tree = jrb_find_int(graph.edges, id1);
    
    tree = getJRBTree(tree);
    
    // return;
    JRB node = jrb_find_int(tree, id2);
    
    if(!node) {

        jrb_insert_int(tree, id2, new_jval_i(weight));
    } else {

        node->val = new_jval_i(weight);
    }
}

void addEdge(Graph graph, int id1, int id2, int weight) {

    addEdgeOneDirection(graph, id1, id2, weight);
    addEdgeOneDirection(graph, id2, id1, weight);
}

int getWeight(Graph graph, int id1, int id2) {

    JRB tree = jrb_find_int(graph.edges, id1);

    tree = getJRBTree(tree);

    JRB node = jrb_find_int(tree, id2);

    if(node) {

        return jval_i(node->val);
    } else {

        return INFINITY_VALUE;
    }
}

void addMoreWeight(Graph graph, int id1, int id2) {

    int a = getWeight(graph, id1, id2);
    // printf("%d----\n\n", a);
    // return;
    int weight = (a == INFINITY_VALUE? 1: a + 1);
    
    addEdge(graph, id1, id2, weight);
}

char * getVertexName(Graph graph, int id) {

    JRB node;

    jrb_traverse(node, graph.vertices) {

        int val = jval_i(node->val);

        if(val == id) {

            return jval_s(node->key);
        }
    }

    return NULL;
}

int getKeyByInt(JRB tree, int id) {

    JRB node;

    jrb_traverse(node, tree) {

        int val = jval_i(node->val);

        if(val == id) {

            return jval_i(node->key);
        }
    }

    return -1;
}

int initArray(int * arr, int n) {

    for(int i = 0; i < n; i++) {

        arr[i] = 99999;
    }
}

void sortOut(OutType *arr, int n) {

    for(int i = 0; i < n-1; i++) {

        for(int j = i+1; j< n; j++) {

            if(arr[i].val> arr[j].val) {

                OutType tem = arr[i];
                arr[i] = arr[j];
                arr[j] = tem;
            }
        }
    }
}

void copyArr(OutType *outArr, int * intArr, int n) {

    for(int i = 0; i< n; i++) {

        intArr[i] = outArr[i].key;
    }
}

int getAdjList(Graph graph, int id, int *output) {

    OutType arr[100];
    int i = 0;

    JRB tree = jrb_find_int(graph.edges, id);

    tree = getJRBTree(tree);

    JRB node;

    jrb_traverse(node, tree) {

        int key = jval_i(node->key);
        int val = jval_i(node->val);

        arr[i].key = key;
        arr[i].val = val;
        i++;
    }

    sortOut(arr, i);
    copyArr(arr, output, i);

    return i;
}

void printReverse(Graph graph, int id) {

    int out[100];
    
    int n = getAdjList(graph, id, out);

    for(int i = n-1; i >= 0; i--) {

        printf(" %-12s",getVertexName(graph, out[i])); 
    }

    printf("\n\n");
}

Weight * make_weight(int id, int sum) {

    Weight *a = (Weight*)malloc(sizeof(Weight));
    a->id = id;
    a->sum = sum;

    return a;
}

int deQueue(Dllist queue, JRB ow ) {

    Dllist node, min = dll_first(queue);
    JRB x;
    x =  jrb_find_int(ow, jval_i(min->val));
    int minVal = jval_i(x->val);
  
    dll_traverse(node, queue) {
      
        x =  jrb_find_int(ow, jval_i(node->val));

        if(jval_i(x->val) < minVal) {

            min = node;
            minVal = jval_i(x->val);
        }
    }
    

    minVal = jval_i(min->val);

    dll_delete_node(min);

    return minVal;
}

int getWeightOnOW(JRB ow, int u) {

    JRB x = jrb_find_int(ow, u);

    return jval_i(x->val);
}

void relax(JRB node, int u, JRB ow, JRB op) {

    int key = jval_i(node->key);
    int weight = jval_i(node->val);
    int wu = getWeightOnOW(ow, u);
    int wn = getWeightOnOW(ow, key);

    if(wu + weight < wn) {

        JRB subNode = jrb_find_int(ow, key);
        subNode->val = new_jval_i(wu + weight);

        subNode = jrb_find_int(op, key);
        subNode->val = new_jval_i(u);
    }
}

void Dijkstra(Graph graph, int start, JRB ow, JRB op) {

    JRB node;
    Dllist queue = new_dllist();

    jrb_traverse(node, graph.edges) {

        jrb_insert_int(ow, jval_i(node->key), new_jval_i(INFINITY_VALUE));
        jrb_insert_int(op, jval_i(node->key), new_jval_v(-1));
        dll_prepend(queue, node->key);
    }

    node = jrb_find_int(ow, start);

    if(!node) return;

    node->val = new_jval_i(0);
    
    while(!dll_empty(queue)) {

        int u = deQueue(queue, ow);
        node = jrb_find_int(graph.edges, u);
        
        if(node != NULL) {
            node = getJRBTree(node);
            JRB subNode;

            jrb_traverse(subNode, node) {
                relax(subNode, u, ow, op);
            }
        }
        
    }
}

void printOut(Graph graph, int arr[], int n) {

    if(n ==0) {
        printf("there is no path!\n");
        return;
    }

    char a[50];
    JRB x;

    for(int i = n - 1; i > 0; i--) {
       
        printf(" %s --->",getVertexName(graph, a[i])); 
    }

    printf(" %s\n\n",getVertexName(graph, a[0])); 
}

void convert(Graph graph,int start,int end) {
    // return;
    JRB node = jrb_find_int(graph.edges, start);

    if(!node) {

        printf("invalid input!\n");
        return;
    }

    node = jrb_find_int(graph.edges, end);

    if(!node) {

        printf("invalid input!\n");
        return;
    }

    JRB op = make_jrb();
    JRB ow = make_jrb();

    Dijkstra(graph, start, ow, op);

    

    node = jrb_find_int(ow, end);
    if(jval_i(node->val) == INFINITY_VALUE) {

        printf("there is no path to here!\n");
        return;
    }

    jrb_traverse(node, op) {

        printf("op:%d- %d\n",jval_i(node->key) ,jval_i(node->val));
    }



    node = jrb_find_int(op, end);

    
    if(!node) {
        printf("node not exist!\n");
        return;
    }

    int key = end;

    while(1) {

        if(key == start) {
            printf("%s\n", getVertexName(graph, key));
            break;
        }
        
        printf("%s------>",getVertexName(graph, key));
       
        node = jrb_find_int(op, key);
        key = jval_i(node->val);
    }

    dropJRB(ow);
    dropJRB(op);
}

void dropJRB(JRB g) {
    jrb_free_tree(g);
}

void readProduct(Graph graph) {

    FILE *f = fopen("products.txt", "r");
    int id;
    char name[80];

    while(!feof(f)) {
        fscanf(f,"%d", &id);
        fscanf(f,"%s", name);

        addVertex(graph, name, id);
        printf("%d-%s\n",id, name);
    }

    fclose(f);
}

void loadIntoGraph(Graph graph, int* arr, int n) {

    for(int i = 0; i < n-1; i++) {

        for(int j = i+1; j < n; j++) {

            addMoreWeight(graph, arr[i], arr[j]);
        }
    }
}

void printListInt(int * arr, int n) {

    for(int i = 0; i<n; i++) {
        printf("list-- %-5d", arr[i]);
    }

    printf("\n\n\n");
}

void readOrderHistory(Graph graph) {

    FILE *f = fopen("orderhistory.txt","r");
    char a[80];
    int arr[100];
    int n = 0;
    char c;

    while(!feof(f)) {

        c = fgetc(f);
        
        if(c == '\n' || c == EOF) {
            
            loadIntoGraph(graph, arr, n);
            // printListInt(arr,n);
            n = 0;
            printf("\n");
        }

        if(c != ' ' && c!= '\n' && c!= EOF) {
            arr[n] = atoi(&c);
            printf("a[n] = %d\n", arr[n]);
            n++;
        }
        // fscanf(f, "%[^\n]", a); fscanf(f, "%*c");
        // printf("history : %s\n",a);
    }

    fclose(f);
}

// de thi k55

char *trim(char *str)
{
    size_t len = 0;
    char *frontp = str;
    char *endp = NULL;

    if( str == NULL ) { return NULL; }
    if( str[0] == '\0' ) { return str; }

    len = strlen(str);
    endp = str + len;

    /* Move the front and back pointers to address the first non-whitespace
     * characters from each end.
     */
    while( isspace((unsigned char) *frontp) ) { ++frontp; }
    if( endp != frontp )
    {
        while( isspace((unsigned char) *(--endp)) && endp != frontp ) {}
    }

    if( str + len - 1 != endp )
            *(endp + 1) = '\0';
    else if( frontp != str &&  endp == frontp )
            *str = '\0';

    /* Shift the string so that it starts at str so that if it's dynamically
     * allocated, we can still free it on the returned pointer.  Note the reuse
     * of endp to mean the front of the string buffer now.
     */
    endp = str;
    if( frontp != str )
    {
            while( *frontp ) { *endp++ = *frontp++; }
            *endp = '\0';
    }


    return str;
}

int split(char a[][100], char *s, char c) {

    int n = strlen(s);

    int i = 0;
    int t = 0;
    int st = 0;
    while(t!=n) {

        if(s[t] == c) {
            if(a[i][0] && s[t+1]) i++;
            t++;
            st = 0;
            continue;
        }

        a[i][st] = s[t];
        st++;
        t++;
    }

    return i+1;
}

int getKeyFromString(char *s) {

    int id;
    char i;
    strcpy(s,trim(s));
    
    sscanf(s,"%c%d",&i,&id);
    
    return id;
}

void xulyStr(Graph graph, char *s) {

    char a[100][100], b[2][100], c[10][100];
    
    int n = split(a,trim(s),':');
    int id = getKeyFromString(a[0]);

    addVertex(graph, trim(a[0]), id);

    if(n == 1) return;

    // printf("a[1111] =%s\n", trim(a[1]));
    n = split(c, trim(a[1]), ' ');

    for(int i = 0; i < n; i++) {
        
        split(b,trim(c[i]),'-');

        char ss[100];
        strcpy(ss, trim(b[0]));
        int ikey = getKeyFromString(ss);

        addVertex(graph, ss, ikey);
        addEdgeOneDirection(graph, id, ikey, atoi(b[1]));
    }
}

void readTepDuLieu(Graph graph) {
    
    FILE *f = fopen("tepdulieu.txt", "r");

    if(!f) {

        printf("file not found!\n");
        return;
    }

    char a[100];
    while(!feof(f)) {
        
        fscanf(f, "%[^\n]",a); fscanf(f,"%*c");
        xulyStr(graph, a);
    }
}

int tongNut(Graph graph) {
    int i = 0;

    JRB node;
    jrb_traverse(node, graph.vertices) {

        i++;
    }

    return i;
}

int tongCung(Graph graph) {
    int i = 0;

    JRB node;
    jrb_traverse(node, graph.edges) {

        JRB subNode;
        JRB subTree = getJRBTree(node);
        printf("%d: ", jval_i(node->key));
        jrb_traverse(subNode, subTree) {
            i++;
        };
        printf("\n");
    }

    return i;
}