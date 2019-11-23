/**********************************************************************************************************************
* Copyright (c) Shenyang Institute of Automation, Chinese Academy of Sciences. All rights reserved.
* FileName: robot_abstract.h
* Contact:  
* Version:  V0.1
*
* LICENSING TERMS:
*
* History:
* <author>      <time>      <version>      <desc>
*
* Description:
***********************************************************************************************************************/

#include "data.h"

void data_print(unsigned char* buffer, int len)
{
    for(int i=0;i<len;i++)
    {
        printf("%02x ",*(buffer+i));
    }
    printf("\n");
}
