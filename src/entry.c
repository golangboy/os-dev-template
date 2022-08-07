#include "console.h"
void read_hd0(char *buf);
void read_hd1(char *buf);
int main()
{
    console_clear();
    console_write("HelloOS");
    while (1)
        ;
    return 0;
}
