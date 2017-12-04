#ifndef HUFFMAN_CODE_H
#define HUFFMAN_CODE_H
#include "stdio.h"
#include "stdlib.h"
#include "dllist.h"

#include "priority_queue.h"

#include "graph.h"

typedef struct {
   vGraph graph;
   Dllist root;
} HuffmanTree;

#include "dllist.h"
#include "jrb.h"
#include "priority_queue.h"

HuffmanTree makeHuffman (char * buffer, int size);

#endif
