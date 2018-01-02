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
  printf("\n1.Doc file");
  printf("\n2.In ra tong nut va tong cung");
  printf("\n3.Tim nut lien thong");
  printf("\n4.cac nut lien thong lon nhat");
  printf("\n5.cac nut dao");
  printf("\n6.Duong di ngan nhat");
  printf("\n7.So cach di");
  printf("\n0.exit");
  printf("\nyou choose: ");
}

int xy = 0;

int check(Graph graph,int point) {

    JRB node;
    jrb_traverse(node, graph.edges) {

        if(point == jval_i(node->key)) return point;
    }
    
    printf("diem khong ton tai hoac khong phai la cua!\n");
    return 0;
}

int getPoint(Graph graph) {

  int n;
  printf("nhap diem: ");
  scanf("%d", &n);
  n+=11;

  int out[100];

  return check(graph,n);
}

void mecung(Graph graph) {

    int ls;
    int tn, tc, point;
    int diem1, diem2;
    int out[100];
    do {
      menu();
      scanf("%d", &ls);

      switch(ls) {

      case 1: readMeCung(graph); break;

      case 2: tc = tongCung(graph); tn = tongNut(graph);
	printf("tong nut la: %d\ntong cung la: %d\n", tn, tc/2);
	break;

      case 3: point = getPoint(graph);
	congVietNgayTruoc(graph, point);
	break;

      case 4: listLienThong(graph); break;

      case 5: listDao(graph); break;

      case 6: {
          diem1 = getPoint(graph);
          if(!diem1) break;
          
          diem2 = getPoint(graph);
          if(!diem2) break;
          convert(graph, diem1, diem2); break;
      }

      case 7:
          diem1 = getPoint(graph);
          if (!diem1)
              break;

          diem2 = getPoint(graph);
          if (!diem2)
              break;
	        initU(out, 100);
		soCachDi(graph, diem1, diem2, out);
          printf("so cach di: %d\n", xy);
          break;

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
