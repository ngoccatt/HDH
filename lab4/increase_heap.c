#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/resource.h>   //for rlimit
#include <stdlib.h>

int main() {
    printf("my pid is: %d\n", getpid());
    printf("before increasing\n");
    printf("current break is at %p\n", sbrk(0));
    //sleep(20);
    sbrk(80);
    printf("after increase\n");
    printf("We have a new break, it's %p\n", sbrk(0));
    //sleep(20);
    return 0;
}