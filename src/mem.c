#include "mem.h"
struct Mem_Free_Info
{
    int start_addr;
    int size;
};
struct Mem_Mg
{
    struct Mem_Free_Info freemem[MAX_MEM_SIZE], allocmem[MAX_MEM_SIZE];
};
struct Mem_Mg mem_mg;
void init_memmg(int addr, int size)
{
    for (int i = 0; i < MAX_MEM_SIZE; i++)
    {
        mem_mg.freemem[i].start_addr = 0;
        mem_mg.freemem[i].size = 0;
        mem_mg.allocmem[i].start_addr = 0;
        mem_mg.allocmem[i].size = 0;
    }
    mem_mg.freemem[0].start_addr = addr;
    mem_mg.freemem[0].size = size;
}
void *alloc(int size)
{
    if (0 == size)
    {
        return 0;
    }
    for (int i = 0; i < MAX_MEM_SIZE; i++)
    {
        if (mem_mg.freemem[i].size >= size)
        {
            int addr = mem_mg.freemem[i].start_addr;
            mem_mg.freemem[i].start_addr += size;
            mem_mg.freemem[i].size -= size;
            for (int j = 0; j < MAX_MEM_SIZE; j++)
            {
                if (mem_mg.allocmem[j].size == 0)
                {
                    mem_mg.allocmem[j].start_addr = addr;
                    mem_mg.allocmem[j].size = size;
                    break;
                }
            }
            return (void *)addr;
        }
    }
    return 0;
}
int free(void *ptr)
{
    int addr = (int)ptr;
    int size = 0;
    for (int i = 0; i < MAX_MEM_SIZE; i++)
    {
        if (mem_mg.allocmem[i].start_addr == addr)
        {
            size = mem_mg.allocmem[i].size;
            mem_mg.allocmem[i].start_addr = 0;
            mem_mg.allocmem[i].size = 0;
            break;
        }
    }
    for (int i = 0; i < MAX_MEM_SIZE; i++)
    {
        if (mem_mg.freemem[i].start_addr == addr + size)
        {
            mem_mg.freemem[i].start_addr -= size;
            mem_mg.freemem[i].size += size;
            return 1;
        }
    }
    return 0;
}
int get_freemem()
{
    int size = 0;
    for (int i = 0; i < MAX_MEM_SIZE; i++)
    {
        size += mem_mg.freemem[i].size;
    }
    return size;
}
int get_allocmem()
{
    int size = 0;
    for (int i = 0; i < MAX_MEM_SIZE; i++)
    {
        size += mem_mg.allocmem[i].size;
    }
    return size;
}