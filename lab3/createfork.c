#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char ** argv) {
    switch(fork()) {
        case 0:
            printf("I am the child: pid=%d\n", getpid());
            break;
        default: 
            printf("I am the parent: pid=%d", getpid());
        break;
        case -1:
            perror("Fork failed"); 
        break;
    }
    return 0;
}