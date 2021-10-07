#include<stdio.h>
#include<stdlib.h>
#define MAXROW 3
#define MAXCOL 4

int main()
{
    printf("size of int: %ld\n", sizeof(int));
    int (*p)[MAXCOL];       //(*p)[MAXCOL] khac *p[MAXCOL]. cai sau hinh nhu chi tao 1 con tro, may cai khac thi la int
    int (*i)[MAXCOL];
    int (*a);
    int *x = (int*)malloc(64);
    printf("sizeof(*x) = %ld\n", sizeof(*x));
    //so that incase of malloc, sizeof(*x) only give us the size of datatype, not the whole malloc size.
    printf("sizeof(a) = %ld\n", sizeof(a));
    printf("sizeof(p) give us size of p pointer, that mean 8: %ld\n", sizeof(i));
    printf("size of *p give us size of data type of that pointer, mean 4 * MAXCOL= %ld\n", sizeof(*i));
    p = (int (*) [MAXCOL])malloc(MAXROW *sizeof(*p));   //don't need to calculate anything here
    //first, p. sizeof(p) is the size of the pointer. so 8
    printf("size of %ld\n", sizeof(int (*)[MAXCOL]));
    //then, *p. sizeof(*p), no matter the size given by malloc, is always the data size. so sizeof(int) * MAXCOL = 16.
    printf("%ld, %ld\n", sizeof(p), sizeof(*p));
    free(p);
    return 0;
}