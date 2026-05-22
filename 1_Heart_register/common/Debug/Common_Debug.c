#include "Common_Debug.h"


void Common_Debug_Init(void)
{
    Driver_UASRT1_Init();
    Driver_USART1_Start();
}

