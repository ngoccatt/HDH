#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv) {
    printf("Process_ID: %d\n", getpid());
    printf("Parent process ID: %d\n", getppid());
    printf("My group: %d\n", getpgrp());
}