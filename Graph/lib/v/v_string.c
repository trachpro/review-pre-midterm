#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "v_string.h"

char * strLower(char * dest, const char * s) {
        size_t i;
        for (i = 0; i < strlen(s); i++) {
                dest[i] = tolower(s[i]);
        }
        dest[strlen(s)] = '\0';
        return dest;
}

char * strUpper(char * dest, const char * s) {
        size_t i;
        for (i = 0; i < strlen(s); i++) {
                dest[i] = toupper(s[i]);
        }
        dest[strlen(s)] = '\0';
        return dest;
}


char * strTrim(char * dest, const char * s) {
        int l, r;
        l = 0;
        r = strlen(s)-1;


        // remove spaces at beginning
        while (l <= r) {
                if (isspace(s[l])) l++;
                else break;
        }

        // remove space at the end
        while (l <= r) {
                if (isspace(s[r])) r--;
                else break;
        }

        if (r < l) dest[0] = '\0';
        else  {
                strncpy(dest, s+l, r-l+1);
                dest[r-l+1] = '\0';
        }

        return dest;
}


// - remove space at last and at the begin
// - remove duplicated spaces
// - turn all space into #32 ASCII
void strSpaceStdlize(char *s) {
        int spaceBefore;
        int ptr1; // pointer 1: writing pointer;
        int ptr2; // reading pointer;

        spaceBefore = 1;
        ptr2 = 0; ptr1 = -1;
        while (ptr2 < strlen(s)) {
                if (isspace(s[ptr2])) {
                        if (!spaceBefore){
                                s[++ptr1] = ' ';
                                spaceBefore = 1;
                        } 
                } else {
                        s[++ptr1] = s[ptr2];
                        spaceBefore = 0;
                }
                ptr2++;
        }

        if (ptr1 == -1) {
                s[0] = '\0';
        }

        // remove last space
        if (isspace(s[ptr1])) {
                s[ptr1] = '\0';
        } else {
                s[ptr1+1] = '\0';
        }

}


// Split a string using space as delim
void strSplit(char* s, char ** arr, int * n) { // n is number of words
        char * tmp;
        char * word;

        tmp = (char *)malloc((strlen(s)+1) * sizeof(char));

        strcpy(tmp, s);
        strSpaceStdlize(tmp);

        *n = 0;
        word = strtok(tmp, " ");
        while (word != NULL) {
                strcpy(arr[*n], word);
                (*n)++;
                word = strtok(NULL, " ");
        }

        free(tmp);
}

// Join a string using optional delim
void strJoin(char *s, char ** arr, int begin, int end, const char * delim) {
        // empty string s;
        s[0] = '\0';

        int i;
        for (i = begin; i <= end; ++i){
                if (strlen(s) != 0) {
                        strcat(s, delim);
                }
                strcat(s, arr[i]);
        }
}


// return 0: the same; <0: name1 < name2; >0: name1 > name2
int nameCompare(char* fullname1, char* fullname2) {

        size_t nameStringSize;
        char * familyName1;
        char * surname1;
        char * name1;
        char * familyName2;
        char * surname2;
        char * name2;
        char ** a;
        int n, i;


        if (strlen(fullname1) > strlen(fullname2)) {
                nameStringSize = strlen(fullname1);    
        } else {
                nameStringSize = strlen(fullname2);
        }

        familyName1 = (char*)malloc(sizeof(char) * nameStringSize + 1);
        surname1 = (char*)malloc(sizeof(char) * nameStringSize + 1);
        name1  = (char*)malloc(sizeof(char) * nameStringSize + 1);

        familyName2 = (char*)malloc(sizeof(char) * nameStringSize + 1);
        surname2 = (char*)malloc(sizeof(char) * nameStringSize + 1);
        name2  = (char*)malloc(sizeof(char) * nameStringSize + 1);
        

        a = (char**)malloc(sizeof(char*) * MAX_WORDNUM_IN_NAME);
        for (i = 0; i < MAX_WORDNUM_IN_NAME; i++) {
             a[i] = (char*)malloc(sizeof(char) * nameStringSize + 1);
        }
        

        strSplit(fullname1, a, &n);
        if (n > 0) {
                strcpy(name1, a[n-1]);
        }
        if (n > 1) {
                strcpy(familyName1, a[0]);
        }
        if (n > 2) {
                strJoin(surname1, a, 1, n-2, " ");
        }

        strSplit(fullname2, a, &n);
        if (n > 0) {
                strcpy(name2, a[n-1]);
        }
        if (n > 1) {
                strcpy(familyName2, a[0]);
        }
        if (n > 2) {
                strJoin(surname2, a, 1, n-2, " ");
        }

        strLower(familyName1, familyName1); strLower(surname1, surname1); strLower(name1, name1); 
        strLower(familyName2, familyName2); strLower(surname2, surname2); strLower(name2, name2); 

        if (strcmp(name1, name2) != 0) {
                return strcmp(name1, name2);
        } else {
                if (strcmp(surname1, surname2) != 0) {
                        return strcmp(surname1, surname2);
                } else {
                        return strcmp(familyName1, familyName2);
                }
        }

        return 0;
}
