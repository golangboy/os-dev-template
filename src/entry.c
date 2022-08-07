#include "console.h"
void read_hd0(char *buf);
void read_hd1(char *buf);
int main()
{
    console_clear();
    console_printf("Hello, kernel World!\n");
    load_idt();
    while (1)
        ;
    return 0;
}
