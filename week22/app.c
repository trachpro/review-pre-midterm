#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../lib/libfdr/jrb.h"
#include "../lib/libfdr/dllist.h"

void test(JRB tree) {
    JRB str = tree;
    JRB node = jrb_find_int(str, 1);

    node->val = new_jval_i(2);
}

int main() {

    JRB tree = make_jrb();

    jrb_insert_int(tree,1,new_jval_i(1));

    test(tree);
    JRB node = jrb_find_int(tree, 1);

    printf("%d\n", jval_i(node->val));

    return 0;
}