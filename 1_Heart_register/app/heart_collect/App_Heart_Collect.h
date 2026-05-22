#ifndef __APP_HEAT_COLLECT__H
#define __APP_HEAT_COLLECT__H

#include "Driver_ADC1.h"
#include "Driver_TIM7.h"
#include "Common_Debug.h"


void APP_HeartCollect_Start(uint16_t rate, uint16_t duration);
uint16_t APP_HeartCollect_ReadHeartDate(void);
#endif
