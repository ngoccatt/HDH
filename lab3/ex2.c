#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>       //needed for wait;

//IN ORDER TO CHECK THE CORRECTNESS OF THIS CODE
//UNCOMMENT EVERY sleep(10) (10 second, perhaps?), 
//run it, and use pstree -p parentID
//also, uncomment the printf function to print out parentID too :v

//sleep(10) is put inside every deepest child, to prevent it from
//terminated, and we can look at the full tree.

int main() {
    printf("hey, I'm parent process, my pid is %d\n", getpid());
    pid_t child1 = fork();
    if (child1 == 0){ //first child, create 2 more child
        pid_t child4 = fork();
        if (child4 > 0) {   //inside parent (child1 process)
            pid_t child5 = fork();
            if (child5 > 0) {
                int pid, status;
                while((pid = wait(&status)) > 0) {
                    //printf("Process %d terminated\n", pid);
                }
            } else { //child 5 sleep
                sleep(10);
            }
        } else {    //child 4 sleep
            sleep(10);
        }
    } else {    //inside parent
        pid_t child2 = fork();
        if (child2 == 0) {  //second child, create a child and a grandchild
            pid_t child6 = fork();
            if (child6 == 0) {      //inside children process of secondchild
                pid_t child7 = fork();
                if (child7 > 0) {
                    int pid, status;
                    while((pid = wait(&status)) > 0) {
                        //printf("Process %d terminated\n", pid);
                    }
                } else {//child 7 sleep
                    sleep(10);
                }
            } else {                //parent
                int pid, status;
                while((pid = wait(&status)) > 0) {
                    //printf("Process %d terminated\n", pid);
                }
            }
        } else {    //inside parent
            pid_t child3 = fork();
            if (child3 == 0) {  //third child, do nothing
                //do nothing
                sleep(10);  //child 3 sleep
            } else {
                int pid, status;
                while((pid = wait(&status)) > 0) {
                    //printf("Process %d terminated\n", pid);
                }
                
            }
        }
    }
    return 0;
}