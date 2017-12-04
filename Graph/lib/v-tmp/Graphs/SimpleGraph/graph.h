typedef struct {
        int * matrix;
        int sizemax;
} Graph;

Graph createGraph(int sizemax);
void addEdge(Graph g, int v1, int v2);
int isAjacent(Graph g, int v1, int v2);
int getAjacentVertices(Graph g, int vertex, int * output);
void dropGraph(Graph g);