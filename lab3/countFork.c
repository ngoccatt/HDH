#include <stdio.h>
#include <unistd.h>

int count = 1;
 
int main() {
    fork();
    fork();
    fork();
    printf("hey yo come look at this %d\n", ++count);
    return 0;
}