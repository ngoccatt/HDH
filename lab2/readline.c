#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "readline.h"
#include <string.h>

int read_line(char* str)
{
	char buffer[51];
	// char ch = getchar();
	// if (ch != '\n') {
	// 	ungetc(ch, stdin);
	// } else return -1;
	fgets(buffer, 51, stdin);
	int length = strlen(buffer);
	strcpy(str, buffer);
	for(int i = 0; i < length - 1; i++) 
	{
		if (!isdigit(buffer[i])) return 0;
	}	
	return 1;
}
