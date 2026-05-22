#include "Driver_TIM7.h"

void Driver_TIM7_Init(void)
{
    // 开启时钟
    RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;
    // 预分频的值
    TIM7->PSC = 7200 - 1;
    // 重装载寄存器的值;中断周期是1ms
    TIM7->ARR = 10 - 1;
    // 设置ug位。触发一次更新事件
    TIM7->EGR |= TIM_EGR_UG;
    // 清楚中断标志位
    TIM7->SR &= ~TIM_SR_UIF;
    // 开启更新中断
    TIM7->DIER |= TIM_DIER_UIE;
    // NVIC的配置:
    NVIC_SetPriority(TIM7_IRQn, 2);
    NVIC_EnableIRQ(TIM7_IRQn);
}

void Driver_TIM7_Start(void)
{
    // 使能计数器
    TIM7->CR1 |= TIM_CR1_CEN;
}

void Driver_TIM7_Stop(void)
{
    // 失能计数器
    TIM7->CR1 &= ~TIM_CR1_CEN;
}

__weak void TIM7_UpInterrupMstCallBack(uint32_t msCount)
{
}
uint32_t msCount = 0;
// 中断服务函数
void TIM7_IRQHandler(void)
{
    TIM7->SR &= ~TIM_SR_UIF;
    // 每一毫秒产生一次中断
    msCount++;
    TIM7_UpInterrupMstCallBack(msCount);
}
