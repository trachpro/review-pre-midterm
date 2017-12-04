#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "btree.h"
#include "jrb.h"
#include "dllist.h"
#include "v_io.h"
#include "v_string.h"
#include "priority_queue.h"
#include "huffman_code.h"
#include "main.h"



int main() {
        char s[] = "AABBBCCDDD";
        
        HuffmanTree hmt = makeHuffman (s, strlen(s));

        return 0;
}
