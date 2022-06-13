/**
 * @file test_functions_Scale.cpp
 * @author Joscha Wagner (joscha@nebensound.com)
 * @brief Tests of the Module Scale
 *
 * Copyright (c) Nebensound GmbH 2021
 */
#include "Scale.h"
#include "unity.h"

void test_function_Scale_ul_to_float(void)
{
  TEST_ASSERT_EQUAL_FLOAT(0.0, Scale::Scale(123456ul, 0.0, 0.0));
  TEST_ASSERT_EQUAL_FLOAT(234567.0, Scale::Scale(234567ul, 1.0, 0.0));
  TEST_ASSERT_EQUAL_FLOAT(172839.0, Scale::Scale(345678ul, 0.5, 0.0));
  TEST_ASSERT_EQUAL_FLOAT(228000.0, Scale::Scale(456789ul, 0.5, -789.0));
}

void test_function_Scale_float_to_float(void)
{
  TEST_ASSERT_EQUAL_FLOAT(0.0, Scale::Scale(5278963.67886, 0.0, 0.0));
  TEST_ASSERT_EQUAL_FLOAT(234567.0, Scale::Scale(234567.0, 1.0, 0.0));
  TEST_ASSERT_EQUAL_FLOAT(172839.0, Scale::Scale(345678.0, 0.5, 0.0));
  TEST_ASSERT_EQUAL_FLOAT(12001.0, Scale::Scale(6789.5, 2, -789.0));
}

void test_function_ScaleBack_float_to_ul(void)
{
  TEST_ASSERT_EQUAL_UINT32(0ul, Scale::ScaleBack<uint32_t>(123456.0, 0.0, 0.0));
  TEST_ASSERT_EQUAL_UINT32(234567ul, Scale::ScaleBack<uint32_t>(234567.0, 1.0, 0.0));
  TEST_ASSERT_EQUAL_UINT32(345678ul, Scale::ScaleBack<uint32_t>(172839.0, 0.5, 0.0));
  TEST_ASSERT_EQUAL_UINT32(456789ul, Scale::ScaleBack<uint32_t>(228000.0, 0.5, -789.0));
}

void test_function_ScaleBack_float_to_float(void)
{
  TEST_ASSERT_EQUAL_FLOAT(0, Scale::ScaleBack(123456.0, 0.0, 0.0));
  TEST_ASSERT_EQUAL_FLOAT(234567.0, Scale::ScaleBack(234567.0, 1.0, 0.0));
  TEST_ASSERT_EQUAL_FLOAT(345678.0, Scale::ScaleBack(172839.0, 0.5, 0.0));
  TEST_ASSERT_EQUAL_FLOAT(6789.5, Scale::ScaleBack(12001.0, 2, -789.0));
}

void process()
{
  UNITY_BEGIN();
  RUN_TEST(test_function_Scale_ul_to_float);
  RUN_TEST(test_function_Scale_float_to_float);
  RUN_TEST(test_function_ScaleBack_float_to_ul);
  RUN_TEST(test_function_ScaleBack_float_to_float);
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
