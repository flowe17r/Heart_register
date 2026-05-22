#ifndef __APP_COMMUNICATION_H
#define __APP_COMMUNICATION_H

#include "Driver_UASRT1.h"
#include "string.h"
#include "Common_Debug.h"
#include <stdlib.h>
void  App_Communication_Start(void);

void App_Communication_CommandProcess(uint16_t *rate,uint16_t *duration);

void APP_Communication_SendHeartData(uint16_t heratData);

#endif 


