#ifdef BOARDTEST
#include <kt1260.h>
#include <testcase.h>
#include <STM32Ethernet.h>
IPAddress ipp(192, 168, 31, 156);
void test_di_do();
void test_axy();
void setup()
{
    board.begin();
    core_debug("start");
    Ethernet.begin(ipp);
    Ethernet.schedule();
}
int flag = 0;
int download(const char *host, uint16_t port, char *url, char *filename);
void loop()
{
    core_debug("loop");
    UNITY_BEGIN(); // IMPORTANT LINE!
    RUN_TEST(test_spiffs);
    RUN_TEST(test_di_init);
    RUN_TEST(test_di_do);
    RUN_TEST(test_axy);
    if (UNITY_END() == 0)
    {
        flag |= 4;
    }
    if (!(flag & 0x1))
    {
        flag |= download("123.207.157.205", 8018, "/stm32flash.exe", "test.bin") ? 0 : 1;
    }
    if (!(flag & 0x2))
    {
        flag |= download("123.207.157.205", 8018, "/stm32flash.exe", "main.bin") ? 0 : 2;
    }
    if (flag == 0x7)
    {
        FlashFile prog("prog", SPIFFS_O_CREAT | SPIFFS_O_RDWR);
        prog.write("test.bin", 8);
        prog.close();

        ch.setChar('V', 1);
    }
    delay(1000);
}
void test_di_do()
{
    yy1 = 1;
    board.output();
    delay(20);
    TEST_ASSERT_EQUAL(LOW, digitalRead(X1));

    yy2 = 1;
    board.output();
    delay(20);
    TEST_ASSERT_EQUAL(LOW, digitalRead(X2));

    yy3 = 1;
    board.output();
    delay(20);
    TEST_ASSERT_EQUAL(LOW, digitalRead(X3));

    yy4 = 1;
    board.output();
    delay(20);
    TEST_ASSERT_EQUAL(LOW, digitalRead(X4));

    yy5 = 1;
    board.output();
    delay(20);
    TEST_ASSERT_EQUAL(LOW, digitalRead(X5));

    yy6 = 1;
    board.output();
    delay(20);
    TEST_ASSERT_EQUAL(LOW, digitalRead(X6));

    yy7 = 1;
    board.output();
    delay(20);
    TEST_ASSERT_EQUAL(LOW, digitalRead(X7));

    yy8 = 1;
    board.output();
    delay(20);
    TEST_ASSERT_EQUAL(LOW, digitalRead(X8));
    yy9 = 1;
    board.output();
    delay(20);
    TEST_ASSERT_EQUAL(LOW, digitalRead(X9));

    yy10 = 1;
    board.output();
    delay(20);
    TEST_ASSERT_EQUAL(LOW, digitalRead(X10));

    yy11 = 1;
    board.output();
    delay(20);
    TEST_ASSERT_EQUAL(LOW, digitalRead(X11));

    yy12 = 1;
    board.output();
    delay(20);
    TEST_ASSERT_EQUAL(LOW, digitalRead(X12));

    yy13 = 1;
    board.output();
    delay(20);
    TEST_ASSERT_EQUAL(LOW, digitalRead(X13));

    yy14 = 1;
    board.output();
    delay(20);
    TEST_ASSERT_EQUAL(LOW, digitalRead(X14));

    yy15 = 1;
    board.output();
    delay(20);
    TEST_ASSERT_EQUAL(LOW, digitalRead(X15));

    yy16 = 1;
    board.output();
    delay(20);
    TEST_ASSERT_EQUAL(LOW, digitalRead(X16));

    yy1 = 0;
    board.output();
    delay(20);
    TEST_ASSERT_EQUAL(HIGH, digitalRead(X1));

    yy2 = 0;
    board.output();
    delay(20);
    TEST_ASSERT_EQUAL(HIGH, digitalRead(X2));

    yy3 = 0;
    board.output();
    delay(20);
    TEST_ASSERT_EQUAL(HIGH, digitalRead(X3));

    yy4 = 0;
    board.output();
    delay(20);
    TEST_ASSERT_EQUAL(HIGH, digitalRead(X4));

    yy5 = 0;
    board.output();
    delay(20);
    TEST_ASSERT_EQUAL(HIGH, digitalRead(X5));

    yy6 = 0;
    board.output();
    delay(20);
    TEST_ASSERT_EQUAL(HIGH, digitalRead(X6));

    yy7 = 0;
    board.output();
    delay(20);
    TEST_ASSERT_EQUAL(HIGH, digitalRead(X7));

    yy8 = 0;
    board.output();
    delay(20);
    TEST_ASSERT_EQUAL(HIGH, digitalRead(X8));
    yy9 = 0;
    board.output();
    delay(20);
    TEST_ASSERT_EQUAL(HIGH, digitalRead(X9));
    yy10 = 0;
    board.output();
    delay(20);
    TEST_ASSERT_EQUAL(HIGH, digitalRead(X10));
    yy11 = 0;
    board.output();
    delay(20);
    TEST_ASSERT_EQUAL(HIGH, digitalRead(X11));
    yy12 = 0;
    board.output();
    delay(20);
    TEST_ASSERT_EQUAL(HIGH, digitalRead(X12));
    yy13 = 0;
    board.output();
    delay(20);
    TEST_ASSERT_EQUAL(HIGH, digitalRead(X13));
    yy14 = 0;
    board.output();
    delay(20);
    TEST_ASSERT_EQUAL(HIGH, digitalRead(X14));
    yy15 = 0;
    board.output();
    delay(20);
    TEST_ASSERT_EQUAL(HIGH, digitalRead(X15));
    yy16 = 0;
    board.output();
    delay(20);
    TEST_ASSERT_EQUAL(HIGH, digitalRead(X16));
}
void test_axy()
{
    ya1 = 1000;
    ya2 = 1000;
    board.output();
    board.input();
    TEST_ASSERT_INT32_WITHIN(50, 2000, xa1);
    TEST_ASSERT_INT32_WITHIN(50, 2000, xa2);
    TEST_ASSERT_INT32_WITHIN(50, 2000, xa3);
    TEST_ASSERT_INT32_WITHIN(50, 2000, xa4);
    TEST_ASSERT_INT32_WITHIN(50, 2000, xa5);
    TEST_ASSERT_INT32_WITHIN(50, 2000, xa6);
    TEST_ASSERT_INT32_WITHIN(50, 2000, xa7);
    TEST_ASSERT_INT32_WITHIN(50, 2000, xa8);
    TEST_ASSERT_INT32_WITHIN(50, 2000, xa9);
    TEST_ASSERT_INT32_WITHIN(50, 2000, xa10);
}
#endif