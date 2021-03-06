#include "huffman_code.h"


HuffmanTree makeHuffman (char * buffer, int size) {
        int i;
	vprq_list_t char_list;


        // Make a queue for characters
        char_list = vprq_create();
        
	// Enqueue all the node
        for (i = 0; i < size; i++) {
                vprq_add_priority(char_list,  buffer[i], 1); 
        }

        /* int value; */
        /* vprq_item_t * item; */
        /* Dllist node; */
        /* dll_traverse(node, char_list) { */
        /*         item = jval_v(node->val); */
        /*         value = item->val; */
        /*         printf("%c --> ", value); */
        /*         printf("%lf\n", vprq_get_priority(node)); */
        /* } */

}
