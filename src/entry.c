#include "console.h"
void read_hd0(char *buf);
void read_hd1(char *buf);
int main()
{
    console_clear();
    console_printf("Hello, kernel World!\n");
    load_idt();
    init_8259();
    init_timer(100);
    init_task();
    asm volatile("sti");
    while (1)
    {
        asm volatile("hlt");
    };
    return 0;
}
