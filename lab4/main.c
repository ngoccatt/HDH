#include "ex1.h"
#include <stdio.h>

int main() {
    char* test = aligned_malloc(10, 128);
    printf("Address of the memory allocated: %p\n", test);
    printf("%p mod 128 = %ld\n" ,test ,(size_t)(test) % 128);
    aligned_free(test);
}