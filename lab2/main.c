#include <stdio.h>
#include <stdlib.h>
#include "factorial.h"
#include "readline.h"
#include <string.h>
int main() 

{
	//factorial(11);
	printf("\nEnter a string\n");
	char str[51];
	int res;
	char ch = getchar();
	while(ch != EOF) {		//EOF la ctrl + c
		ungetc(ch, stdin);
		res = read_line(str);
		if (res == 1) {
			printf("%s\n", factorial(atoi(str)));
		}
		//printf("hey, look at my string %s, it return %d\n", str, res);
		ch = getchar();
	}
	
	return 0;
}
