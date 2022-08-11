#ifndef MEM_H
#define MEM_H
#define MAX_MEM_SIZE 10
void init_memmg(int addr, int size);
void *alloc(int size);
int free(void *ptr);
int get_freemem();
int get_allocmem();
#endif