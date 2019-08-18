/* RT-Thread config file */
#ifndef __RTTHREAD_CFG_H__
#define __RTTHREAD_CFG_H__

//  #define RT_USING_NEWLIB 1
//  #define RT_USING_MINILIBC 1




/* RT_NAME_MAX*/

/* RT_ALIGN_SIZE*/
#define RT_ALIGN_SIZE 4

/* Tick per Second */
#define RT_TICK_PER_SECOND  1000

/* SECTION: RT_DEBUG */
/* Thread Debug */
//  #define RT_DEBUG
#define RT_THREAD_DEBUG

#define RT_USING_OVERFLOW_CHECK

#define RT_TINY_SIZE
/* Using Hook */
/*  #define RT_USING_HOOK*/

/* Using Software Timer */
//  #define RT_USING_TIMER_SOFT
//  #define RT_TIMER_THREAD_PRIO    4
//  #define RT_TIMER_THREAD_STACK_SIZE  8192
//  #define RT_TIMER_TICK_PER_SECOND  100

/* SECTION: IPC */
/* Using Semaphore*/
#define RT_USING_SEMAPHORE

/* Using Mutex */
#define RT_USING_MUTEX

/* Using Event */
#define RT_USING_EVENT

/* Using MailBox */
#define RT_USING_MAILBOX

/* Using Message Queue */
#define RT_USING_MESSAGEQUEUE

/* SECTION: Memory Management */
/* Using Memory Pool Management*/
#define RT_USING_MEMPOOL

/* Using Dynamic Heap Management */
#define RT_USING_HEAP
//#define RT_USING_MEMHEAP_AS_HEAP
//#define RT_USING_MEMHEAP

/* Using Small MM */
#define RT_USING_SMALL_MEM

/* SECTION: Device System */
/* Using Device System */
#define RT_USING_DEVICE
#define RT_USING_UART1
#define RT_USING_UART2
#define RT_USING_UART3

/* SECTION: Console options */
#define RT_USING_CONSOLE
/* the buffer size of console*/
#define RT_CONSOLEBUF_SIZE  128
#define RT_CONSOLE_DEVICE_NAME  "COM1"

/* SECTION: finsh, a C-Express shell */
#ifdef DEBUG
#define RT_USING_FINSH
#define FINSH_USING_HISTORY 1
#define FINSH_USING_MSH
#define FINSH_USING_MSH_DEFAULT
#define FINSH_USING_SYMTAB
#define FINSH_USING_DESCRIPTION
#endif

/* SECTION: device filesystem */
//  #define RT_USING_DFS  1
#define RT_USING_DFS_DEVFS 1
#define STM32_USE_SDIO  1
//  #define RT_USING_USB_DEVICE 1
//#define RT_USING_RTC 1

#define RT_USB_DEVICE_CDC
#define RT_USB_DEVICE_MSTORAGE
#define RT_USB_MSTORAGE_DISK_NAME "sd0"


//  #define RT_USING_DFS_ELMFAT
#define RT_DFS_ELM_WORD_ACCESS
/* Reentrancy (thread safe) of the FatFs module.  */
#define RT_DFS_ELM_REENTRANT
/* Number of volumes (logical drives) to be used. */
#define RT_DFS_ELM_DRIVES     2
/* #define RT_DFS_ELM_USE_LFN     1 */
#define RT_DFS_ELM_MAX_LFN      255
/* Maximum sector size to be handled. */
#define RT_DFS_ELM_MAX_SECTOR_SIZE  4096

/* the max number of mounted filesystem */
#define DFS_FILESYSTEMS_MAX     2
/* the max number of opened files     */
#define DFS_FD_MAX          4
#define DFS_USING_WORKDIR   1

/* SECTION: lwip, a lighwight TCP/IP protocol stack */
#define RT_USING_LWIP
/* LwIP uses RT-Thread Memory Management */
#define RT_LWIP_USING_RT_MEM
/* Enable ICMP protocol*/
#define RT_LWIP_ICMP
/* Enable UDP protocol*/
#define RT_LWIP_UDP
/* Enable TCP protocol*/
#define RT_LWIP_TCP
/* Enable DNS */
#define RT_LWIP_DNS

/* the number of simulatenously active TCP connections*/
#define RT_LWIP_TCP_PCB_NUM 5

#define RT_LWIP_DEBUG

/* tcp thread options */
#define RT_LWIP_TCPTHREAD_PRIORITY    12
#define RT_LWIP_TCPTHREAD_MBOX_SIZE   10
#define RT_LWIP_TCPTHREAD_STACKSIZE   1024

/* ethernet if thread options */
#define RT_LWIP_ETHTHREAD_PRIORITY    15
#define RT_LWIP_ETHTHREAD_MBOX_SIZE   10
#define RT_LWIP_ETHTHREAD_STACKSIZE   512

/* TCP sender buffer space */
#define RT_LWIP_TCP_SND_BUF 8192
/* TCP receive window. */
#define RT_LWIP_TCP_WND   8192

/* SECTION: RT-Thread/GUI */
#define RT_USING_RTGUI

/* name length of RTGUI object */
#define RTGUI_NAME_MAX    12
/* support 16 weight font */
#define RTGUI_USING_FONT12
#define RTGUI_USING_FONT16
//  #define RTGUI_USING_FONT_COMPACT
/* support Chinese font */
#define RTGUI_USING_FONTHZ
/* use DFS as file interface */
//  #define RTGUI_USING_DFS_FILERW
/* use font file as Chinese font */
//  #define RTGUI_USING_HZ_FILE
/* use Chinese bitmap font */
#define RTGUI_USING_HZ_BMP
/* use small size in RTGUI */
#define RTGUI_USING_SMALL_SIZE
/* use mouse cursor */
/* #define RTGUI_USING_MOUSE_CURSOR */
/* default font size in RTGUI */
#define RTGUI_DEFAULT_FONT_SIZE 12

/* image support */
/* #define RTGUI_IMAGE_XPM */
/* #define RTGUI_IMAGE_BMP */

// <bool name="RT_USING_CMSIS_OS" description="Using CMSIS OS API" default="true" />
// #define RT_USING_CMSIS_OS
// <bool name="RT_USING_RTT_CMSIS" description="Using CMSIS in RTT" default="true" />
#define RT_USING_RTT_CMSIS
// <bool name="RT_USING_BSP_CMSIS" description="Using CMSIS in BSP" default="true" />
// #define RT_USING_BSP_CMSIS

#endif

