#include "mem.h"
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>


pthread_mutex_t lock;

void * mem_pool = NULL;

struct mem_region {
    size_t size;    //Size of memory region
    char * pointer; // Pointer to the first byte
    struct mem_region* next;   // Pointer to the next region in the list
    struct mem_region * prev; // Pointer to the previos region in the list.
};

struct mem_region * free_regions = NULL;
struct mem_region * used_regions = NULL;

static void * best_fit_allocator(unsigned int size);
static void * first_fit_allocator(unsigned int size);

struct mem_region * create_node(struct mem_region* prev, struct mem_region* next, size_t size, char* pointer) {
    struct mem_region * temp = (struct mem_region *)malloc(sizeof(struct mem_region));
    temp->size = size;
    temp->pointer = pointer;
    temp->prev = prev;
    temp->next = next;
    return temp;
}

struct mem_region * add_node(size_t size, char* pointer, struct mem_region * regions, int index) {
    struct mem_region * scan = regions;
    struct mem_region * temp = create_node(NULL, NULL, size, pointer);
    if (index == 0) {
        temp->next = regions;
        if (regions != NULL) {
            regions->prev = temp;
        }
        regions = temp;
    } else {
        int i = 0;
        for(i = 0; i < index - 1; i++) {        //chay toi "truoc" vi tri index, chu khong chay "den" vi tri index
            scan = scan->next;
        }
        if (i != index - 1) {
            temp->prev = scan;
            temp->next = scan->next;
            scan->next->prev = temp;
            scan->next = temp;
        } else {        // neu i == index - 1, insert phan tu vao cuoi
            temp->prev = scan;
            temp->next = scan->next;
            scan->next = temp;
        }
    }
    return regions;
}

struct mem_region * delete_node(struct mem_region * regions, int index) {
    struct mem_region * scan = regions;
    struct mem_region * temp = NULL;
    if (index == 0) {                   //first node:
        temp = regions;
        regions = regions->next;
        if (regions != NULL) {
            regions->prev = NULL;
        }
    } else {
        for(int i = 0; i < index; i++) {
            scan = scan->next;
            if (scan->next == NULL) break;
        }
        if (scan->next == NULL) {       //final node:
            temp = scan;
            scan->prev->next = NULL;
        } else {                        //middle node:
            scan->prev->next = scan->next;
            scan->next->prev = scan->prev;
            temp = scan;
        }
    }
    //gan pointer == NULL, boi vi minh sap delete 1 cai mem_region co chua char * pointer
    //nho~ cai pointer cung bi free() luon thi sao? (ma that ra la no khong bi free.) hay dieu nay chi xay ra doi voi
    //lap trinh huong doi tuong cua C++ ?.
    temp->pointer = NULL;
    free(temp);
    return regions;
}

int mem_init(unsigned int size) {
    // Initial lock for multi-thread allocators
    pthread_mutex_init(&lock, NULL);
    //allocate [size] bytes.
    mem_pool = (void *)malloc(size * sizeof (char));   
    free_regions = create_node(NULL, NULL, size, mem_pool);
    return (mem_pool != 0);
}

void mem_finish() {
    // Clean preallocated region
    free(mem_pool);
    // need to clear free_regions and used_regions too!
    while(free_regions != NULL) {
        free_regions = delete_node(free_regions, 0);
    }
    while(used_regions != NULL) {
        used_regions = delete_node(used_regions, 0);
    }
    pthread_mutex_destroy(&lock);
}

void * mem_alloc(unsigned int size) {
    pthread_mutex_lock(&lock);
    // Follow is FIRST FIT allocator used for demonstration only.
    // You need to implement your own BEST FIT allocator
    // TODO: Comment the next line
    //void * pointer = first_fit_allocator(size);
    //Comment out the previous line and uncomment the next line
    // to invoke best fit allocator
    // TODO: uncomment the next line
    void * pointer = best_fit_allocator(size);

    //FOR VERIFICATION ONLY. DO NOT REMOVE THESE LINES
    if (pointer != NULL) {
        printf("Alloc   [%4d bytes] %p-%p\n", size, pointer, (char*)pointer + size - 1);
    } else {
        printf("Alloc   [%4d bytes] NULL\n", size);
    }

    pthread_mutex_unlock(&lock);
    return pointer;
}

