#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "ex1.h"

void * aligned_malloc(unsigned int size, unsigned int align){
    void *p1, *p2;
    /* We need to use malloc provided by C. First we need to allocate memory
    of size bytes + alignment + sizeof(size_t) . We need 'bytes' because
    user requested it. We need to add 'alignment' because malloc can give us
    any address and we need to find multiple of 'alignment', so at maximum multiple
    of alignment will be 'alignment' bytes away from any location. We need
    'sizeof(size_t)' for implementing 'aligned_free', since we are returning modified
    memory pointer, not given by malloc ,to the user, we must free the memory
    allocated by malloc not anything else. So I am storing address given by malloc just above
    pointer returning to user. Thats why I need extra space to store that address.
    Then I am checking for error returned by malloc, if it returns NULL then
    aligned_malloc will fail and return NULL.
    */
    p1 = (void*)malloc(size + align + sizeof(void*));
    if (p1 == NULL) return NULL;
    size_t addr = (size_t)p1 + sizeof(void*);       //make sure that we always have 8byte for saving the address of p1.
    size_t step = addr % align;
    //if step == 0, then our p2 address will use extra align byte, not addr
    //this is not wrong, since we need to save the address allocated by malloc 
    //from p1 previous to the pointer p2 which we return to user
    p2 = (void*)(addr + (align - step));
    //this p2 pointer is returned to user.
    //cast pointer 2 from void to size_t to easy changing its value!
    //size_t * pointer size is equal to void *, so we can cast it, and decrease
    //the pointer by 1. then we dereference it, to assign address p1 inside it.
    //We then have address of p1 right before p2 pointer!
    *((size_t *)p2 - 1) = (size_t)p1;
    return p2;
}

//we does not free the pointer passed in here, but the pointer
//right before it (the pointer created by malloc).
//example
//ptr = 0x80
//ptr - 1 = 0x7f
//(size_t *)ptr - 1 = 0x78
//*((size_t *)ptr - 1) = 0x60       //get the value contain in address 0x78
//(void *)0x60 -> cast to pointer. 0x60 is the address create by malloc. we use this to do 
//the deallocating.
void * aligned_free(void * ptr) {
    //void* p_malloc = (void *)(*((size_t *)ptr - 1));
    void* p_malloc = (void *)(*((size_t*)ptr - 1));
    free(p_malloc);
}

