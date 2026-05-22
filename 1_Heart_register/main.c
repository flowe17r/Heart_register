#include "stdint.h"
#include "stm32f10x.h" // Device header
#include "Common_Debug.h"
#include "App_communication.h"
#include "Driver_ADC1.h"
#include "Driver_TIM7.h"
#include "App_Heart_Collect.h"
int main()
{

    debug_Init();
    // printf("心电项目开始运行...\r\n");
    // debug_printf("心电项目开始运行...%d\r\n",A);
    debug_printfln("心电项目开始运行...");

    // 1.启动通讯
    App_Communication_Start();

    // 2.处理用户指令
    debug_printfln("请下发指令“采样率（s1000\\n）和c200\\n");
    uint16_t rate, duration;
    App_Communication_CommandProcess(&rate, &duration);
    debug_printfln("采集率为：%d", rate);
    debug_printfln("采集时间为：%d", duration);

    //3.启动采集模块
    APP_HeartCollect_Start(rate,duration);

    while (1)
    {  
        uint16_t data = APP_HeartCollect_ReadHeartDate();
        APP_Communication_SendHeartData(data);

    }
}
