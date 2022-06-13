/**
 * @file test_functions_Signals.cpp
 * @author Joscha Wagner (joscha@nebensound.com)
 * @brief Methods to deal with Signals
 *
 * Copyright (c) Nebensound GmbH 2021
 */
#include "Signals.h"
#include "unity.h"

using namespace Signals;

void test_function_RetrieveAD_Charge(void) {
  TEST_ASSERT_EQUAL_STRING("AD_Charge", Name(AD_Charge));
  TEST_ASSERT_EQUAL_STRING("Current the battery is getting charged with", Description(AD_Charge));
  TEST_ASSERT_EQUAL_STRING("A", Unit(AD_Charge));
  TEST_ASSERT_EQUAL(AnalogInput, Type(AD_Charge));
  TEST_ASSERT_EQUAL_STRING("AnalogInput", TypeName(AD_Charge));
}
void test_function_RetrieveLED1(void) {
  TEST_ASSERT_EQUAL_STRING("LED1", Name(LED1));
  TEST_ASSERT_EQUAL_STRING("Status LED 1 on PCB", Description(LED1));
  TEST_ASSERT_EQUAL_STRING("", Unit(LED1));
  TEST_ASSERT_EQUAL(DigitalOutput, Type(LED1));
  TEST_ASSERT_EQUAL_STRING("DigitalOutput", TypeName(LED1));
}

void test_function_InvalidSignalId(void) {
  TEST_ASSERT_EQUAL_STRING("NoSignal", Name((SignalId)255));
  TEST_ASSERT_EQUAL_STRING("Not a Signal", Description((SignalId)255));
  TEST_ASSERT_EQUAL_STRING("", Unit((SignalId)255));
  TEST_ASSERT_EQUAL(NotASignal, Type((SignalId)255));
  TEST_ASSERT_EQUAL_STRING("NotASignal", TypeName((SignalId)255));
}

void process() {
  UNITY_BEGIN();
  Init();
  RUN_TEST(test_function_RetrieveAD_Charge);
  RUN_TEST(test_function_RetrieveLED1);
  RUN_TEST(test_function_InvalidSignalId);
  UNITY_END();
}
#ifdef ARDUINO
#include <Arduino.h>
void setup() {
#ifdef LED1_EXISTS
  pinMode(LED1_PIN, LED1_TYPE);
#endif // LED1_EXISTS
  delay(2000);
  process();
}
void loop() {
#ifdef LED1_EXISTS
  digitalWrite(LED1_PIN, HIGH);
  delay(100);
  digitalWrite(LED1_PIN, LOW);
  delay(500);
#endif // LED1_EXISTS
}
#else
int main(int argc, char **argv) {
  process();
  return 0;
}
#endif
