#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
    char name[80];
    long number;
}PhoneEntry;

typedef struct {
    PhoneEntry *entries;
    int total;
    int size;
}PhoneBook;

#define INITIAL_SIZE 2
#define INCREMENT_SIZE 1

PhoneBook createPhoneBook();
void dropPhoneBook(PhoneBook* book);
void addPhoneNumber(char *name, long number, PhoneBook *book);
PhoneEntry *getPhoneNumber(char *name, PhoneBook *book);

PhoneBook createPhoneBook() {

    PhoneBook a;
    
    a.size = INITIAL_SIZE;

    a.entries = (PhoneEntry*)malloc(sizeof(PhoneEntry)* a.size);

    a.total = 0;

    return a;
}

void dropPhoneBook(PhoneBook *book) {
    free(book->entries);
}

PhoneEntry *getPhoneNumber(char *name, PhoneBook *book) {

    for(int i = 0; i < book->total; i++) {
        
        if(strcmp(book->entries[i].name, name) == 0) return &book->entries[i];
    }

    return NULL;
}

PhoneEntry makePhone(char *name, long number) {

    PhoneEntry a;
    
    strcpy(a.name, name);

    a.number = number;

    return a;
}

void addPhoneNumber(char *name, long number, PhoneBook *book) {
    
    PhoneEntry *p = getPhoneNumber(name, book);

    if(p) {
     
        p->number = number;
    } else {

        if(book->total == book->size) {
            
            book->size += INCREMENT_SIZE;
            book->entries = realloc(book->entries, sizeof(PhoneEntry) *book->size);
        }

        book->entries[book->total++] = makePhone(name, number);
    }
}

void print(PhoneBook book) {
    
    for(int i = 0; i < book.total; i++) {

        printf("%s: %ld\n", book.entries[i].name, book.entries[i].number);
    }

    printf("-------------------------------------\n");
}

void addType2(PhoneBook a) {
    a.entries[0] = makePhone("tu",123);
}

int main() {

    PhoneBook a = createPhoneBook();

    // addPhoneNumber("tuh",1234, &a);
    // addPhoneNumber("tu",88234, &a);
    // addPhoneNumber("tup",134, &a);
    // addPhoneNumber("tuph",134, &a);
    // addPhoneNumber("tufp",134, &a);

    addType2(a);

    printf("%s: %ld\n", a.entries[0].name, a.entries[0].number);

    // print(a);

    dropPhoneBook(&a);
    return 0;
}