#include "main.h"

void nhap2Id(int *id1, int *id2) {
    printf("nhap id cua 2 san pham: \nid sp1 = ");
    scanf("%d", id1);
    printf("id sp 2 = ");
    scanf("%d", id2);
}

void DeProduct(Graph graph) {

    int ls;
    int id1, id2;

    do{
        printf("\n-----menu------\n1.Doc va in san pham\n2.doc du lieu order history\n3.Do lien quan giua 2 san pham\n4.Cac san pham lien quan\n5.Moi lien he giua 2 san pham\n");
        printf("0.exit\nyou choose: "); scanf("%d",&ls);

        switch(ls) {

            case 1: readProduct(graph); break;
            case 2: readOrderHistory(graph); break;
            case 3: {
                
                nhap2Id(&id1, &id2);
                printf("do lien quan giua 2 san pham la: %d\n", getWeight(graph, id1,id2));
                
                break;
            }
            case 4: {
                printf("nhap id cua 2 san pham: \nid sp = ");
                scanf("%d", &id1);
                printf("cac sp lien quan: ");
                printReverse(graph, id1);
                break;
            }

            case 5: {
                nhap2Id(&id1, &id2);
                convert(graph,id1,id2);
                break;
            }
            case 0: break;
            default: printf("no match! please enter a valid value!\n");
        }
    } while(ls!=0);
}

void deDocTepDuLieu(Graph graph) {
    
    readTepDuLieu(graph);

    JRB node;

    int tc = tongCung(graph);
    int tn = tongNut(graph);

    printf("tong cung la: %d\ntong nut la: %d\n", tc, tn);

    // congVietNgayTruoc(graph, 6);
    // tatCaCacViecTruoc(graph, 5);

    // convert2(graph);
    // BFS(graph, 1, 4);
    int hasCircle = DAG(graph);

    printf("hasCircle: %d\n", hasCircle);
    int output[100];

    int n = topologicalSort(graph, output);
    printf("topo: ");
    for(int i = 0; i < n; i++) {

        printf("%-5d", output[i]);
    }

    printf("\n");
}

void mecung(Graph graph) {

    readMeCung(graph);

    JRB node;
    jrb_traverse(node, graph.edges) {

        JRB subTree = getJRBTree(node);
        JRB subNode;
        printf("%d: ", jval_i(node->key));
        jrb_traverse(subNode, subTree) {

            printf("%d ", jval_i(subNode->key));
        }
        printf("\n ");
    }

    listBB(graph);
}

void menu() {
  printf("\n-----MENU----");
  printf("\n1.");
  printf("\n2.");
  printf("\n3.");
  printf("\n4.");
  printf("\n5.");
  printf("\n6.");
  printf("\n7.");
  printf("\n0.exit");
  printf("\nyou choose: ");
}

int main() {

    
    Graph graph = make_graph();


    mecung(graph);
    //menu();
    
    dropJRB(graph.edges);
    dropJRB(graph.vertices);

    return 0;
}
