#include "console.h"
int main()
{
    console_clear();
    console_write("HelloOS");
    while (1)
        ;
    return 0;
}
