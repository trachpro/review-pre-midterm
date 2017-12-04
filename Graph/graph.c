#include <stdio.h>
#include <stdlib.h>
#include "jrb.h"
#include "dllist.h"
#include "graph.h"


vGraph vg_create_graph() {
        vGraph g;
        g.edges = make_jrb(); // make red-black tree for edges
        g.vertices = make_jrb(); // make red-black tree for vertices
        return g;
}


void vg_add_vertex(vGraph g, int id, Jval val) {
        JRB node = jrb_find_int(g.vertices, id);

        if (node != NULL) {
                fprintf(stderr, "Duplicated vertex id: %d -> Replace.\n", id);
                jrb_delete_node(node);
        }

        jrb_insert_int(g.vertices, id, val);
}


int vg_get_vertex(vGraph g, int id, Jval * val) {
        JRB node = jrb_find_int(g.vertices, id);

        if (node != NULL) {
                *val =  node->val;
                return 1;
        } else {
                return 0;
        }
}


void vg_add_edge(vGraph g, int v1, int v2, double weight) {
        JRB node; // vertex node in edge tree
        JRB tree; // tree to save edges from each vertex node

        // find v1 in edges list
        node = jrb_find_int(g.edges, v1);

        if (node == NULL) {
                tree = make_jrb();
                jrb_insert_int(g.edges, v1, new_jval_v(tree));
        } else {
                tree = jval_v(node->val);
        }

        jrb_insert_int(tree, v2, new_jval_d(weight));
}


double vg_get_edge_value(vGraph g, int v1, int v2) {
        JRB node = jrb_find_int(g.edges, v1);
        if (node != NULL) {
                JRB tree = jval_v(node->val);
                node = jrb_find_int(tree, v2);
                if (node != NULL) {
                        return jval_d(node->val);
                }
        }
        return VG_INFINITY;
}


int vg_has_edge(vGraph g, int v1, int v2) {
        JRB node; // vertex node in edge tree
        JRB tree; // tree to save edges from each vertex node

        // find v1 in edges list
        node = jrb_find_int(g.edges, v1);

        if (node != NULL) {

                // get the edge list of v1
                tree = jval_v(node->val);

                // check if v2 is in the edge list of v1
                node = jrb_find_int(tree, v2);
                if (node != NULL) {
                        return 1;
                }
                        
        }

        return 0;
}

int vg_indegree(vGraph g, int v, int * output) {
        JRB node;
        int count = 0;

        jrb_traverse(node, g.vertices) {
                int head = jval_i(node->key);
                if (vg_has_edge(g, head, v)) {
                        output[count] = head;
                        count++;
                }
        }

        return count;
}

int vg_outdegree(vGraph g, int v, int * output) {
        JRB node = jrb_find_int(g.edges, v);
        int count = 0;

        if (node != NULL) {
                JRB tree = jval_v(node->val);
                jrb_traverse(node, tree) {
                        output[count] = jval_i(node->key);
                        count++;
                }
        }

        return count;
}


void vg_drop_graph(vGraph g) {
        jrb_free_tree(g.vertices);
        JRB node;
        jrb_traverse(node, g.edges) {
                jrb_free_tree(jval_v(node->val));
        }
        jrb_free_tree(g.edges);
}


