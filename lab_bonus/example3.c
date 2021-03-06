#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define NUM_THREADS     4  
#define NUM_LOOPS    10000000

void * user_def_func(void * threadID) {
    long TID;
    TID = (long) threadID;
    int i;
    double result = 0.0;
    printf("Thread %ld starting...\n", TID);
    for(int i = 0; i < NUM_LOOPS; i++) {
        result = result + sin(i) + tan(i);
    }
    printf("Thread %ld done. Result = %e\n", TID, result);
    pthread_exit((void *)threadID);
}

long taskids[NUM_THREADS];

int main(int argc, char* argv) {
    pthread_t threads[NUM_THREADS];
    pthread_attr_t attr; //attribute of threads
    int creation_flag, join_flag;
    long i;
    void *status;   //status of threads

    // Initialisze and set thread detached attribute
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    for(i = 0; i < NUM_THREADS; i++) {
        printf("In main: creating thread %ld\n", i);
        creation_flag = pthread_create(&threads[i], &attr, user_def_func, (void*)i);
        if (creation_flag) {
            printf("ERROR: return code from pthread_create(0 is %d\n",  creation_flag);
            exit(-1);
        }
    }

    pthread_attr_destroy(&attr);
    for(i = 0; i < NUM_THREADS; i++) {
        join_flag = pthread_join(threads[i], &status);
        if (join_flag) {
            printf("ERROR: return code from pthread_join is %d\n", join_flag);
            exit(-1);
        }
        printf("Main: completed join with thread %ld having a status of %ld\n", i, (long)status);
    }

    printf("Main: program completed. Exiting.\n");
    

    //free thread
    pthread_exit(NULL);
    return 0;
}