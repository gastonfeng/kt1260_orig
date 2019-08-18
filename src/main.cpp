#include <Arduino.h>
#include <lwip/apps/httpd.h>
#include <core_debug.h>

// #include "plc.h"
//#include <plusein.h>
//#include <ArduinoRS485.h> // ArduinoModbus depends on the ArduinoRS485 library
//#include <ArduinoModbus.h>
#include <stdlib.h>
const char swname[] = "1260orig";
uint8_t xx1, xx2, xx3, xx4, xx5, xx6, xx7, xx8, xx9, xx10, xx11, xx12, xx13, xx14, xx15, xx16, yy1, yy2, yy3, yy4, yy5, yy6, yy7, yy8, yy9, yy10, yy11, yy12, yy13, yy14, yy15, yy16, yy17, yy18, yy19, yy20, yy21, yy22, yy23, yy24;
uint16_t xa1, xa2, xa3, xa4, xa5, xa6, xa7, xa8, xa9, xa10, ya1, ya2;
int xt1, xt2, xt3, xt4;

#include <ArduinoModbus.h>
#include <ArduinoRS485.h>
DEFINE_USART_RS485(serial3, 3, 0, 0);
ModbusRTUServerClass ms2;

#include "Rtc_Pcf8563.h"
Rtc_Pcf8563 pcf8563(PB9, PB8);

#include <pt100_hx711.h>
pt100_hx711 hx1(PE11, PE12), hx2(PE13, PE14), hx3(PE15, PB10), hx4(PD12, PD13);

#include "ad7689.h"
AD7689 ad(0, 8);

#include "ch423.h"
ch423 ch;

#include <MCPDAC.h>
MCPDACClass mcp;

#include <Wire.h>


void httpd_setup();
void httpd_loop();
extern "C"
{
    void phy_dump();
    void config_init__();
    void config_run__(unsigned long tick);
    int debug_printf(const char *str, ...)
    {
        Serial1.println(str);
        return 0;
    }

    unsigned int GetRand()
    {
        unsigned int seed = millis();
        return rand_r(&seed) + millis();
    }
};
void ch423_test();
void setup()
{

    Wire.begin(PB9,PB8);
    ch423_test();
    mcp.begin(PC7, PD14);
    ad.selftest();
    pinMode(X1, INPUT_PULLUP);
    pinMode(X2, INPUT_PULLUP);
    pinMode(X3, INPUT_PULLUP);
    pinMode(X4, INPUT_PULLUP);
    pinMode(X5, INPUT_PULLUP);
    pinMode(X6, INPUT_PULLUP);
    pinMode(X7, INPUT_PULLUP);
    pinMode(X8, INPUT_PULLUP);
    pinMode(X9, INPUT_PULLUP);
    pinMode(X10, INPUT_PULLUP);
    pinMode(X11, INPUT_PULLUP);
    pinMode(X12, INPUT_PULLUP);
    pinMode(X13, INPUT_PULLUP);
    pinMode(X14, INPUT_PULLUP);
    pinMode(X15, INPUT_PULLUP);
    pinMode(X16, INPUT_PULLUP);
    pinMode(XA4, INPUT_ANALOG);
    pinMode(XA7, INPUT_ANALOG);
    // srand(1111111);
    core_debug("rand:%d\n", GetRand());
    pinMode(PA5, OUTPUT);
    digitalWrite(PA5, LOW);
    delay(10);
    digitalWrite(PA5, HIGH);
    delay(100);
    // while(1);
    // rt_hw_interrupt_disable();
    /* startup RT-Thread RTOS */
    //    rt_thread_startup();
    httpd_setup();
    hx1.begin();
    hx2.begin();
    hx3.begin();
    hx4.begin();
    if (!ms2.begin(&serial3, 1, 115200))
    {
        Serial1.println("Failed to start Modbus RTU Server!");
        while (1)
            ;
    }
    ms2.configureInputRegisters(0x00, 4);
    ms2.configureHoldingRegisters(0x00, 4);
    ms2.configureDiscreteInputs(0x00, 5);
    ms2.configureCoils(0x00, 6);
}
void rt_application_init()
{
    config_init__();
}