// Deep-First-Search
// start: start vertex
// stop: end vertex ; set it to -1 to traverse all
// func: function to excute with each node
int vg_DFS(vGraph g, int start, int stop, void (*func)(Jval)) {
        JRB node;
        JRB visited = make_jrb();
        Dllist stack;
        Dllist temp;
        int adjacents[MAX_ADJACENT_NUMBER];
        int count;
        int i;
        int key;
        int cycle = 0;
        Jval node_val;

        node = jrb_find_int(g.vertices, start);
        if (node == NULL) {
                fprintf(stderr, "Graph does not have vertex with id: %d\n", start);
                return 0;
        }
    
        // Create a graph name 'visited' in which each node's key is
        // a vertex, and it's key indicate whether the vertex has been
        // visited (1) or not (0)
        jrb_traverse(node, g.vertices) {
                jrb_insert_int(visited, jval_i(node->key), new_jval_i(0));
        }

        // Create a stack and push the first element
        stack = new_dllist();
        dll_append(stack, new_jval_i(start));

        // Traversing
        while(dll_empty(stack) != 1) {
                // Take the top element in the stack
                temp = dll_last(stack);
                key = jval_i(temp->val);

                // If this is the required vertex, return
                if (key == stop) {
                        return 0;
                }

                // Do something with node
                node_val = dll_val(temp);
                func(node_val);

                
                // Pop this element
                dll_delete_node(temp);

                // Mark this element as 'visited'
                node = jrb_find_int(visited, key);
                jrb_delete_node(node);
                jrb_insert_int(visited, key, new_jval_i(1));

                count = vg_outdegree(g, key, adjacents);

                for (i = 0; i < count; i++) {
                        // Graph has cycle
                        if (adjacents[i] == start) {
                                cycle = 1;
                                break;
                        }

                        // If the vertice has not been visited, push it
                        node = jrb_find_int(visited, adjacents[i]);
                        if (jval_i(node->val) == 0) {
                                key = jval_i(node->key);
                                dll_append(stack, new_jval_i(key));
                                // Mark this element as 'visited'
                                jrb_delete_node(node);
                                jrb_insert_int(visited, key, new_jval_i(1));
                        }
                }

                if (cycle == 1) {
                        break;
                }
        }

        return cycle;
}

void do_nothing(){}
int vg_DAG(vGraph g) {
        JRB node;
        jrb_traverse(node, g.vertices) {
                if (vg_DFS(g, jval_i(node->key), -1, do_nothing)) {
                        return 0;
                }
        }
        return 1;
}


void vg_topological_sort(vGraph g, int * output, int * n) {
        JRB node;
        int indegreeList[100];
        int adjacents[100];
        int count = 0;
        int i, total;
        int key;
        int tail;
        Dllist queue = new_dllist();
        Dllist temp;

        jrb_traverse(node, g.vertices) {
                indegreeList[count] = vg_indegree(g, jval_i(node->key), adjacents);
                if (indegreeList[count] == 0) {
                        dll_append(queue, node->key);
                }
                count++;
        }
    
        *n = count;
        count = 0;
    
        while(dll_empty(queue) != 1) {
                temp = dll_first(queue);
                key = jval_i(temp->val);
                dll_delete_node(temp);

                output[count] = key;
                indegreeList[key] = -1;

                total = vg_outdegree(g, key, adjacents);
                for (i = 0; i < total; i++) {
                        tail = adjacents[i];
                        indegreeList[tail]--;
                        if (indegreeList[tail] == 0) {
                                dll_append(queue, new_jval_i(tail));
                        }
                }
        
                count++;
        }
}


