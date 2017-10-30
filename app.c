#include "main.h"

int main()
{
    BTA* abc = btcrt("data.dat",1,0);

    readFile(abc);

    print(abc);
    btcls(abc);
}