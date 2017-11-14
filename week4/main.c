#include "main.h"
int input;

int readFile(BTA *root) {
    FILE *f = fopen("dns.txt", "r");
    if(f == NULL) return 0;

    char name[30], number[20];

    char c;
    fscanf(f,"%c",&c);fscanf(f,"%*c");
    int n;
    
    if(c>='a' && c<='w') {

      printf("format of file is wrong! fail to read file!\n");
      return 0;
    }

    n = (int)c - 48;

    
    input = n;
   
    for(int i = 0; i< n; i++) {

      fscanf(f,"%[^\n]", name); fscanf(f,"%*c");
      fscanf(f,"%[^\n]", number); fscanf(f,"%*c");

      int s = btins(root, number, name, 30* sizeof(char));
      
      if(s != 0) {

	printf("add fail: %s: %s\n", name,number);
	return 0;
      }
    }
    /* while(!feof(f)) { */
    /*     fscanf(f,"%[^:]", name); fscanf(f,"%*c"); */
    /*     fscanf(f,"%[^\n]", number); fscanf(f,"%*c"); */
        
    /*     printf("%s-%s-%d\n",name, number, btins(root, number, name, 30* sizeof(char))); */
    /* } */

    fclose(f);

    return 1;
}

void writeFile(char *name, char* number) {
    FILE *f = fopen("dns.txt","a");

    if(f == 0) {
        printf("cannot read file!\n");
        return;
    };
    
    fprintf(f,"%s\n%s\n",name,number);
    
    fclose(f);

    FILE *f2 = fopen("dns.txt","r+");
    
    fprintf(f2,"%d",++input);
    
    fclose(f2);
}

void insert(BTA *root) {
    char name[30], number[20];

    printf("input name: "); scanf("%[^\n]",name); scanf("%*c");
    printf("input number: "); scanf("%[^\n]",number); scanf("%*c");

    int a = btins(root, number, name, 30* sizeof(char));

    if(a) printf("insert fail!\n");

    else {
        writeFile(name, number);
        printf("insert ok!\n");
    }
}

void searchByName(BTA *root) {
    char name[30],name1[30];
    char number[15];
    int i, rsize, flag = 0;
    printf("\n\n--------search by domain-----\n");
    printf("enter the domain: ");
    scanf("%[^\n]",name1); scanf("%*c");
    
    btpos(root,ZSTART);
    printf("\n result: \n");
    while(bnxtky(root,number,&i) == 0) {
        btsel(root, number, name, 30, &rsize);
        if(!strcmp(name,name1)) {
            printf("%-30s%-15s\n",name,number);
            flag = 1;
        }
    }

    if(!flag) printf("no number match!\n");
}

void searchByNumber(BTA *root) {
    char name[30], number[15];
    int rsize;
    printf("\n\n--------search by ip-----\n");
    printf("enter the ip: ");
    scanf("%[^\n]",number); scanf("%*c");
    printf("\n result: \n");
    if(btsel(root, number,name,30, &rsize) == 0) {
        // printf("rsiez = %d",rsize);
        printf("%-30s%-15s\n", name, number);
    } else {
        printf("\nno name match!\n");
    }
}

void editPhoneByNumber(BTA *root) {
    char name[30], number[20];
    int rsize;

    printf("enter the ip: ");
    scanf("%[^\n]",number); scanf("%*c");

    if(btsel(root, number,name,30, &rsize) == 0) {
        // printf("rsiez = %d",rsize);
        printf("edit the name: ");
        scanf("%[^\n]",name); scanf("%*c");
        btupd(root,number,name,30);
    } else {
        printf("\nno name match!\n");
    }
}

void del(BTA *root) {
    char number[20];
    printf("enter the number: ");
    scanf("%[^\n]",number); scanf("%*c");

    if(btdel(root,number) == 0) {
        printf("delete ok!\n");
    } else {
        printf("no phone match!\n");
    }
}

void print(BTA *root)
{
    BTint i;
    char number[20];
    char name[30];
    int rsize;
    btpos(root, ZSTART);

    printf("\n---------the list---------\n");
    while(bnxtky(root, number, &i) == 0) {
        btsel(root, number, name, 30, &rsize);
        printf("%-30s%-15s\n", name, number);
    }
}

void add(BTA *root) {

  char name[30], number[20], name1[30], number1[20];
  int s, rsize,i;
  printf("enter the domain: ");
  scanf("%[^\n]", name); scanf("%*c");

  btpos(root,ZSTART);
  while(bnxtky(root,number1,&i) == 0) {
    
    btsel(root, number1, name1, 30, &rsize);
    if(!strcmp(name,name1) || !strcmp(number,number1)) {
      printf("\n\nfail! exist domain!\n\n");
      s = 1;
      return;
    }
  }

  printf("enter the ip: ");
  scanf("%[^\n]", number); scanf("%*c");
  
  s = btins(root, number, name, 30* sizeof(char));
  
  if(!s) {

    writeFile(name, number);
    printf("add successfull!\n\n");
  } else {

    printf("\n\nfail! exist ip!\n\n");
  }
}
