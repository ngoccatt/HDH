#include <stdio.h>
#include <pthread.h>
void * hello(void * tid) {
    printf("Hello from thead %ld\n", (long int)tid);
    return NULL;
}

int main() {
    pthread_t tid[10];
    long int i;
    for(i = 0; i < 10; i++) {
        pthread_create(&tid[i], NULL, hello, (void*)i);
        //this pthread_join just block the caller until the thread
        //complete. specify the thread (tid[i]) so that the caller
        //will wait for that tid till done.
        pthread_join(tid[i], NULL);
    }
    pthread_exit(NULL);
}