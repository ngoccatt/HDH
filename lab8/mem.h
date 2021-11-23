#ifndef _MEM_H
#define _MEM_H

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

pthread_mutex_t lock;

int mem_init(unsigned int size);

void mem_finish();

void * mem_alloc(unsigned int size);

void mem_free(void * pointer);

#endif // _MEM_H