// Find the shortest way using Dijiktra algorithm
// source_id : beginning point
// target_id: ending point. set = -1 to scan whole the graph
// prev: previous
// ret_prev: return array for previous position of each point (used to find the way from destination to source)
// ret_dist: return array of min distace from source to each point
void vg_find_shortest_path(vGraph g, int source_id, int target_id, JRB * prev_tree, JRB * dist_tree) {

        Dllist Q = NULL;
        Dllist Q_node = NULL;

        int vertex_id;
        JRB vertex_node;

        double min_dist;
        double alt;
        int min_dist_node_id;
        Dllist min_dist_node_dll;
        int min_dist_node_set; // flag to determine min node was set or not

        JRB node_jrb;
        int node_id;
        double node_dist;

        JRB tmp_node;

        // make a distance tree
        *dist_tree = make_jrb();

        // make a prev. treeso save paths
        *prev_tree = make_jrb();

        // set the distance from source to source equal to 0
        jrb_insert_int(*dist_tree, source_id, new_jval_d(0));

        // create an empty queue
        Q = new_dllist();

        // Loop for all other vertices
        jrb_traverse(vertex_node, g.vertices) {
                vertex_id = jval_i(vertex_node->key);
                if (vertex_id != source_id) {
                        // Unknown distance function from source to each node set to infinity
                        jrb_insert_int(*dist_tree, vertex_id, new_jval_d(VG_INFINITY));
                }

                // All nodes initially in Q
                // Enqueue
                dll_prepend(Q, new_jval_i(vertex_id));

        }

        
        // The main loop of Dijiktra algo.
        min_dist = 0;
        min_dist_node_id = 0;

        while (!dll_empty(Q)) { 
                // Reset the min node set flag.
                min_dist_node_set = 0;
                // Determine the node with min distance
                // In the first run-through, this vertex is the source node
                dll_traverse(Q_node, Q) {
                        // determine min node was set or not. Use to initialize the min node value
                        if (!min_dist_node_set) {
                                min_dist_node_id = jval_i(Q_node->val);
                                min_dist = jval_d(jrb_find_int(*dist_tree, min_dist_node_id)->val);
                                min_dist_node_dll = Q_node;
                                min_dist_node_set = 1;
                        } else {
                                // if the min node wasn't set
                                node_id = jval_i(Q_node->val);
                                node_dist = jval_d(jrb_find_int(*dist_tree, node_id)->val);

                                // if found a not with the distance < min distance
                                if (node_dist < min_dist) {
                                        min_dist = node_dist;
                                        min_dist_node_id = node_id;
                                        min_dist_node_dll = Q_node;
                                }
                        }

                }

                // remove min node from Queue Q
                dll_delete_node(min_dist_node_dll);

                // terminate if found a way from source to target
                if (min_dist_node_id == target_id) {
                        return;
                }

                // Loop for all neighbor u which has not yet been removed from Q.
                dll_traverse(Q_node, Q) {
                        node_id = jval_i(Q_node->val);
                        if (vg_has_edge(g, min_dist_node_id, node_id)) {

                                alt = min_dist + vg_get_edge_value(g, min_dist_node_id, node_id);
                                
                                node_jrb = jrb_find_int(*dist_tree, node_id);

                                if (node_jrb != NULL) {
                                        node_dist = jval_d(node_jrb->val);

                                        // A shorter path to u has been found
                                        if (alt < node_dist) {

                                                // update distance of u
                                                jrb_delete_node(node_jrb);
                                                jrb_insert_int(*dist_tree, node_id, new_jval_d(alt));

                                                // update prev. table
                                                // prev[v] ← u
                                                tmp_node = jrb_find_int(*prev_tree, node_id);
                                                if (tmp_node) {
                                                        jrb_delete_node(tmp_node);
                                                }
                                                printf("v = %d, u = %d\n", node_id, min_dist_node_id);
                                                jrb_insert_int(*prev_tree, node_id, new_jval_i(min_dist_node_id));

                                        }
                                }
                                
                        }
                }

                
        }

}

void vg_print_graph(vGraph g) {
        JRB node;
        int key;
        JRB edge_list_tree;
        char *s; 
        JRB edge_tree;
        JRB edge_node;
        jrb_traverse(node, g.vertices) {
                key = jval_i(node->key);
                
                printf("*** NODE:  %d  ***\n", key);

                s = jval_s(node->val);
                printf("NAME: %s\n", s);

                edge_list_tree = jrb_find_int(g.edges, key);

                if (edge_list_tree != NULL) {
                        edge_tree = jval_v(edge_list_tree->val);
                        jrb_traverse(edge_node, edge_tree) {
                               printf("(%d, %lf) ; ", jval_i(edge_node->key), jval_d(edge_node->val));
                        }
                        printf("\n");
                }

        }
}


