#ifndef _v_io_
#define _v_io_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <ctype.h>

// clear screen
#define clear() printf("\033[H\033[J")

#define RED 31
#define GREEN 32
#define ORANGE 33
#define BLUE 34
#define MAGENTA 35
#define CYAN 36
#define YELLOW 38
#define NORMAL 0

// print a string with a specific color
void printColor(const char * str, int color);

// flush standard input (keyboard)
void cleanStdin(void);

// Remove '\n' character in the end of string s
void removeLastEnter(char *s);

// Read a line
char* readLn(FILE * fin, char *s, int max_len);

// Getch a character from keyboard without printing to the screen
int getch();

// goto a specific point on the screen
void gotoxy(int x,int y);


#endif