#include "console.h"
void read_hd0(char *buf);
void read_hd1(char *buf);
int total_mem = 0;
typedef struct MemBlock
{
    int baselow32;
    int basehigh32;
    int lenlow32;
    int lenhigh32;
    int type;
} MemBlock;
int main(int *mcrNumber, MemBlock *memChkBuf)
{
    console_clear();
    console_printf("Hello, kernel World!\n");
    console_printf("Loading IDT\n");
    load_idt();
    init_8259();
    init_timer(100);
    init_task();
    asm volatile("sti");
    read_memsize(mcrNumber, memChkBuf);
    console_printf("Physical memory size: %d\n", total_mem);
    while (1)
    {
    };
    return 0;
}

void read_memsize(int *mcrNumber, MemBlock *memChkBuf)
{
    for (int i = 0; i < *mcrNumber; i++)
    {
        long long sz = (memChkBuf[i].baselow32 << 32) + memChkBuf[i].basehigh32;
        total_mem += (sz);
        memChkBuf++;
    }
}