int last;
void loop()
{
    uptime = millis() / 60000;
    yy1 = ms2.coilRead(0);
    yy2 = ms2.coilRead(1);
    yy3 = ms2.coilRead(2);
    yy4 = ms2.coilRead(3);
    yy5 = ms2.coilRead(4);
    yy6 = ms2.coilRead(5);
    ya1 = ms2.holdingRegisterRead(0);
    ya2 = ms2.holdingRegisterRead(1);
    xa1 = ad.acquireChannel(0);
    xa2 = ad.acquireChannel(1);
    xa3 = ad.acquireChannel(2);
    xa4 = analogRead(XA4);
    xa5 = ad.acquireChannel(3);
    xa6 = ad.acquireChannel(4);
    xa7 = analogRead(XA7);
    xa8 = ad.acquireChannel(5);
    xa9 = ad.acquireChannel(6);
    xa10 = ad.acquireChannel(7);
    xx1 = digitalRead(X1);
    xx2 = digitalRead(X2);
    xx3 = digitalRead(X3);
    xx4 = digitalRead(X4);
    xx5 = digitalRead(X5);
    xx6 = digitalRead(X6);
    xx7 = digitalRead(X7);
    xx8 = digitalRead(X8);
    xx9 = digitalRead(X9);
    xx10 = digitalRead(X10);
    xx11 = digitalRead(X11);
    xx12 = digitalRead(X12);
    xx13 = digitalRead(X13);
    xx14 = digitalRead(X14);
    xx15 = digitalRead(X15);
    xx16 = digitalRead(X16);
    hx1.loop();
    hx2.loop();
    hx3.loop();
    hx4.loop();
    xt1 = hx1.value() * 100;
    xt2 = hx2.value() * 100;
    xt3 = hx3.value() * 100;
    xt4 = hx4.value() * 100;
    if (millis() - last > 10000)
    {
        phy_dump();
        last = millis();
    }
    // config_run__(10);
    httpd_loop();
    // yout.setBit(0,yy1);
    // yout.setBit(1,yy2);
    // yout.setBit(2,yy3);
    // yout.setBit(3,yy4);
    // yout.setBit(4,yy5);
    // yout.setBit(5,yy6);
    // yout.setBit(6,yy7);
    // yout.setBit(7,yy8);
    shiftOut(PD5, PD3, LSBFIRST, yy1);
    // yout.setBit(0,yy9);
    // yout.setBit(1,yy10);
    // yout.setBit(2,yy11);
    // yout.setBit(3,yy12);
    // yout.setBit(4,yy13);
    // yout.setBit(5,yy14);
    // yout.setBit(6,yy15);
    // yout.setBit(7,yy16);
    shiftOut(PD5, PD3, LSBFIRST, yy9);
    // yout.setBit(0,yy17);
    // yout.setBit(1,yy18);
    // yout.setBit(2,yy19);
    // yout.setBit(3,yy20);
    // yout.setBit(4,yy21);
    // yout.setBit(5,yy22);
    // yout.setBit(6,yy23);
    // yout.setBit(7,yy24);
    shiftOut(PD5, PD3, LSBFIRST, yy17);
    mcp.setVoltage(0, ya1);
    mcp.setVoltage(1, ya2);
    mcp.update();
    // ch.write();
    ms2.discreteInputWrite(0, xx1);
    ms2.inputRegisterWrite(0, xa1);
    ms2.coilWrite(0, yy1);
    ms2.coilWrite(1, yy2);
    ms2.coilWrite(2, yy3);
    ms2.coilWrite(3, yy4);
    ms2.coilWrite(4, yy5);
    ms2.coilWrite(5, yy6);
    ms2.holdingRegisterWrite(0, build);  //
    ms2.holdingRegisterWrite(1, uptime); //
    ms2.holdingRegisterWrite(2, ya1);    //
    ms2.holdingRegisterWrite(3, ya2);    //
    ms2.poll();
}
//DEFINE_USART_RS485(mons, 1, 0, 0);
//DEFINE_USART_RS485(rs485, 3, 0, 0);
//void modbus_server()
//{
//    if (!ModbusRTUServer.begin(&mons, 1, 9600))
//    {
//        //Serial.println("Failed to start Modbus RTU Server!");
//        while (1)
//            ;
//    }
//    ModbusRTUServer.configureHoldingRegisters(0x00, 13);
//    while (1)
//    {
//        ModbusRTUServer.poll(); //
//        ModbusRTUServer.holdingRegisterWrite(0, 0);
//    }
//}
void ch423_test()
{
    unsigned char i, j;
    // Delay( 50 );
    for (i = 0; i < 16; i++)
        ch.CH423_buf_index(i, 0);     // 因为CH423复位时不清空显示内容，所以刚开电后必须人为清空，再开显示
    ch.CH423_buf_write(CH423_SYSON1); // 开启显示
    // 如果需要定期刷新显示内容，那么只要执行17个命令，包括16个数据加载命令，以及1个开启显示命令
    ch.CH423_buf_write(CH423_DIG15 | BCD_decode_tab[15]); // 显示BCD码1
    ch.CH423_buf_write(CH423_DIG14 | BCD_decode_tab[14]);
    ch.CH423_buf_write(CH423_DIG13 | BCD_decode_tab[13]);
    ch.CH423_buf_write(CH423_DIG12 | BCD_decode_tab[12]);
    ch.CH423_buf_write(CH423_DIG11 | BCD_decode_tab[11]); // 显示BCD码1
    ch.CH423_buf_write(CH423_DIG10 | BCD_decode_tab[10]);
    ch.CH423_buf_write(CH423_DIG9 | BCD_decode_tab[9]);
    ch.CH423_buf_write(CH423_DIG8 | BCD_decode_tab[8]);
    ch.CH423_buf_write(CH423_DIG7 | BCD_decode_tab[7]);
    ch.CH423_buf_write(CH423_DIG6 | BCD_decode_tab[6]);
    ch.CH423_buf_write(CH423_DIG5 | BCD_decode_tab[5]); // 显示BCD码1
    ch.CH423_buf_write(CH423_DIG4 | BCD_decode_tab[4]);
    ch.CH423_buf_write(CH423_DIG3 | BCD_decode_tab[3]);
    ch.CH423_buf_write(CH423_DIG2 | BCD_decode_tab[2]);
    ch.CH423_buf_write(CH423_DIG1 | BCD_decode_tab[1]);
    ch.CH423_buf_write(CH423_DIG0 | BCD_decode_tab[0]);
    while (1)
    { // 演示
        for (i = 0; i < 16; i++)
            ch.CH423_buf_index(i, 0xFF); // 全亮
        // mDelayS( 1 );
        for (i = 0; i < 16; i++)
            ch.CH423_buf_index(i, 0x00); // 全灭
        delay(500);
        for (j = 0; j != 8; j++)
        { // 依次扫描每段，演示
            for (i = 0; i != 16; i++)
                ch.CH423_buf_index(i, 1 << j);
            delay(250);
        }
        for (i = 0; i < 16; i++)
            ch.CH423_buf_index(i, 0xFF); // 全亮
        delay(500);
        for (i = 0; i < 16; i++)
            ch.CH423_buf_index(i, BCD_decode_tab[i]); // 依次显示BCD译码0、1、2、3、4、5、6、7、8、9、A、b、c、d、E、F
        delay(500);
        for (i = 0; i != 8; i++) // 左循环
        {
            ch.LEFTCYC();
            delay(250);
        }
        for (i = 0; i != 8; i++) // 右循环
        {
            ch.RIGHTCYC();
            delay(250);
        }
        for (i = 0; i != 8; i++) // 左移
        {
            ch.LEFTMOV();
            delay(250);
        }
        for (i = 0; i != 8; i++) // 右移
        {
            ch.RIGHTMOV();
            delay(250);
        }
        for (i = 0; i < 16; i++)
            ch.CH423_buf_index(i, BCD_decode_tab[i]); // 依次显示BCD译码0、1、2、3、4、5、6、7、8、9、a、b、c、d、E、F
        delay(250);
        for (i = 0; i != 16; i++) // 闪烁
        {
            ch.TWINKLE(i);
            delay(100);
        }
        for (i = 0; i < 16; i++)
            ch.CH423_buf_index(i, 0x00); // 全灭
        delay(250);
        for (i = 0; i != 16 * 8; i++) // 依次置段位
        {
            ch.CH423_set_bit(i);
            delay(100);
        }
        delay(500);
        for (i = 0; i != 16 * 8; i++) // 依次清段位
        {
            ch.CH423_clr_bit(i);
            delay(100);
        }
        delay(500);
    }
}