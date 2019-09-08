#include <Arduino.h>
#include "lwip/apps/httpd.h"
#include "flashFs.h"
FlashFile *fw;
extern "C"
{

    //SSI�����ǩ
    static const char *ppcTAGs[] = //SSI��Tag
        {
            "X01", "X02","Y00",
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
    err_t httpd_post_begin(void *connection, const char *uri, const char *http_request,
                           u16_t http_request_len, int content_len, char *response_uri,
                           u16_t response_uri_len, u8_t *post_auto_wnd)
    {
        struct http_state *hs = (struct http_state *)connection;
        fw = new FlashFile("prog", SPIFFS_APPEND | SPIFFS_CREAT | SPIFFS_RDWR);
        if (!uri || (uri[0] == '\0'))
        {
            return ERR_ARG;
        }
        return ERR_OK;
    }

/** Called for each pbuf of data that has been received for a POST.
 * ATTENTION: The application is responsible for freeing the pbufs passed in!
 *
 * @param connection Unique connection identifier.
 * @param p Received data.
 * @return ERR_OK: Data accepted.
 *         another err_t: Data denied, http_post_get_response_uri will be called.
 */
#define LWIP_HTTPD_POST_MAX_PAYLOAD_LEN 512
    static char http_post_payload[LWIP_HTTPD_POST_MAX_PAYLOAD_LEN];
    static u16_t http_post_payload_len = 0;
    err_t httpd_post_receive_data(void *connection, struct pbuf *p)
    {
        struct http_state *hs = (struct http_state *)connection;
        struct pbuf *q = p;
        int count;
        u32_t http_post_payload_full_flag = 0;
        while (q != NULL) // ������յ�������http_post_payload
        {
            if (http_post_payload_len + q->len <= LWIP_HTTPD_POST_MAX_PAYLOAD_LEN)
            {
                // MEMCPY(http_post_payload + http_post_payload_len, q->payload, q->len);
                fw->write((char *)q->payload, q->len);
                http_post_payload_len += q->len;
            }
            else
            { // ������� �������־λ
                http_post_payload_full_flag = 1;
                break;
            }
            q = q->next;
        }

        pbuf_free(p); // �ͷ�pbuf

        if (http_post_payload_full_flag) // ������� ��������
        {
            http_post_payload_full_flag = 0;
            http_post_payload_len = 0;
        }
        else if (hs->post_content_len_left == 0)
        { // POST�����Ѿ�������� ����
            printf("[*] payload=%s \n", http_post_payload);
            // hs->req_info.post_data = http_post_payload;
            //count = extract_uri_parameters(hs, http_post_payload);  // ����
            printf("[*] POST PARAMETERS: %s, %s, payload=%s", hs->params, hs->param_vals, http_post_payload);
            http_post_payload_len = 0;
        }
        return ERR_OK;
    }

    /** Called when all data is received or when the connection is closed.
 * The application must return the filename/URI of a file to send in response
 * to this POST request. If the response_uri buffer is untouched, a 404
 * response is returned.
 *
 * @param connection Unique connection identifier.
 * @param response_uri Filename of response file, to be filled when denying the request
 * @param response_uri_len Size of the 'response_uri' buffer.
 */
    void httpd_post_finished(void *connection, char *response_uri, u16_t response_uri_len)
    {
        printf("[*] httpd_post_finished invoked, uri=%s", response_uri);
        struct http_state *hs = (struct http_state *)connection;
        if (hs != NULL)
        {
            strncpy(response_uri, "/", response_uri_len);
        }
        fw->close();
    }
}

void web_init()
{
    http_set_cgi_handlers(cgis, sizeof(cgis) / sizeof(tCGI));
    http_set_ssi_handler(SSIHandler, ppcTAGs, sizeof(ppcTAGs) / 4);
}