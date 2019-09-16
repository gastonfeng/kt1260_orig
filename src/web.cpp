#include <kt1260.h>
#include "lwip/apps/httpd.h"
extern "C"
{

    //SSI�����ǩ
    static const char *ppcTAGs[] = //SSI��Tag
        {
            "flashcode",
            "flashsize",
            "ffssize",
            "ffsfree",
            "ws_url",
            "ws_port",
            "ws_realm",
            "e", //��¼����
            "h", //IPģʽ
            "i", //IP��ַ
            "j", //�˿�
            "k", //����ģʽ
            "l", //��������
            "m", //����
            "n", //Ŀ��IP
            "o", //Ŀ�Ķ˿�
            "w", //������
            "x", //����λ
            "y", //У��λ
            "z", //ֹͣλ
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
    //SSI��Handler���
    //���ݲ�ͬ�������������Ӧ������
    //���أ��������ݵ��ַ�������
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

            p = "�û�����������󣡣���";

            return WEB_dis_Handler(pcInsert, p);

            break;

        case 112: //IP��ȡ��ʽ

            if (0) //lwipdev.dhcp_enable)
                p = "��̬��ȡ";

            else
                p = "��̬";

            return WEB_dis_Handler(pcInsert, p);

            break;

        case 1112: //ip��ַ

            // WEB_dis_Handler(pcInsert, pIp_addr);

            break;

        case 3: //�˿�

            // WEB_dis_Handler(pcInsert, pIp_Localport);

            break;

        case 4: //����ģʽ

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
                return (iLoop); //����iLOOP
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

        printf(" httpd_cgi_handler��uri = %s,count = %d \n ", uri, iNumParams);
        for (i = 0; i < iNumParams; i++)
        {
            printf(" param %d,id = %c,va;= %c \n ", i, (*pcParam)[i], (*pcValue)[i]);
        }
    }
    const char *yout_CGIHandler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[])
    {
        iIndex = FindCGIParameter("Y00", pcParam, iNumParams); //�ҵ�led��������
        //ֻ��һ��CGI��� iIndex=0
        if (iIndex != -1)
        {
            yy1 = ~yy1; //�ر�LED1��
        }
        return "/io.shtml";
    }
    static const tCGI cgis[] = //cgi����
        {
            {"/yout.cgi", yout_CGIHandler},
    };
}

void web_init()
{
    http_set_cgi_handlers(cgis, sizeof(cgis) / sizeof(tCGI));
    http_set_ssi_handler(SSIHandler, ppcTAGs, sizeof(ppcTAGs) / 4);
}