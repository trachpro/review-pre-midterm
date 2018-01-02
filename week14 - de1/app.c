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

int getPoint() {

  int n;
  printf("nhap diem: ");
  scanf("%d", &n);
  n+=11;

  return n;
}

void mecung(Graph graph) {

    int ls;
    int tn, tc, point;

    do {
      menu();
      scanf("%d", &ls);

      switch(ls) {

      case 1: readMeCung(graph); break;

      case 2: tc = tongCung(graph); tn = tongNut(graph);
	printf("tong nut la: %d\ntong cung la: %d\n", tn, tc/2);
	break;

      case 3: point = getPoint();
	congVietNgayTruoc(graph, point);
	break;

      case 4: listLienThong(graph); break;

      case 5: listDao(graph); break;

      case 6: convert(graph, 11, 55); break;

      case 7: printf("so cach di: %d\n", DFS(graph, 42, 43));

      case 0: break;

      default: printf("invalid input! enter again please!\n");
      }
    }while(ls!=0);
}

int main() {

    
    Graph graph = make_graph();
    
    mecung(graph);
    
    dropJRB(graph.edges);
    dropJRB(graph.vertices);

    return 0;
}
