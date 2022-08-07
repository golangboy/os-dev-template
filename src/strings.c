#include "strings.h"
int strlen(const char *str)
{
    if (0 == str)
        return 0;
    int i = 0;
    while (str[i] != '\0')
        i++;
    return i;
}
void memset(void *dst, int c, uint32_t size)
{
    uint8_t *dst_ = (uint8_t *)dst;
    for (uint32_t i = 0; i < size; i++)
        dst_[i] = c;
}