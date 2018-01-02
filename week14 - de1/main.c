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
    
    if(tree == NULL) return;

    JRB nTree = jrb_find_int(graph.edges, id2);

    if(nTree == NULL) return;
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
    // printf("addEdge: %d-%d\n",id1, id2);
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

int outCome(Graph graph, int key, int *out) {

    JRB tree = jrb_find_int(graph.edges, key);
    tree = getJRBTree(tree);

    JRB node;

    int i = 0;
    jrb_traverse(node, tree) {

        out[i] = jval_i(node->key);
        i++;
    }

    return i;
} 

int inCome(Graph graph, int key, int *out) {

    JRB tree;

    JRB node;

    int i = 0;
    jrb_traverse(node, graph.edges) {

        JRB tree = getJRBTree(node);
        JRB subNode;

        jrb_traverse(subNode, tree) {

            if(key == jval_i(subNode->key)) {

                out[i]= jval_i(node->key);
                i++;
            }
        }
    }

    return i;
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

    node = jrb_find_int(op, end);

    
    if(!node) {
        printf("node not exist!\n");
        return;
    }

    int key = end;

    Dllist stack = new_dllist();
    Dllist listnode;

    while(1) {

      dll_prepend(stack, new_jval_i(key));
        if(key == start) {
	  //printf("%s\n", getVertexName(graph, key));
            break;
        }
        
        //printf("%s------>",getVertexName(graph, key));
	
        node = jrb_find_int(op, key);
        key = jval_i(node->val);
    }

    dll_traverse(listnode, stack) {
      key = jval_i(listnode->val);
      listnode == dll_last(stack)? printf("%s",getVertexName(graph, key)): printf("%s->",getVertexName(graph, key));
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
        addEdgeOneDirection(graph, ikey, id, atoi(b[1]));
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

void congVietNgayTruoc(Graph graph, int id) {

    int out[100];

    int n = inCome(graph, id, out);
    if(n == 0) {
      printf("khong co nut lien ke cua %d\n", id);
    }
    printf("nut lien ke la: ");
    for(int i = 0; i< n; i++) {

        printf("%5d", out[i]);
    }

    printf("\n");
}

void initU(int *u, int n) {

    for(int i = 0; i< n; i++) u[i] = 0;
}

void getListJob(Graph graph, int id, int *u) {

    int out[100];
    int n = inCome(graph, id,out);

    for(int i = 0; i< n; i++) {

        u[out[i]] = 1;
        getListJob(graph, out[i], u);
    }
}

void tatCaCacViecTruoc(Graph graph, int id) {

    int u[100];

    initU(u, 100);
    getListJob(graph, id, u);
    for(int i = 0; i< 100; i++) {

        if(u[i]) {

            printf("%5d",i);
        }
    }
    printf("\n");
}

int deQueue2(Dllist queue, JRB ow ) {

    Dllist node, min = dll_first(queue);
    JRB x;
    x =  jrb_find_int(ow, jval_i(min->val));
    int maxVal = jval_i(x->val);
  
    dll_traverse(node, queue) {
      
        x =  jrb_find_int(ow, jval_i(node->val));

        if(jval_i(x->val) > maxVal) {

            min = node;
            maxVal = jval_i(x->val);
        }
    }
    
 
    maxVal = jval_i(min->val);
    printf("max %d -%d\n", jval_i(min->val), maxVal);
    dll_delete_node(min);
    // printf("max %d -%d\n", jval_i(min->val), maxVal);
    return maxVal;
}

void relax2(JRB node, int u, JRB ow, JRB op) {

    int key = jval_i(node->key);
    int weight = jval_i(node->val);
    int wu = getWeightOnOW(ow, u);
    int wn = getWeightOnOW(ow, key);
    // printf("weight = %d\n", weight);
    if(wu + weight > wn) {
        // printf("wn = %d\n wu = %d\n", wn, wu);
        JRB subNode = jrb_find_int(ow, key);
        subNode->val = new_jval_i(wu + weight);

        subNode = jrb_find_int(op, key);
        subNode->val = new_jval_i(u);
        // printf("parent %d-%d\n",jval_i(subNode->key) ,jval_i(subNode->val));
    }
}

void Dijkstra2(Graph graph, JRB ow, JRB op) {

    JRB node;
    Dllist queue = new_dllist();
    int out[100];

    jrb_traverse(node, graph.edges) {
        int key = jval_i(node->key);

        int oc = outCome(graph, key, out);
        int in = inCome(graph,key, out);

        int val = oc != 0 && in == 0? 0: -1;
        printf(" %d = %d\n",key, val);
        jrb_insert_int(ow, jval_i(node->key), new_jval_i(val));
        jrb_insert_int(op, jval_i(node->key), new_jval_v(-1));
        dll_prepend(queue, node->key);
    }
    
    while(!dll_empty(queue)) {

        int u = deQueue2(queue, ow);
        printf("u = %d\n", u);
        node = jrb_find_int(graph.edges, u);
        
        if(node != NULL) {
            node = getJRBTree(node);
            JRB subNode;

            jrb_traverse(subNode, node) {
                relax2(subNode, u, ow, op);
            }
        }
        
    }
}

void convert2(Graph graph) {

    JRB ow = make_jrb();
    JRB op = make_jrb();

    Dijkstra2(graph, ow, op);

    JRB node;

    int key = 2;
    node = jrb_find_int(ow, key);
    printf("weight = %d\n", jval_i(node->val));
    printf("traverse: \n");
    

    while(key != -1) {

        
        printf("%s------>",getVertexName(graph, key));
       
        node = jrb_find_int(op, key);
        key = jval_i(node->val);
    }
}

int DFS(Graph graph, int start, int end) {

    int flag = 0;

    // printf("dfs");
    JRB node = jrb_find_int(graph.edges, start);

    if(node == NULL) {

        return flag;
    }

    JRB visited = make_jrb();
    Dllist stack = new_dllist();

    dll_prepend(stack, new_jval_i(start));
    Dllist nodeList;
    // printf("dfs");
    while(!dll_empty(stack)) {

        nodeList = dll_first(stack);
        int u = jval_i(nodeList->val);
        dll_delete_node(nodeList);
        
        
        if(u == end) {
            flag++;
        }

        node = jrb_find_int(visited, u);

        if(node == NULL) {
            jrb_insert_int(visited, u, new_jval_i(1));
        } else {
            continue;
        }
       
        node = jrb_find_int(graph.edges, u);

        JRB tree = getJRBTree(node);

        jrb_traverse(node, tree) {

            int key = jval_i(node->key);
            // printf("--\n%d--%d\n", key, start);
            if(jrb_find_int(visited, key) == NULL) {

                dll_prepend(stack, new_jval_i(key));
            }
        }

    }
    return flag;
}

int  BFS(Graph graph, int start, int end) {

    int flag = 0;
    JRB node = jrb_find_int(graph.edges, start);

    if(node == NULL) {

        return flag;
    }

    JRB visited = make_jrb();
    Dllist stack = new_dllist();

    dll_append(stack, new_jval_i(start));
    Dllist nodeList;

    while(!dll_empty(stack)) {

        nodeList = dll_first(stack);
        int u = jval_i(nodeList->val);
        dll_delete_node(nodeList);
        
        
        if(u == end) break;

        node = jrb_find_int(visited, u);

        if(node == NULL) {
            jrb_insert_int(visited, u, new_jval_i(1));
        } else {
            continue;
        }
        printf("u = %d-", u);
        node = jrb_find_int(graph.edges, u);

        JRB tree = getJRBTree(node);

        jrb_traverse(node, tree) {

            int key = jval_i(node->key);
            if(jrb_find_int(visited, key) == NULL) {

                dll_append(stack, new_jval_i(key));
            }
            if(key == start) flag = 1;
        }

    }
    return flag;
}

void copyJRB(JRB des, JRB sour) {

    JRB node;
    jrb_traverse(node, sour) {

        int key = jval_i(node->key);
        jrb_insert_int(des, key, new_jval_i(1));
    }
}

// void  DFSAV(Graph graph, int start, Dllist stack) {
//     int out[100];

//     JRB tree = jrb_find_int(graph.edges, start);
//     JRB node;
//     tree = getJRBTree(tree);

//     jrb_traverse(node, tree) {

//         int n = jval_i(node->key);
//         dll_prepend(stack, new_jval_i(n));

//         int in = inCome(graph, n,out);

//         if(in == 0) {
//             printf(list)
//         }
//     }
// }

int deleteEdge(Graph graph, int vertex, int value) {
  JRB node = jrb_find_int(graph.edges, vertex);
  if(node == NULL) return 0;

  JRB tree = (JRB) jval_v(node->val);
  JRB nodeTree;
  jrb_traverse(nodeTree, tree) {
    if (jval_i(nodeTree->key) == value) jrb_delete_node(nodeTree);
    return 1;
  } 
  return 0;
}

int topologicalSort(Graph graph, int *output)
{
    int n = 0;
    Dllist queue = new_dllist();
    int out[100];
    JRB node;

    jrb_traverse(node, graph.edges)
    {
        if (inCome(graph, jval_i(node->key), out) == 0)
            dll_prepend(queue, new_jval_i(jval_i(node->key)));
    }

    Dllist nodeList;

    while (!dll_empty(queue))
    {
        nodeList = dll_first(queue);
        int v = jval_i(dll_val(nodeList));
        output[n++] = v;

        dll_delete_node(nodeList);
        JRB nodeGraph = jrb_find_int(graph.edges, v);

        if (nodeGraph != NULL)
        {
            JRB tree = (JRB)jval_v(nodeGraph->val);
            jrb_traverse(node, tree)
            {
                deleteEdge(graph, v, jval_i(node->key));
                if (inCome(graph, jval_i(node->key), out) == 0)
                    dll_prepend(queue, new_jval_i(jval_i(node->key)));
            }
        }
    }

    return n;
} 

int DAG(Graph graph) {
  JRB vertex;
  jrb_traverse(vertex, graph.vertices) {
    int hasCycle = DFS(graph, jval_i(vertex->val), -1);
    if(hasCycle) return 0;
  }
  return 1;
}

void createConnection(Graph graph) {

    JRB node;

    jrb_traverse(node, graph.edges) {

        int key = jval_i(node->key);
        addEdge(graph, key, key + 10, 1);
        addEdge(graph, key, key+1, 1);
        addEdge(graph, key, key - 10, 1);
        addEdge(graph, key, key-1, 1);
    }
}

int readMeCung(Graph graph) {

    FILE *f = fopen("mecung.txt", "r");

    char a[80];
    int h = 1;
    char str[3];
    fscanf(f,"%[^\n]",a); fscanf(f,"%*c");
    while(!feof(f)) {
        int t = 1;
        fscanf(f,"%[^\n]",a); fscanf(f,"%*c");
        char c;
        int strbuff = strlen(a);
        
        int subLen = 0;
        while(subLen < strbuff) {
            
            sscanf(subLen + a, "%c", &c);
            subLen += sizeof(c);

            if(c != ' ') {
                int tem = atoi(&c);
                printf("%d", tem);

                if(tem == 0) {
                    
                    str[0] = h + '0';

                    str[1] = t + '0';
                    str[2] = '\0';

                    addVertex(graph, str, h * 10 + t);
                }

                t++;
            } else {
                printf("%c",c);
            }
        }
        h++;
        printf("\n");
    }

    createConnection(graph);
    fclose(f);
}

void banBe(Graph graph, int id, JRB rel, int level, JRB visited) {

    JRB node = jrb_find_int(graph.edges, id);
    
    if(!node) return;

    jrb_insert_int(visited, id, new_jval_i(1));
    
    JRB tree = getJRBTree(node);
    level++;
    JRB relTree = jrb_find_int(rel, level);
    Dllist queue;
    if(!relTree) {
        queue = new_dllist();
        jrb_insert_int(rel, level, new_jval_v(queue));
    }else {

        queue = (Dllist)jval_v(relTree->val);
    }

    int dem = 0;
    jrb_traverse(node, tree) {

        if(!jrb_find_int(visited,jval_i(node->key))) {
            dem ++;
            dll_append(queue, node->key);
            jrb_insert_int(visited,jval_i(node->key), new_jval_i(1));
        }
    }

    Dllist listNode;

    dll_traverse(listNode, queue) {

        banBe(graph, jval_i(listNode->val), rel, level, visited);
    }
    level--;
}

void listBB(Graph graph) {

    JRB rel = make_jrb();
    JRB visited = make_jrb();
    int level = 0;

    banBe(graph, 33,rel, level, visited);

    JRB node;
    jrb_traverse(node, rel) {

        Dllist queue = (Dllist)jval_v(node->val);
        Dllist subNode;
        printf("%d: ", jval_i(node->key));
        jrb_traverse(subNode, queue) {

            printf("%d ", jval_i(subNode->val));
        }
        printf("\n ");
    }
}

int maxLienThong(Graph graph) {
  int max = 0;

  JRB node;
  int out[100];

  jrb_traverse(node, graph.edges) {

    int a = inCome(graph, jval_i(node->key), out);
    if(a > max) {

      max = a;
    }
  }

  return max;
}

void listLienThong(Graph graph) {

  int max = maxLienThong(graph);

  int out[100];

  JRB node;

  printf("Cac nut co so lien thong lon nhat la: ");
  jrb_traverse(node, graph.edges) {

    if(max == inCome(graph, jval_i(node->key), out)) {

      printf("%-5d", jval_i(node->key) - 11);
    }
  }

  printf("\n");
}

void listDao(Graph graph) {

  int out[100];

  JRB node;

  printf("Cac nut dao la: ");
  jrb_traverse(node, graph.edges) {

    if(inCome(graph, jval_i(node->key), out) == 0) {

      printf("%-5d", jval_i(node->key) - 11);
    }
  }

  printf("\n");
}
