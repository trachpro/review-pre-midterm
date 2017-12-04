#ifndef _v_string_
#define _v_string_

#define MAX_WORDNUM_IN_NAME 100

// lowercase string s and save to string dest
char * strLower(char * dest, const char * s);

// uppercase string s and save to string dest
char * strUpper(char * dest, const char * s);

// remove all space character from string s
char * strTrim(char * dest, const char * s);


// Cắt xâu thành nhiều xâu nhỏ theo dấu cách
// Split a string using space as delim
void strSplit(char* s, char ** arr, int * n); // n is number of words


// Nối các xâu từ begin đến end trong mảng arr thành xâu s bằng kí tự delim
// Join a string using optional delim
void strJoin(char *s, char ** arr, int begin, int end, const char * delim);


// - remove space at last and at the begin
// - remove duplicated spaces
// - turn all space into #32 ASCII
void strSpaceStdlize(char *s);


// So sánh tên. Các tên được cắt ra thành 3 phần và loại bỏ các dấu cách thừa
// So sánh tên > tên đệm > họ
int nameCompare(char* fullname1, char* fullname2);


#endif
