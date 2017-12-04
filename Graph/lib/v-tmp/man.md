*** Dllist
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