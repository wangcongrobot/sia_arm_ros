#include "data.h"

void data_print(unsigned char* buffer, int len)
{
    for(int i=0;i<len;i++)
    {
        printf("%02x ",*(buffer+i));
    }
    printf("\n");
}
