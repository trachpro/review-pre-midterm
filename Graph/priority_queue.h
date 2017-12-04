#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "dllist.h"

typedef  Dllist vprq_list_t;

typedef struct vprq_item {
   int val;
   double priority;
} vprq_item_t;


// Prototypes 
vprq_list_t vprq_create();
void vprq_enqueue(vprq_list_t  list, int val, double priority);
int vprq_extract_min(vprq_list_t list);
int vprq_size(vprq_list_t list);

void vprq_del_node(vprq_list_t node);
void vprq_add_priority(vprq_list_t list, int val, double priority_add);
double vprq_get_priority(vprq_list_t node);

#endif
