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
DEFINE_USART_RS485(serial3, 3, -1, -1);
ModbusRTUServerClass ms2;

#include "Rtc_Pcf8563.h"
Rtc_Pcf8563 pcf8563(PB9, PB8);

#include <pt100_hx711.h>
pt100_hx711 hx1(PE11, PE12), hx2(PE13, PE14), hx3(PE15, PB10), hx4(PD12, PD13);

#include "ad7689.h"
SWSPI spi(PD11, PD9, PD8, PD10);
AD7689 ad(&spi, 8);

#include "ch423.h"
ch423 ch;

#include <MCPDAC.h>
MCPDACClass mcp;

#include <Wire.h>


#include <ShiftRegister74HC595.h>
ShiftRegister74HC595 sr (3, PD5, PD3, PD2); 

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
    sr.setAllLow(); 
    pinMode(PC12,OUTPUT);
    digitalWrite(PC12,LOW);
    Serial1.begin(9600);
    Serial1.println("start");
    Wire.setSCL(PB8);
    Wire.setSDA(PB9);
    Wire.begin(MASTER_ADDRESS);
    pcf8563.initClock();
    pcf8563.setDateTime(18, 1, 8, 0, 19, 22, 30, 30);
    // ch423_test();

    mcp.begin(PC7, PC6, PD15, PD14);
    mcp.setGain(0, true);
    mcp.setGain(1, true);
    mcp.shutdown(0, false);
    mcp.shutdown(1, false);
    // while (!ad.selftest())
        ;
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
    atemp_init=analogRead(ATEMP);
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
    serial3.begin(9600);
    if (!ms2.begin(&serial3, 1, 9600))
    {
        Serial1.println("Failed to start Modbus RTU Server!");
        while (1)
            ;
    }
    ms2.configureInputRegisters(0x00, 14);
    ms2.configureHoldingRegisters(0x00, 4);
    ms2.configureDiscreteInputs(0x00, 16);
    ms2.configureCoils(0x00, 24);

}
void rt_application_init()
{
    config_init__();
}

