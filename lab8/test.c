#include <stdio.h>
#include <stdlib.h>

int main() {
    void * test = (void *)malloc(1024 * sizeof (char));
    printf("%ld\n", sizeof(test[0]));
    char* pointer = test + 3;
    printf("%d, %p -> %p\n",(test + 3) > (test + 2), pointer, (test + 2));
    int * tt = (int *)malloc(2 * sizeof(int));
    printf("%ld\n", sizeof(tt[0]));
    free(test);
    free(tt);
    return 0;
}