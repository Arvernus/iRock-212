/**
 * @file test_functions_Mapping.cpp
 * @author Joscha Wagner (joscha@nebensound.com)
 * @brief Test for the Mapping library
 *
 * Copyright (c) Nebensound GmbH 2021
 */
#include <PersistentStorage.h>
#include <unity.h>

char name[] = "test";
float input = 7.3;
float output = 0;

void test_function_read_write(void)
{
    Store::setup();
    Store::reset();
    Store::write(name, sizeof(input), (byte *)&input);
    Store::read(name, sizeof(output), (byte *)&output);
    TEST_ASSERT_EQUAL_FLOAT(input, output);
}

void test_function_delete(void)
{
    Store::setup();
    Store::reset();
    Store::delete_file(name);
}

void test_function_overflow(void)
{
    Store::setup();
    Store::reset();
    unsigned int count = EEPROM.length() / (sizeof(PersistentStorage) + sizeof(input)) + 1;
    for (size_t i = 0; i < count; i++)
    {
        Store::write(name, sizeof(input), (byte *)&input);
    }
    Store::read(name, sizeof(output), (byte *)&output);
    TEST_ASSERT_EQUAL_FLOAT(input, output);
}

void process()
{
    UNITY_BEGIN();
    RUN_TEST(test_function_read_write);
    RUN_TEST(test_function_delete);
    RUN_TEST(test_function_overflow);
    UNITY_END();
}
#ifdef ARDUINO
#include <Arduino.h>
void setup()
{
#ifdef LED_BUILTIN
    pinMode(LED_BUILTIN, OUTPUT);
#endif // LED1_EXISTS
    delay(2000);
    process();
}
void loop()
{
#ifdef LED_BUILTIN
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
#endif // LED1_EXISTS
}
#else
int main(int argc, char **argv)
{
    process();
    return 0;
}
#endif
