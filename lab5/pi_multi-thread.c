#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

#define NO_OF_THREAD 8

struct arg_thread {
    int inputPoint;
    int outputPoint;
    unsigned int seed;
};

//each thread need a different seed
//HAVE TO USE RAND_R(), BECASUE RAND() IS NOT THREAD SAFE. 
//ALSO IF YOU SEARCH RAND_R, IT'S MOSTLY USED IN MULTITHREADING.


void * countPointInside(void* arg) {
    
    struct arg_thread* arg_t = (struct arg_thread*) arg;
    int nPoint = arg_t->inputPoint;
    int insidePoint = 0;
    for(int i = 0; i < nPoint; i++) {
        double x = (double)rand_r(&arg_t->seed)/RAND_MAX; //create x from 0 -> 1
        double y = (double)rand_r(&arg_t->seed)/RAND_MAX; //create y from 0 -> 1
        if (x*x + y*y <= 1) {
            insidePoint++;
        }
    }
    arg_t->outputPoint = insidePoint;
    return NULL;
}



double compute_pi(int nPoint) {
    unsigned int seed = time(NULL);
    int insidePoint = 0;
    long int partOfPoint = nPoint/NO_OF_THREAD;
    struct arg_thread myarg[NO_OF_THREAD];
    pthread_t tid[NO_OF_THREAD];
    //create all the thread
    for(int i = 0; i < NO_OF_THREAD; i++) {
        //doi so thu 4 cua pthread_create phai duoc cast thanh (void *)
        myarg[i].inputPoint = partOfPoint;
        //each thread have different seed.
        myarg[i].seed = seed + i;
        pthread_create(&tid[i], NULL, countPointInside, (void*)&myarg[i]);
    }
    //and then join all of it
    for(int i = 0; i < NO_OF_THREAD; i++) {
        //khong quan tam toi attribute (doi so thu 2.)
        pthread_join(tid[i], NULL);
        //printf("output point from thread: %d\n", myarg[i].outputPoint);
        insidePoint += myarg[i].outputPoint;
    }
    printf("total of inside point: %d\n", insidePoint);
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