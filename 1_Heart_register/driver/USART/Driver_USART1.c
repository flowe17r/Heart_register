#include "Driver_UASRT1.h"

/// @brief USART1初始化
void Driver_UASRT1_Init(void)
{
    // 开启时钟
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    // gpio模式配置
    // PA9   TX复用推挽 mode 11 cnf 10
    GPIOA->CRH |= (GPIO_CRH_CNF9_1 | GPIO_CRH_MODE9);
    GPIOA->CRH &= ~GPIO_CRH_CNF9_0;

    // PA10 RX输入浮空  mode 00 cnf 01
    GPIOA->CRH |= GPIO_CRH_CNF10_0;
    GPIOA->CRH &= ~(GPIO_CRH_CNF10_1 | GPIO_CRH_MODE10);

    // 波特率 配置为115200
    USART1->BRR = 0x271;

    /*配置一个字的长度 8位 默认值不配也行 */
    USART1->CR1 &= ~USART_CR1_M;
    /* 配置不需要校验位 默认值不配也行*/
    USART1->CR1 &= ~USART_CR1_PCE;
    /*  配置停止位的长度 默认值不配也行*/
    USART1->CR2 &= ~USART_CR2_STOP;
    /*  使能接收和发送 */
    USART1->CR1 |= USART_CR1_TE;
    USART1->CR1 |= USART_CR1_RE;

    // 使能接收中断和空闲中断
    USART1->CR1 |= USART_CR1_RXNEIE;
    USART1->CR1 |= USART_CR1_IDLEIE;

    // NVIC 配置
    NVIC_SetPriorityGrouping(3);      // 设置NVIC优先级分组为3（抢占优先级3位、响应优先级1位）
    NVIC_SetPriority(USART1_IRQn, 3); // 设置USART1中断的优先级数值为3（具体抢占/响应优先级由分组3决定）
    NVIC_EnableIRQ(USART1_IRQn);      // 使能USART1的NVIC中断通道（打开USART1中断总开关）
}

/// @brief 启动串口1
void Driver_USART1_Start(void)
{
    /* 4. 使能串口 */
    USART1->CR1 |= USART_CR1_UE;
}

/// @brief 停止串口1
void Driver_USART1_Stop(void)
{

    USART1->CR1 &= ~USART_CR1_UE;
}
/// @brief 发送一字节
void Driver_USART1_Sendchar(uint8_t c)
{
    while ((USART1->SR & USART_SR_TXE) == 0)
        ;
    USART1->DR = c;
}

/// @brief 发送字符串
/// @param str  要发送的字符串
/// @param len  要发送的字符串长度
void Driver_USART1_SendString(uint8_t *str, uint16_t len)
{
    for (uint8_t i = 0; i < len; i++)
    {
        Driver_USART1_Sendchar(str[i]);
    }
}

int fputc(int c, FILE *file)
{
    Driver_USART1_Sendchar((uint8_t)c);
    return c;
}
//上层如果需要处理接收到的字符，只需要复写这个方法即可
__weak void USART1_RxIdleCallBack(uint8_t rxbuff[],uint8_t rxcount)
{

}
uint8_t buff[100] ={0};
uint8_t count =0;
//中断服务函数
void USART1_IRQHandler(void)
{
    //驱动层，应该把数据接收存储到对应的缓冲区，然后再去调用弱函数，把缓冲区数据传给弱函数
    if(USART1->SR & USART_SR_RXNE)
    {
        buff[count] = USART1->DR &0xff;
        count++;
    }
    else if (USART1->SR & USART_SR_IDLE)
    {
        //清楚空闲中断标志位
        USART1->SR;
        USART1->DR;
        //执行具体的逻辑
        USART1_RxIdleCallBack(buff,count);
        count = 0;
    }
    
}

