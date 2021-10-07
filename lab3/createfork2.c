#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv) {
    pid_t child_pid;

    child_pid = fork();
    
    if (child_pid == -1) {
        perror("fork"); /* print a system-defined error message*/
        exit(1);
    }
    if (child_pid == 0) {
        //fork() success, this is child process
        printf("Children PID = %d\n", getpid());
        printf("Hello, ");
        fflush(stdout);
        //khi chay ps -c {pid}, se thay STAT = Z -> defunct (1 zombie process)
        //terminated but not reaped by its parent
    }
    else {
        //fork success, this is parent process
        printf("Parent PID = %d\n", getpid());
        printf("World!\n");
        fflush(stdout);
        sleep(180);
    }
    
    return 0;
}