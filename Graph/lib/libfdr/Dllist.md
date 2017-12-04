Doubly Linked Lists

Doubly linked lists are like singly linked lists, except each node has two pointers -- one to the next node, and one to the previous node. This makes life nice in many ways:
You can traverse lists forward and backward.
You can insert anywhere in a list easily. This includes inserting before a node, after a node, at the front of the list, and at the end of the list.
You can delete nodes very easily.
The API for doubly linked lists is in dllist.h. It defines a doubly-linked list node:
typedef struct dllist {
  struct dllist *flink;
  struct dllist *blink;
  Jval val;
} *Dllist;
Here are the operations supported by dllist.o:

Dllist new_dllist(): Allocates and returns a new doubly linked list.
free_dllist(Dllist l): Destroys the list, calling free() on all allocated memory in the list. The list does not have to be empty.
dll_prepend(Dllist l, Jval val): Adds a new node at the beginning of the list. This node's value is val. Dll_prepend() has no return value.
dll_append(Dllist l, Jval val): Adds a new node at the end of the list. This node's value is val. Dll_append() has no return value.
dll_insert_b(Dllist n, Jval val): Adds a new node to the list right before the specified node. This node's value is val.
dll_insert_a(Dllist n, Jval val): Adds a new node to the list right after the specified node. This node's value is val.
Dllist dll_nil(Dllist l): Returns a pointer to the nil (sentinel) node for the list. You can think of nil as a node with no value, that begins and ends the list. Since l points to the sentinel node, dll_nil returns l. You don't need to call dll_nil() to access the sentinel node. You can just use l, although it makes your code more readable if you use dll_nil().
Dllist dll_first(Dllist l): Returns a pointer to the first node in the list. If the list is empty, this returns the sentinel. As with dll_nil(), you don't need to call dll_first(l) -- you can just use l->flink.
Dllist dll_last(Dllist l): Returns a pointer to the last node in the list. If the list is empty, this returns the sentinel. As with dll_nil(), you don't need to call dll_last(l) -- you can just use l->blink.
Dllist dll_next(Dllist n): Returns a pointer to the next node in the list after n. If n is the last node on the list, then dll_next(n) returns the sentinel. As with dll_first(), you don't need to call dll_next(n) -- you can just use n->flink.
Dllist dll_prev(Dllist n): Returns a pointer to the previous node in the list before n. If n is the first node on the list, then dll_prev(n) returns the sentinel. As with dll_last(), you don't need to call dll_prev(n) -- you can just use n->blink.
int dll_empty(Dllist l): Returns whether l is empty.
Jval dll_val(Dllist n): Returns node n's val field. Again, you don't need to use this, but sometimes it comes in handy.
int dll_delete_node(Dllist n): Deletes and frees node n.
Finally, there are two macros for traversing dllists forwards and backwards. ptr should be a Dllist and list should be a Dllist:
#define dll_traverse(ptr, list) \
  for (ptr = (list)->flink; ptr != (list); ptr = ptr->flink)
#define dll_rtraverse(ptr, list) \
  for (ptr = (list)->blink; ptr != (list); ptr = ptr->blink)
Implementation

The implementation of each dllists is as a circular doubly-linked list with a sentinel node. The code is in dllist.c.
The typedef for a dllist node is:

typedef struct dllist {
  struct dllist *flink;
  struct dllist *blink;
  Jval val;
} *Dllist;
Note that each node has two pointers -- a forward link (flink) to the next node on the list, and a backward link (blink) to the previous node on the list. A Dllist is a pointer to the sentinel node.
The list is circular in both directions -- the sentinel's flink points to the first node on the list, and its blink points to the last node on the list. The first node's blink points to the sentinel, as does the last node's flink.

Some ascii art: Here's an empty list l:

l -------------+--> |-----------|
               |    | flink ---------\
               |    | blink -------\ |
               |    | val = ?   |  | |
               |    |-----------|  | |
               |                   | |
               \-------------------+-/
And here's that list after calling dll_append(l, new_jval_i(3));: (or dll_prepend(l, new_jval_i(3)) for that matter).
l -------------+--> |-----------|  /-+->|-----------|
               |    | flink -------/ |  | flink ---------\
               |    | blink ---------/  | blink -------\ |
               |    | val = ?   |       | val.i = 3 |  | |
               |    |-----------|       |-----------|  | |
               |                                       | |
               \---------------------------------------+-/
Actually, it makes the drawing cleaner to have the back links go backwards:
l ----------------->|-----------|       |-----------|
               /--->| flink ----------->| flink ---------\
               |  /------ blink |<----------- blink |<-\ |
               |  | | val = ?   |       | val.i = 3 |  | |
               |  | |-----------|       |-----------|  | |
               |  |                                    | |
               |  \------------------------------------/ |
               |                                         |
               \-----------------------------------------/
Here's that list after calling dll_append(l, new_jval_i(5));:
l ---------->|-----------|       |-----------|       |-----------|
        /--->| flink ----------->| flink ----------->| flink ---------\
        |  /------ blink |<----------- blink |<----------- blink |<-\ |
        |  | | val = ?   |       | val.i = 3 |       | val.i = 5 |  | |
        |  | |-----------|       |-----------|       |-----------|  | |
        |  |                                                        | |
        |  \--------------------------------------------------------/ |
        |                                                             |
        \-------------------------------------------------------------/
I won't go over more examples with ascii art. You should be getting the hang of this by now.
Many of the procedure implementations are trivial procedures or macros:

 
Dllist new_dllist()
{
  Dllist d;

  d = (Dllist) malloc (sizeof(struct dllist));
  d->flink = d;
  d->blink = d;
  return d;
}

dll_empty(Dllist l)
{
  return (l->flink == l);
}


free_dllist(Dllist l)
{
  while (!dll_empty(l)) {
    dll_delete_node(dll_first(l));
  }
  free(l);
}


#define dll_first(d) ((d)->flink)
#define dll_next(d) ((d)->flink)
#define dll_last(d) ((d)->blink)
#define dll_prev(d) ((d)->blink)
#define dll_nil(d) (d)


The only subtle pieces of code are dll_insert_b() and dll_delete_node. With dll_insert_b(n, v) we malloc() a new node, set its value to v, and then link it into the list right before n. This means that we set the new node's flink field to n, and its blink field to n->blink. Then we set n->blink to the new node, and the old n->blink's flink field to the new node. Here's the code:
dll_insert_b(Dllist node, Jval v)       /* Inserts before a given node */
{
  Dllist new;

  new = (Dllist) malloc (sizeof(struct dllist));
  new->val = v;

  new->flink = node;
  new->blink = node->blink;
  new->flink->blink = new;
  new->blink->flink = new;
}
Once we have dll_insert_b() the other three list insertion routines are simply calls to dll_insert_b():
dll_insert_a(Dllist n, Jval val)        /* Inserts after a given node */
{
  dll_insert_b(n->flink, val);
} 

dll_append(Dllist l, Jval val)     /* Inserts at the end of the list */
{ 
  dll_insert_b(l, val);
}

dll_prepend(Dllist l, Jval val)    /* Inserts at the beginning of the list */
{ 
  dll_insert_b(l->flink, val);
} 
Deletion is pretty easy too. First you must remove the node n's from the list by setting n->flink->blink to n->blink and by setting n->blink->flink to n->flink. Then you free n:
dll_delete_node(Dllist node)            /* Deletes an arbitrary iterm */
{
  node->flink->blink = node->blink;
  node->blink->flink = node->flink;
  free(node);
}
