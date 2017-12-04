#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "jrb.h"



typedef struct {
   JRB edges;
   JRB vertices;
} vGraph;


// for vg_DFS()
#define MAX_ADJACENT_NUMBER 1000

#define VG_INFINITY INFINITY

vGraph vg_create_graph();

void vg_add_vertex(vGraph g, int id, Jval val);

int vg_get_vertex(vGraph g, int id, Jval * val);

void vg_add_edge(vGraph g, int v1, int v2, double weight);

double vg_get_edge_value(vGraph g, int v1, int v2);

int vg_has_edge(vGraph g, int v1, int v2);

int vg_indegree(vGraph g, int v, int * output);

int vg_outdegree(vGraph g, int v, int * output);

void vg_drop_graph(vGraph g);

int vg_DFS(vGraph g, int start, int stop, void (*func)(Jval));

int vg_DAG(vGraph g);

// Sorting
void vg_topological_sort(vGraph g, int * output, int * n) ;

// Dijiktra algorithm
void vg_find_shortest_path(vGraph g, int source_id, int target_id, JRB * prev_tree, JRB * dist_tree);

// for debugging purpose
void vg_print_graph(vGraph g);


#endif
