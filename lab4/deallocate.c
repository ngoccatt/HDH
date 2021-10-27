#include<stdio.h>
#include<stdlib.h>
#define MAXROW 3
#define MAXCOL 4

int main()
{
    int **p, i, j;
    p = (int **) malloc(MAXROW * sizeof(int*));
    free(p);
    return 0;
}