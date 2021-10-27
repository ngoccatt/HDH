#include <sys/types.h>
#include <sys/wait.h> //needed for wait.
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int value = 5;

int main() {
    pid_t pid;
    pid = fork();
    if (pid == 0) {
        value += 15;
        printf("PARENT: value = %d", value);
        return 0;
    } else if (pid > 0) {
        wait(NULL); //wait until child has complete it task
        printf("PARENT: value = %d", value);
        return 0;
    }
}