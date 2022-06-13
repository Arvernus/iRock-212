/**
 * @file test_functions_Pins.cpp
 * @author Joscha Wagner (joscha@nebensound.com)
 * @brief Test for the Pins library
 *
 * Copyright (c) Nebensound GmbH 2021
 */
#include "Pins.h"
#include "unity.h"

using namespace Pins;

void test_function_RetrievePinATEMP(void)
{
  TEST_ASSERT_EQUAL_STRING("PinATEMP", Name(PinATEMP));
  TEST_ASSERT_EQUAL_STRING("ATEMP CPU-Temperature", Description(PinATEMP));
  TEST_ASSERT_EQUAL(AnalogInputPin, Type(PinATEMP));
  TEST_ASSERT_EQUAL_STRING("AnalogInputPin", TypeName(PinATEMP));
}

void test_function_RetrievePinPC10(void)
{
  TEST_ASSERT_EQUAL_STRING("PinPC10", Name(PinPC10));
  TEST_ASSERT_EQUAL_STRING("PC10", Description(PinPC10));
  TEST_ASSERT_EQUAL(DigitalInputPullUpPin, Type(PinPC10));
  TEST_ASSERT_EQUAL_STRING("DigitalInputPullUpPin", TypeName(PinPC10));
}

void test_function_InvalidPinId(void)
{
  TEST_ASSERT_EQUAL_STRING("NoPin", Name((PinId)255));
  TEST_ASSERT_EQUAL_STRING("Not a Pin", Description((PinId)255));
  TEST_ASSERT_EQUAL(NotAPin, Type((PinId)255));
  TEST_ASSERT_EQUAL_STRING("NotAPin", TypeName((PinId)255));
}

void test_function_InvalidIO(void)
{
  TEST_ASSERT_FALSE(ReadDigital(PinPA0));
  TEST_ASSERT_EQUAL_FLOAT(NAN, ReadAnalog(PinPA15));
  TEST_ASSERT_EQUAL_FLOAT(NAN, ReadAnalog(PinPB1));
  TEST_ASSERT_EQUAL_INT32(0l, ReadAnalogRaw(PinPA15));
}

void process()
{
  UNITY_BEGIN();
  Init();
  RUN_TEST(test_function_RetrievePinATEMP);
  RUN_TEST(test_function_RetrievePinPC10);
  RUN_TEST(test_function_InvalidPinId);
  RUN_TEST(test_function_InvalidIO);
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
