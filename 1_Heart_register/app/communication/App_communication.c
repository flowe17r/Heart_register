#include "App_communication.h"

/*
?* ?接收上位机传递过来指令。 ?一共两种指
?* ?1. ?"s1000\n" ?s表示下发的是采样率 ? ? 1000表示采样率（每m采样1000次）
?* ?2. ?"c60\n" ? ?c表示下发的是采集时长 ? 60表示采样60s。 收到这个命令之后开启ADC和定时器开始采集
?* ? ? ?用 \n 表示命令结束
*/
// 初始化
void App_Communication_Start(void)
{
    // 1.初始化串口
    Driver_UASRT1_Init();
    // 2.开启串口
    Driver_USART1_Start();
}

// 标志位，表示所有参数全部接收完毕
uint8_t g_isReceiveComleted = 0;
// 存储采样率
uint8_t g_isReceiveCRate[10] = {0};
// 存储采样时长
uint8_t g_isReceiveCDuration[10] = {0};


void USART1_RxIdleCallBack(uint8_t rxbuff[], uint8_t rxcount)
{
    if (rxbuff[0] == 's') // 下发的是采样率
    {
        // for (uint8_t i = 0; i < rxcount-1; i++)
        // {
        //     g_isReceiveCRate[i] = rxbuff[i+1];
        // }
        memcpy(g_isReceiveCRate, &rxbuff[1], rxcount - 2);
    }
    else if (rxbuff[0] == 'c') // 下发的是采样时长
    {
        memcpy(g_isReceiveCDuration, &rxbuff[1], rxcount - 2);
        g_isReceiveComleted = 1;
    }
}

/// @brief 处理用户指令
/// @param rate 采样率 表示1分钟采集的次数
/// @param duration 采集时长 单位s
void App_Communication_CommandProcess(uint16_t *rate, uint16_t *duration)
{
    // 1.等待用户下发指令
    while (!g_isReceiveComleted)
    {
        /* code */
    }
    // 2.处理指令
    // 2.1 把字符变成数字
    *rate = atoi((char *)g_isReceiveCRate);
    *duration = atoi((char *)g_isReceiveCDuration);
}


uint8_t g_buff[6] = {0}; 
//给上位机发信息
void APP_Communication_SendHeartData(uint16_t heratData)
{
    sprintf((char *)g_buff,"%04lu\n",heratData);
    Driver_USART1_SendString(g_buff,5);
}