void mem_free(void * pointer) {
    // free memory
    pthread_mutex_lock(&lock);

    struct mem_region * scan = used_regions;
    int del_index = 0;
    while (scan->pointer != pointer) {
        scan = scan->next;
        del_index++;
    }
    if (scan->pointer != pointer) return;
    //da tim ra vi tri can phai free. gio thi minh can quet mang free_region
    //de tim vi tri phu hop de tra? lai vung memory vao free_region list theo thu tu 
    //tang dan cua gia tri pointer cua cac node. 
    //minh se co "tra? lai vung nho" cho free_region.
    struct mem_region * scan_1 = free_regions;
    int index = 0;
    //neu vong lap nay thanh cong, ta se di toi 1 node co gia tri pointer > gia tri pointer cua scan (node can insert lai vao free_regions)
    //hoac, scan_1 co the ra toi tan NULL. Dieu do nghia la scan->pointer lon hon han cac node trong free_regions, nen ta phai insert vao cuoi'
    while(scan->pointer > scan_1->pointer && scan_1 != NULL) {        
        scan_1 = scan_1->next;
        index++;
    }
    
    if (scan_1 == NULL) {       //neu scan_1 di xa toi muc == NULL, co nghia la minh se can insert vao cuoi mang free_regions
        free_regions = add_node(scan->size, scan->pointer, free_regions, index);  
    } else {
    
        struct mem_region * prev_node = scan_1->prev;       //prev_node co the == NULL neu scan_1 la node dau tien.
        struct mem_region * next_node = scan_1;
        //kiem tra xem temp co the ket hop voi prev_node khong
        //neu co, prev_node se tang size, pointer khong doi
        //neu ket hop duoc voi prev_node va ca next_node, nghia la scan nam ngay giua
        //prev va next, noi lien nhau. trong truong hop nay, ta keo
        // dai prev node : prev_node->size + scan->size + next->node va xoa next_node di.
        if ((prev_node != NULL) && (prev_node->pointer + prev_node->size == scan->pointer)) { //dinh lien voi prev_node
            prev_node->size += scan->size;
            if (scan->pointer + scan->size == next_node->pointer) { //dinh lien voi ca next_node
                prev_node->size += next_node->size;
                free_regions = delete_node(free_regions, index);
            }
        } else if ((next_node != NULL) && (next_node->pointer == (scan->pointer + scan->size))) {    //dinh lien voi next_node -> cap nhat next_node bang cach tang size va day pointer len tren
            next_node->pointer = scan->pointer;
            next_node->size += scan->size;
        } else { //cha dinh voi cai gi ca. Add no vao vi tri chinh giua prev_ va next_ node
            free_regions = add_node(scan->size, scan->pointer, free_regions, index);
        }
    }
    //xoa node ra khoi used_regions
    if (scan != NULL) {
        printf("\nDealloc [%4ld bytes] %p-%p\n\n", scan->size, scan->pointer, (char*)scan->pointer + scan->size - 1);
    } else {
        printf("\nDealloc [%4ld bytes] NULL\n\n", scan->size);
    }
    used_regions = delete_node(used_regions, del_index);
    pthread_mutex_unlock(&lock);
}

void *best_fit_allocator(unsigned int size) {
    //TODO: Implement your best fit allocator here
    int best_slot = 0;
    int i = 0;
    size_t min_size = 0x7ffffff;
    struct mem_region * scan = free_regions;
    while (scan != NULL) {
        if ((scan->size >= size) && (scan->size < min_size)) {
            best_slot = i;
            min_size = scan->size;
        }
        scan = scan->next;
        i++;
    }
    scan = free_regions;
    for (i = 0; i < best_slot; i++) {
        scan = scan->next;
    }
    //used_regions thi add dau cung duoc, nen add o dau cho nhanh
    used_regions = add_node(size, scan->pointer, used_regions, 0);
    //thay doi pointer va size cua scan thuoc free_regions hien tai
    scan->pointer = scan->pointer + size;
    scan->size = scan->size - size;
    
    return used_regions->pointer;    //return this shit
}

void * first_fit_allocator(unsigned int size) {
    //copy here
    return NULL;
}