#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/bt/inc/btree.h"
#include "../lib/libfdr/jrb.h"

int readFile(BTA *root);
void writeFile(char *name, char* number);
void insert(BTA *root);
void searchByName(BTA *root);
void searchByNumber(BTA *root);
void editPhoneByNumber(BTA *root);
void del(BTA *root);
void print(BTA *root);
void add(BTA *root);
