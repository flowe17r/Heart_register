#ifndef __COMMON_DEBEG_H
#define __COMMON_DEBEG_H

#include "Driver_UASRT1.h"
#include "string.h"


#define DEBUG  // 调试阶段开启，发布阶段注释掉这行

#ifdef DEBUG
//初始化不用的时候就不用调用
#define debug_Init() Common_Debug_Init()

//定义DEBUG时：执行真实的printf打印调试信息
//1. 获取短文件名的宏（修正括号冗余）

#define FILENAME (strrchr(__FILE__, '\\') ? (strrchr(__FILE__, '\\') + 1) : __FILE__)

// 2. 带文件名+行号的调试打印宏（修正字符串拼接与参数传递）
#define debug_printf(format, ...)  printf("[%s:%d]--" format,FILENAME, __LINE__, ##__VA_ARGS__)
//自带\r\n，
#define debug_printfln(format, ...)  printf("[%s:%d]--" format "\r\n", FILENAME, __LINE__, ##__VA_ARGS__)

//
#else
// 未定义DEBUG时：空语句（编译时直接优化掉，不执行任何操作）
#define debug_Init() ((void)0)
#define debug_printf(format,...)  ((void)0)
#define debug_printfln(format, ...) ((void)0)
#endif

void Common_Debug_Init(void);

#endif //__COMMON_DEBEG_H

