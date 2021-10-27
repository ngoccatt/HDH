#include <stdio.h>
#include "factorial.h"
#include <stdlib.h>

int to_int(char c) {
	return (c - '0');
}
char to_char(int i) {
	return (i + '0');
}
void multiply(char res[], int* resSize, int num) {
	int carry = 0;
	for(int i = 0; i < *resSize; i++) {
		int temp = to_int(res[i]) * num + carry;
		res[i] = to_char(temp % 10);
		carry = temp/10;
	}
	while(carry > 0) {
		res[*resSize] = to_char(carry % 10);
		(*resSize)++;
		carry /= 10;
	}
}
char * factorial(const int aNumber) 
{
	char * res = (char*)malloc(1001 * sizeof(char));
	res[0] = '1';
	int resSize = 1;
	for(int i = 2; i <= aNumber; i++) {
		multiply(res, &resSize, i);
	}
	res[resSize] = '\0';
	for (int i = 0; i < resSize/2; i++) {
		char temp = res[i];
		res[i] = res[resSize - 1 -i];
		res[resSize - 1 - i] = temp;
	}
	return res;
}
