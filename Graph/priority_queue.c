// Priority queue - used in Dijiktra algorithm
#include <stdlib.h>
#include "priority_queue.h"
#include "dllist.h"

vprq_list_t vprq_create() {
    return new_dllist();
}


void vprq_enqueue(vprq_list_t  list, int val, double priority) {
    
    // create new item
    vprq_item_t * item;
    item = malloc(sizeof(vprq_item_t));
    item->val = val;
    item->priority = priority;

    // enqueue
    dll_prepend(list, new_jval_v(item));

}


vprq_list_t vprq_find_node(vprq_list_t  list, int val) {
       
        vprq_list_t node;
        vprq_item_t * node_item;
        int node_val;

        dll_traverse(node, list) {

                // Get the value of the node
                node_item = jval_v(node->val);
                node_val = node_item->val;

                // if found the node with finding value
                if (node_val == val) {
                        return node;
                }
        }


        return NULL;
}


double vprq_get_priority(vprq_list_t node) {
        double priority;
        vprq_item_t * item;

        item = jval_v(node->val); 
        
        priority = item->priority;
        return priority;
}


void vprq_del_node(vprq_list_t node) {
        dll_delete_node(node);
}

void vprq_add_priority(vprq_list_t list, int val, double priority_add) {

        vprq_list_t node;
        double priority;

        // Find the node with value val
        node = vprq_find_node(list, val);


        // Get old priority && delete node (if available)
        if (node != NULL) {
                priority = vprq_get_priority(node);
                vprq_del_node(node);
        } else {
                priority = 0;
        }

        priority += priority_add;

        // Insert new node
        vprq_enqueue(list, val, priority);
}


// delete the item with min value and delete it from queue
int vprq_extract_min(vprq_list_t list) {
    double min_priority;
    double min_priority_set = 0; // determin min value is initialized or not
    vprq_list_t min_node;


    vprq_list_t node;
    double node_priority;

    Jval node_v;
    vprq_item_t * node_v_ptr;


    // Scan the queue to find the node with min. priority
    dll_traverse(node, list) {
        node_v = node->val;
        node_v_ptr = jval_v(node_v);

        if (!min_priority_set) {
            min_priority = node_v_ptr->val;
            min_node = node;
            min_priority_set = 1;
        } else {
            node_priority = node_v_ptr->val;

            if (node_priority < min_priority) {
                min_priority = node_priority;
                min_node = node;
            }
        }
    }

    if (!min_priority_set) {
        return -1;
    }

    // Delete min node from list
    node_v = min_node->val;
    node_v_ptr = jval_v(node_v);
    free(node_v_ptr);
    dll_delete_node(min_node);

    return min_priority;
}  


int vprq_size(vprq_list_t list) {
    int size;
    Dllist ptr;

    size = 0;
    dll_traverse(ptr, list) {
        size++;
    }

    return size;
}
