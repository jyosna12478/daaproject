#include<stdio.h>
#define NO_OF_CHARS 256 

int naive(char *text, char *pat);

int horspool(char *text, char *pattern);
int* shiftTable(char* pattern);

int rabin_karp(char *txt, char *pat);
int rabinkarp(char pat[], char txt[], int q);

int kmp( char* X, char* Y, int m, int n);
int *pi_table(char *pattern, int psize);
