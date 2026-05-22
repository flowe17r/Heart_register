#include "App_Heart_Collect.h"

static uint16_t g_rate;
static uint16_t g_duration;
void APP_HeartCollect_Start(uint16_t rate, uint16_t duration)
{
    // 0.存储采样率和采样时长
    g_rate = 1000 * 60 / rate;
    g_duration = duration * 1000;
    // 1.初始化adc1
    Driver_ADC1_Init();
    // 2.启动ADC1
    Driver_ADC1_Start();
    // 3.初始化定时器
    Driver_TIM7_Init();
    // 4.启动定时器
    Driver_ADC1_Start();
}

__IO uint8_t g_isToReadValue = 0 ;
void TIM7_UpInterrupMstCallBack(uint32_t msCount)
{
    if (msCount >= g_duration)
    {
        //关闭定时器
        Driver_TIM7_Stop();
        //关闭ADC
        Driver_ADc1_Stop();
    } 

    if ((msCount % g_rate) == 0)
    {
       //读取一次ADC的值 

       g_isToReadValue = 1;
    }
    
}
/// @brief 读取心电数据
/// @return 返回值是adc的值
uint16_t APP_HeartCollect_ReadHeartDate(void)
{
    while (g_isToReadValue == 0)
    {
        /* code */
    }
    g_isToReadValue = 0;
    return Driver_ADC1_ReadValue();

}

