#ifdef MAIN
#include <kt1260.h>
#include <lwip/apps/httpd.h>
#include <core_debug.h>
#include <uart.h>
#include "plc.h"
//#include <plusein.h>
//#include <ArduinoRS485.h> // ArduinoModbus depends on the ArduinoRS485 library
//#include <ArduinoModbus.h>
#include <stdlib.h>
const char swname[] = "1260orig";

HardwareSerial Serial1(USART1);

#include "WebSocketsClient.h"
#include "AutobahnWs.h"
WebSocketsClient eclient;
AutobahnWS ws;

char *ws_url = "192.168.31.10";
uint16_t ws_port = 8888;
char *ws_realm = "Automation";

void httpd_setup();
void httpd_loop();
extern "C"
{
    void uart_debug_init(void);
    void phy_dump();
    void config_init__();
    void config_run__(unsigned long tick);
};
void onJoin();

void setup()
{
    board.begin();
    uart_debug_init();
    // usb.begin();

    Serial1.begin(115200, SERIAL_8E1);
    Serial1.println("start");

    flash_fs.begin(&fspi, PA15);
    flash_fs.info();

    Wire.setSCL(PB8);
    Wire.setSDA(PB9);
    // Wire.begin(MASTER_ADDRESS);
    pcf8563.initClock();
    pcf8563.setDateTime(18, 1, 8, 0, 19, 22, 30, 30);
    // ch423_test();

    atemp_init = analogRead(ATEMP);
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
    ws.begin(eclient, ws_url, ws_port, ws_realm);
    ws.on_join(onJoin);
    plc_status = Started;
}

void rt_application_init()
{
    config_init__();
}

int last;
void loop()
{
    uptime = millis() / 60000;
    // avref = analogRead(AVREF);
    // atemp = analogRead(ATEMP) - atemp_init;
    // // Serial1.print(pcf8563.formatDate());
    // // Serial1.print(" ");
    // // Serial1.println(pcf8563.formatTime());
    // yy1 = ms2.coilRead(0);
    // yy2 = ms2.coilRead(1);
    // yy3 = ms2.coilRead(2);
    // yy4 = ms2.coilRead(3);
    // yy5 = ms2.coilRead(4);
    // yy6 = ms2.coilRead(5);
    // yy7 = ms2.coilRead(6);
    // yy8 = ms2.coilRead(7);
    // yy9 = ms2.coilRead(8);
    // yy10 = ms2.coilRead(9);
    // yy11 = ms2.coilRead(10);
    // yy12 = ms2.coilRead(11);
    // yy13 = ms2.coilRead(12);
    // yy14 = ms2.coilRead(13);
    // yy15 = ms2.coilRead(14);
    // yy16 = ms2.coilRead(15);
    // yy17 = ms2.coilRead(16);
    // yy18 = ms2.coilRead(17);
    // yy19 = ms2.coilRead(18);
    // yy20 = ms2.coilRead(19);
    // yy21 = ms2.coilRead(20);
    // yy22 = ms2.coilRead(21);
    // yy23 = ms2.coilRead(22);
    // yy24 = ms2.coilRead(23);
    // ya1 = ms2.holdingRegisterRead(2);
    // ya2 = ms2.holdingRegisterRead(3);
 
    // if (millis() - last > 10000)
    // {
    //     // phy_dump();
    //     last = millis();
    // }
    // config_run__(10);
    httpd_loop();
    ws.loop();
 
    // // ch.write();
    // ms2.discreteInputWrite(0, xx1);
    // ms2.discreteInputWrite(1, xx2);
    // ms2.discreteInputWrite(2, xx3);
    // ms2.discreteInputWrite(3, xx4);
    // ms2.discreteInputWrite(4, xx5);
    // ms2.discreteInputWrite(5, xx6);
    // ms2.discreteInputWrite(6, xx7);
    // ms2.discreteInputWrite(7, xx8);
    // ms2.discreteInputWrite(8, xx9);
    // ms2.discreteInputWrite(9, xx10);
    // ms2.discreteInputWrite(10, xx11);
    // ms2.discreteInputWrite(11, xx12);
    // ms2.discreteInputWrite(12, xx13);
    // ms2.discreteInputWrite(13, xx14);
    // ms2.discreteInputWrite(14, xx15);
    // ms2.discreteInputWrite(15, xx16);
    // ms2.inputRegisterWrite(0, xa1);
    // ms2.inputRegisterWrite(1, xa2);
    // ms2.inputRegisterWrite(2, xa3);
    // ms2.inputRegisterWrite(3, xa4);
    // ms2.inputRegisterWrite(4, xa5);
    // ms2.inputRegisterWrite(5, xa6);
    // ms2.inputRegisterWrite(6, xa7);
    // ms2.inputRegisterWrite(7, xa8);
    // ms2.inputRegisterWrite(8, xa9);
    // ms2.inputRegisterWrite(9, xa10);
    // ms2.inputRegisterWrite(10, xt1);
    // ms2.inputRegisterWrite(11, xt2);
    // ms2.inputRegisterWrite(12, xt3);
    // ms2.inputRegisterWrite(13, xt4);
    // ms2.coilWrite(0, yy1);
    // ms2.coilWrite(1, yy2);
    // ms2.coilWrite(2, yy3);
    // ms2.coilWrite(3, yy4);
    // ms2.coilWrite(4, yy5);
    // ms2.coilWrite(5, yy6);
    // ms2.coilWrite(6, yy7);
    // ms2.coilWrite(7, yy8);
    // ms2.coilWrite(8, yy9);
    // ms2.coilWrite(9, yy10);
    // ms2.coilWrite(10, yy11);
    // ms2.coilWrite(11, yy12);
    // ms2.coilWrite(12, yy13);
    // ms2.coilWrite(13, yy14);
    // ms2.coilWrite(14, yy15);
    // ms2.coilWrite(15, yy16);
    // ms2.coilWrite(16, yy17);
    // ms2.coilWrite(17, yy18);
    // ms2.coilWrite(18, yy19);
    // ms2.coilWrite(19, yy20);
    // ms2.coilWrite(20, yy21);
    // ms2.coilWrite(21, yy22);
    // ms2.coilWrite(22, yy23);
    // ms2.coilWrite(23, yy24);
    // ms2.holdingRegisterWrite(0, build);  //
    // ms2.holdingRegisterWrite(1, uptime); //
    // ms2.holdingRegisterWrite(2, ya1);    //
    // ms2.holdingRegisterWrite(3, ya2);    //
    // ms2.poll();
    // usb.loop();
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
#endif