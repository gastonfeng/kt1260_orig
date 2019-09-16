#ifdef TEST
#include <Arduino.h>
#include <testcase.h>
#include <SPI.h>
uint8_t di[] = {X1, X2, X3, X4, X5, X6, X7, X8, X9, X10, X11, X12, X13, X14, X15, X16}, di_nrs = sizeof(di);
SPIClass fspi(PB5,PB4,PB3);
#include "flashFs.h"
FlashFs flash_fs;
void setup()
{    flash_fs.begin(&fspi,PA15);
    flash_fs.info();
    delay(2000);
    UNITY_BEGIN(); // IMPORTANT LINE!
    RUN_TEST(test_spiffs);
    RUN_TEST(test_di_init);
    UNITY_END();
}
void loop()
{
    UNITY_BEGIN(); // IMPORTANT LINE!  RUN_TEST(test_di_do);
    delay(500);
    RUN_TEST(test_xa);
    delay(500);

    UNITY_END();
}
#endif