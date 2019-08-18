#ifndef RTCONFIG_H
#define RTCONFIG_H

#ifdef WIN32

#define _WIN32_NATIVE 1
#include "rtconfig_win32.h"

#elif defined(CORTEX_M3)
#include "rtconfig_cm3.h"

#elif defined(ADSTAR)
#include "rtconfig_adstar.h"

#elif defined(S3C2440)||defined(S3C2416)
#include "rtconfig_24xx.h"

#elif defined(__ARMLINUX__)

#else
#error !!!!!!!!!!!!!!Select a platform
#endif


#define RT_NAME_MAX 8


enum
{
 	RTGUI_SVR_THREAD_PRIORITY,
    PRIO_THREAD_DEVICE,
 	PRIO_THREAD_GUI,
    RT_TIMER_THREAD_PRIO,
    PRIO_THREAD_PLC,
    PRIO_THREAD_RETAIN,
    PRIO_THREAD_TXT_SAVE,
    PRIO_THREAD_SOUND,
    FINSH_THREAD_PRIORITY
};

/* PRIORITY_MAX */
#define RT_THREAD_PRIORITY_MAX  32

#define STACK_SIZE_CALI 2048
//  #define RTGUI_USING_MOUSE_CURSOR
//  #define RTGUI_IMAGE_XPM
#define RTGUI_IMAGE_BMP 1

#define RT_USING_SERIAL
#define RT_USING_MTD_NOR
#define RT_USING_MTD_NAND

#define RT_USING_UART1
#define RT_USING_UART2
#define RT_USING_UART3
#define RT_USING_UART4
#define RT_USING_UART5
#define RT_USING_UART6


#define RT_LWIP_DHCP

#define RT_USING_AUDIO
#define RT_USING_HWTIMER
#define RT_USING_CAN
#define RT_USING_PIN
#define RT_USING_WDT
#define RT_USING_SDIO
#define RT_USING_I2C_BITOPS
#define RT_USING_I2C
#define RT_USING_SERIAL
#define RT_USING_USB_HOST
#define RT_USING_USB_DEVICE
#define RT_USING_MTD_NAND
#define RT_USING_MTD_NOR
#define RT_USING_SPI
#define RT_USING_RTC
#define RT_USING_ALARM


#if defined(BUILD_DLL) && !defined(ISSWIG)
#define DLL_EXPORT  __declspec(dllexport)
#else
#define DLL_EXPORT
#endif
#endif
