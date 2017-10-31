#include "main.h"

int main()
{
    BTA* abc = btcrt("data.dat",1,0);
    int ls;

    do {
      printf("\n--------------menu-----------\n");
      printf("1.read file\n2.add more element\n3.search by name\n4.search by ip\n5.print all\n0.exit\n\nyou choose: ");
      scanf("%d", &ls); scanf("%*c");
      
      switch(ls) {

      case 1: readFile(abc); print(abc); break;
      case 2: add(abc); break;
      case 3: searchByName(abc); break;
      case 4: searchByNumber(abc); break;
      case 5: print(abc); break;
      case 0: break;
      default: printf("invalid value! enter again please!\n");
      }
    }while(ls!=0);
    btcls(abc);
}