int last;
void loop()
{
    uptime = millis() / 60000;
    avref=analogRead(AVREF);
    atemp=analogRead(ATEMP)-atemp_init;
    // Serial1.print(pcf8563.formatDate());
    // Serial1.print(" ");
    // Serial1.println(pcf8563.formatTime());
    yy1 = ms2.coilRead(0);
    yy2 = ms2.coilRead(1);
    yy3 = ms2.coilRead(2);
    yy4 = ms2.coilRead(3);
    yy5 = ms2.coilRead(4);
    yy6 = ms2.coilRead(5);
    yy7 = ms2.coilRead(6);
    yy8 = ms2.coilRead(7);
    yy9 = ms2.coilRead(8);
    yy10 = ms2.coilRead(9);
    yy11 = ms2.coilRead(10);
    yy12 = ms2.coilRead(11);
    yy13 = ms2.coilRead(12);
    yy14 = ms2.coilRead(13);
    yy15 = ms2.coilRead(14);
    yy16 = ms2.coilRead(15);
    yy17 = ms2.coilRead(16);
    yy18 = ms2.coilRead(17);
    yy19 = ms2.coilRead(18);
    yy20 = ms2.coilRead(19);
    yy21 = ms2.coilRead(20);
    yy22 = ms2.coilRead(21);
    yy23 = ms2.coilRead(22);
    yy24 = ms2.coilRead(23);
    ya1 = ms2.holdingRegisterRead(2);
    ya2 = ms2.holdingRegisterRead(3);
    xa1 = ad.acquireChannel(0) * 2000 / 2.5;
    xa2 = ad.acquireChannel(1) * 2000 / 2.5;
    xa3 = ad.acquireChannel(2) * 2000 / 2.5;
    xa4 = analogRead(XA4);
    xa5 = ad.acquireChannel(3) * 2000 / 2.5;
    xa6 = ad.acquireChannel(4) * 2000 / 2.5;
    xa7 = analogRead(XA7);
    xa8 = ad.acquireChannel(5) * 2000 / 2.5;
    xa9 = ad.acquireChannel(6) * 2000 / 2.5;
    xa10 = ad.acquireChannel(7) * 2000 / 2.5;
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
    // hx1.loop();
    // hx2.loop();
    // hx3.loop();
    // hx4.loop();
    xt1 = hx1.value() * 100;
    xt2 = hx2.value() * 100;
    xt3 = hx3.value() * 100;
    xt4 = hx4.value() * 100;
    if (millis() - last > 10000)
    {
        // phy_dump();
        last = millis();
    }
    // config_run__(10);
    httpd_loop();
    sr.setNoUpdate(0,yy1);
    sr.setNoUpdate(1,yy2);
    sr.setNoUpdate(2,yy3);
    sr.setNoUpdate(3,yy4);
    sr.setNoUpdate(4,yy5);
    sr.setNoUpdate(5,yy6);
    sr.setNoUpdate(6,yy7);
    sr.setNoUpdate(7,yy8);
    sr.setNoUpdate(8,yy9);
    sr.setNoUpdate(9,yy10);
    sr.setNoUpdate(10,yy11);
    sr.setNoUpdate(11,yy12);
    sr.setNoUpdate(12,yy13);
    sr.setNoUpdate(13,yy14);
    sr.setNoUpdate(14,yy15);
    sr.setNoUpdate(15,yy16);
    sr.setNoUpdate(16,yy17);
    sr.setNoUpdate(17,yy18);
    sr.setNoUpdate(18,yy19);
    sr.setNoUpdate(19,yy20);
    sr.setNoUpdate(20,yy21);
    sr.setNoUpdate(21,yy22);
    sr.setNoUpdate(22,yy23);
    sr.setNoUpdate(23,yy24);
    sr.updateRegisters();
    mcp.setVoltage(0, ya1);
    mcp.setVoltage(1, ya2);
    mcp.update();
    // ch.write();
    ms2.discreteInputWrite(0, xx1);
    ms2.discreteInputWrite(1, xx2);
    ms2.discreteInputWrite(2, xx3);
    ms2.discreteInputWrite(3, xx4);
    ms2.discreteInputWrite(4, xx5);
    ms2.discreteInputWrite(5, xx6);
    ms2.discreteInputWrite(6, xx7);
    ms2.discreteInputWrite(7, xx8);
    ms2.discreteInputWrite(8, xx9);
    ms2.discreteInputWrite(9, xx10);
    ms2.discreteInputWrite(10, xx11);
    ms2.discreteInputWrite(11, xx12);
    ms2.discreteInputWrite(12, xx13);
    ms2.discreteInputWrite(13, xx14);
    ms2.discreteInputWrite(14, xx15);
    ms2.discreteInputWrite(15, xx16);
    ms2.inputRegisterWrite(0, xa1);
    ms2.inputRegisterWrite(1, xa2);
    ms2.inputRegisterWrite(2, xa3);
    ms2.inputRegisterWrite(3, xa4);
    ms2.inputRegisterWrite(4, xa5);
    ms2.inputRegisterWrite(5, xa6);
    ms2.inputRegisterWrite(6, xa7);
    ms2.inputRegisterWrite(7, xa8);
    ms2.inputRegisterWrite(8, xa9);
    ms2.inputRegisterWrite(9, xa10);
    ms2.inputRegisterWrite(10, xt1);
    ms2.inputRegisterWrite(11, xt2);
    ms2.inputRegisterWrite(12, xt3);
    ms2.inputRegisterWrite(13, xt4);
    ms2.coilWrite(0, yy1);
    ms2.coilWrite(1, yy2);
    ms2.coilWrite(2, yy3);
    ms2.coilWrite(3, yy4);
    ms2.coilWrite(4, yy5);
    ms2.coilWrite(5, yy6);
    ms2.coilWrite(6, yy7);
    ms2.coilWrite(7, yy8);
    ms2.coilWrite(8, yy9);
    ms2.coilWrite(9, yy10);
    ms2.coilWrite(10, yy11);
    ms2.coilWrite(11, yy12);
    ms2.coilWrite(12, yy13);
    ms2.coilWrite(13, yy14);
    ms2.coilWrite(14, yy15);
    ms2.coilWrite(15, yy16);
    ms2.coilWrite(16, yy17);
    ms2.coilWrite(17, yy18);
    ms2.coilWrite(18, yy19);
    ms2.coilWrite(19, yy20);
    ms2.coilWrite(20, yy21);
    ms2.coilWrite(21, yy22);
    ms2.coilWrite(22, yy23);
    ms2.coilWrite(23, yy24);
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
        ch.CH423_buf_index(i, 0); // 因为CH423复位时不清空显示内容，所以刚开电后必须人为清空，再开显示
    ch.CH423_Write(4, 0x17);      // 开启显示

    // 如果需要定期刷新显示内容，那么只要执行17个命令，包括16个数据加载命令，以及1个开启显示命令
    ch.CH423_buf_write(CH423_DIG15, BCD_decode_tab[15] & 0x0); // 显示BCD码1
    ch.CH423_buf_write(CH423_DIG14, BCD_decode_tab[14] & 0x0);
    ch.CH423_buf_write(CH423_DIG13, BCD_decode_tab[13] | 0xff);
    ch.CH423_buf_write(CH423_DIG12, BCD_decode_tab[12] | 0xff);
    ch.CH423_buf_write(CH423_DIG11, BCD_decode_tab[11] | 0xff); // 显示BCD码1
    ch.CH423_buf_write(CH423_DIG10, BCD_decode_tab[10] | 0xff);
    ch.CH423_buf_write(CH423_DIG9, BCD_decode_tab[9] | 0xff);
    ch.CH423_buf_write(CH423_DIG8, BCD_decode_tab[8] | 0xff);
    ch.CH423_buf_write(CH423_DIG7, BCD_decode_tab[7] | 0xff);
    ch.CH423_buf_write(CH423_DIG6, BCD_decode_tab[6] | 0xff);
    ch.CH423_buf_write(CH423_DIG5, BCD_decode_tab[5] | 0xff); // 显示BCD码1
    ch.CH423_buf_write(CH423_DIG4, BCD_decode_tab[4] | 0xff);
    ch.CH423_buf_write(CH423_DIG3, BCD_decode_tab[3] | 0xff);
    ch.CH423_buf_write(CH423_DIG2, BCD_decode_tab[2] | 0xff);
    ch.CH423_buf_write(CH423_DIG1, BCD_decode_tab[1] | 0xff);
    ch.CH423_buf_write(CH423_DIG0, BCD_decode_tab[0] | 0xff);
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