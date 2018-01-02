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

void findRelation(Graph g)
{
    int n = 0;
    Graph container = createGraph();
    JRB visited = make_jrb();
    printf("\n");

    void fRUtil(int key, Graph h, int i)
    {
        jrb_insert_int(visited, key, new_jval_i(n));
        addEdge(h, new_jval_i(n), new_jval_i(i), new_jval_i(key), 1);

        JRB out = make_jrb();
        int nOut = outDegree(g, new_jval_i(key), &out, 1);

        if(nOut != 0)
        {
            JRB temp = NULL;
            jrb_traverse(temp, out)
            {
                if(jrb_find_int(visited, jval_i(temp->val)) == NULL)
                {
                    fRUtil(jval_i(temp->val), h, i+1);
                }
            }
        }

        jrb_free_tree(out);
    }


    JRB vtex = NULL;
    jrb_traverse(vtex, g.vertices)
    {
        if(jrb_find_int(visited, jval_i(vtex->val)) == NULL)
        {
            n += 1;
            fRUtil(jval_i(vtex->val), container, 1);
        }
    }


    JRB tmp = NULL;
    jrb_traverse(tmp, container.edges)
    {
        JRB tmp2 = NULL;
        JRB branch = jval_v(tmp->val);

        printf("%d - length %d : ", jval_i(tmp->key), jval_i(jrb_last(branch)->key));

        jrb_traverse(tmp2, branch)
        {
            printf("%d, ", jval_i(tmp2->val));
        }

        printf("\n");
    }

    jrb_free_tree(visited);
    dropGraph(container);
}

int main() {

    JRB tree = make_jrb();

    jrb_insert_int(tree,1,new_jval_i(1));

    test(tree);
    JRB node = jrb_find_int(tree, 1);

    printf("%d\n", jval_i(node->val));

    return 0;
}