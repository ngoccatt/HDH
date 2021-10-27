#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

double compute_pi(int nPoint) {
    srand(time(0));
    int insidePoint = 0;
    for(int i = 0; i < nPoint; i++) {
        double x = (double)rand()/RAND_MAX; //create x from 0 -> 1
        double y = (double)rand()/RAND_MAX; //create y from 0 -> 1
        if (x*x + y*y <= 1) {
            insidePoint++;
        }
    }
    printf("number of inside point: %d\n", insidePoint);
    double pi = (double)insidePoint/(double)nPoint * 4;
    return pi;
}

int main(int argc, char** argv) {   //argv 2* lan!
    //argc la so luong string duoc dua vao command line, tinh ca goi ham
    //./file a1 a2 a3
    // argc = 4, argv[0] = ./file , argv[1] = a1, argv[2] = a2, argv[3] = a3
    if (argc != 2) {
        printf("Invalid call\n");
        return -1;
    }
    char nPoint[100];
    strcpy(nPoint, argv[1]);
    printf("%f\n", compute_pi(atoi(nPoint)));
    return 0;
}