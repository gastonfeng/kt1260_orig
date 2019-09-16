#include <kt1260.h>
#include "lwip/apps/httpd.h"
extern "C"
{

    //SSI插入标签
    static const char *ppcTAGs[] = //SSI的Tag
        {
            "flashcode",
            "flashsize",
            "ffssize",
            "ffsfree",
            "ws_url",
            "ws_port",
            "ws_realm",
            "e", //登录错误
            "h", //IP模式
            "i", //IP地址
            "j", //端口
            "k", //工作模式
            "l", //子网掩码
            "m", //网关
            "n", //目的IP
            "o", //目的端口
            "w", //波特率
            "x", //数据位
            "y", //校验位
            "z", //停止位
            "X01",
            "X02",
            "Y00",
    };
    int WEB_dis_Handler(char *dst, const char *src)
    {
        int len = strlen(src);
        strncpy(dst, src, len);
        return len;
    }
    //SSI的Handler句柄
    //根据不同的索引来插入对应的数据
    //返回：插入数据的字符串长度
    static u16_t SSIHandler(int iIndex, char *pcInsert, int iInsertLen)
    {
        char *p;
        switch (iIndex)
        {
        case 0:
            return WEB_dis_Handler(pcInsert, xx1 ? "1" : "0");
            break;
        case 1:
            return WEB_dis_Handler(pcInsert, xx2 ? "1" : "0");
            break;
        case 2:
            return WEB_dis_Handler(pcInsert, yy1 ? "1" : "0");
            break;
        case 111:

            p = "用户名或密码错误！！！";

            return WEB_dis_Handler(pcInsert, p);

            break;

        case 112: //IP获取方式

            if (0) //lwipdev.dhcp_enable)
                p = "动态获取";

            else
                p = "静态";

            return WEB_dis_Handler(pcInsert, p);

            break;

        case 1112: //ip地址

            // WEB_dis_Handler(pcInsert, pIp_addr);

            break;

        case 3: //端口

            // WEB_dis_Handler(pcInsert, pIp_Localport);

            break;

        case 4: //工作模式

            // if (lwipdev.tcp_mode == TCP_SERVER_MODE)

            p = "TCP server";

            // else

            p = "TCP client";

            return WEB_dis_Handler(pcInsert, p);

            break;
        }
        return WEB_dis_Handler(pcInsert, "ERROR");
        ;
    }
    int FindCGIParameter(const char *pcToFind, char *pcParam[], int iNumParams)
    {
        int iLoop;
        for (iLoop = 0; iLoop < iNumParams; iLoop++)
        {
            if (strcmp(pcToFind, pcParam[iLoop]) == 0)
            {
                return (iLoop); //返回iLOOP
            }
        }
        return (-1);
    }

    void httpd_cgi_handler(const char *uri, int iNumParams, char **pcParam, char **pcValue
#if defined(LWIP_HTTPD_FILE_STATE) && LWIP_HTTPD_FILE_STATE
                           ,
                           void *connection_state
#endif /* LWIP_HTTPD_FILE_STATE */
    )
    {
        int i;

        printf(" httpd_cgi_handler：uri = %s,count = %d \n ", uri, iNumParams);
        for (i = 0; i < iNumParams; i++)
        {
            printf(" param %d,id = %c,va;= %c \n ", i, (*pcParam)[i], (*pcValue)[i]);
        }
    }
    const char *yout_CGIHandler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[])
    {
        iIndex = FindCGIParameter("Y00", pcParam, iNumParams); //找到led的索引号
        //只有一个CGI句柄 iIndex=0
        if (iIndex != -1)
        {
            yy1 = ~yy1; //关闭LED1灯
        }
        return "/io.shtml";
    }
    static const tCGI cgis[] = //cgi程序
        {
            {"/yout.cgi", yout_CGIHandler},
    };
}

void web_init()
{
    http_set_cgi_handlers(cgis, sizeof(cgis) / sizeof(tCGI));
    http_set_ssi_handler(SSIHandler, ppcTAGs, sizeof(ppcTAGs) / 4);
}