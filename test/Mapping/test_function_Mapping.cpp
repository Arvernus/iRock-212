/**
 * @file test_functions_Mapping.cpp
 * @author Joscha Wagner (joscha@nebensound.com)
 * @brief Test for the Mapping library
 *
 * Copyright (c) Nebensound GmbH 2021
 */
#include <Mapping.h>
#include <MappingTable.h>
#include <Pins.h>
#include <Signals.h>
#include <unity.h>

using namespace Mapping;

void test_function_Variant1(void) {
  Init();
  TEST_ASSERT_EQUAL_INT(0, SwitchMap(2));
  TEST_ASSERT_EQUAL_INT(PinPA0, GetPin(AD_Charge, 0));
  for (int n = 1; n < MaxPinsPerSignal; n++) {
    TEST_ASSERT_EQUAL_INT(NoPin, GetPin(AD_Charge, n));
  }
  TEST_ASSERT_EQUAL_INT(1, NoOfPins(AD_Charge));
  TEST_ASSERT_EQUAL_INT(PinPA1, GetPin(AD_Load, 0));
  TEST_ASSERT_EQUAL_INT(1, NoOfPins(AD_Load));
  TEST_ASSERT_EQUAL_STRING("PinPA1", Pins::Name(GetPin(AD_Load, 0)));
  TEST_ASSERT_EQUAL_INT(InvalidVariant, AddPin(AD_Charge, PinPA3));
  TEST_ASSERT_EQUAL_INT(InvalidVariant, RemovePin(AD_Charge, PinPA3));
  TEST_ASSERT_EQUAL_INT(InvalidVariant, ClearSignal(AD_Charge));
}

void test_function_Variant0Add(void) {
  Init();
  TEST_ASSERT_EQUAL_INT(4, NoOfAllMappings);
  TEST_ASSERT_EQUAL_INT(Ok, SwitchMap(0));
  TEST_ASSERT_EQUAL_STRING("AD_Charge", Signals::Name(AD_Charge));
  TEST_ASSERT_EQUAL_INT(PinPA0, GetPin(AD_Charge, 0));
  TEST_ASSERT_EQUAL_INT(NoPin, GetPin(AD_Charge, 1));
  TEST_ASSERT_EQUAL_INT(1, NoOfPins(AD_Charge));
  TEST_ASSERT_EQUAL_STRING("PinPA0", Pins::Name(GetPin(AD_Charge, 0)));
  TEST_ASSERT_EQUAL_INT(AlreadyMapped, AddPin(AD_Charge, PinPA0));
  TEST_ASSERT_EQUAL_INT(Ok, AddPin(AD_Charge, PinPA1));
  TEST_ASSERT_EQUAL_INT(AlreadyMapped, AddPin(AD_Charge, PinPA1));
  TEST_ASSERT_EQUAL_INT(Ok, AddPin(AD_Charge, PinPA2));
  TEST_ASSERT_EQUAL_INT(Ok, AddPin(AD_Charge, PinPA3));
  TEST_ASSERT_EQUAL_INT(Ok, AddPin(AD_Charge, PinPA4));
  TEST_ASSERT_EQUAL_INT(TooManyPins, AddPin(AD_Charge, PinPA5));
  TEST_ASSERT_EQUAL_INT(InvalidSignal, AddPin(NoSignal, PinPA6));
  for (byte n = 4; n < MaxDynamicMappings; n++) {
    int Result = AddPin((Signals::SignalId)(n + 1), (Pins::PinId)(n + 1));
    if (Result != Ok) {
      char Msg[40];
      sprintf(Msg, "AddPin(%d, %d) = %d", n + 1, n + 1, Result);
      TEST_FAIL_MESSAGE(Msg);
    }
  }
  TEST_ASSERT_EQUAL_INT(TooManyMappings, AddPin(AD_Load, PinPA3));
}

void test_function_Variant0Remove(void) {
  Init();
  TEST_ASSERT_EQUAL_INT(Ok, SwitchMap(0));
  TEST_ASSERT_EQUAL_INT(NoPin, GetPin(AD_Charge, 1));
  TEST_ASSERT_EQUAL_INT(1, NoOfPins(AD_Charge));
  TEST_ASSERT_EQUAL_INT(Ok, AddPin(AD_Charge, PinPA1));
  TEST_ASSERT_EQUAL_INT(Ok, AddPin(AD_Charge, PinPA2));
  TEST_ASSERT_EQUAL_INT(Ok, AddPin(AD_Charge, PinPA3));
  TEST_ASSERT_EQUAL_INT(Ok, AddPin(AD_Charge, PinPA4));
  TEST_ASSERT_EQUAL_INT(TooManyPins, AddPin(AD_Charge, PinPA5));
  TEST_ASSERT_EQUAL_INT(5, NoOfPins(AD_Charge));
  TEST_ASSERT_EQUAL_INT(PinNotMapped, RemovePin(AD_Charge, PinPA5));
  TEST_ASSERT_EQUAL_INT(5, NoOfPins(AD_Charge));
  TEST_ASSERT_EQUAL_INT(Ok, RemovePin(AD_Charge, PinPA2));
  TEST_ASSERT_EQUAL_INT(4, NoOfPins(AD_Charge));
  TEST_ASSERT_EQUAL_INT(PinPA0, GetPin(AD_Charge, 0));
  TEST_ASSERT_EQUAL_INT(PinPA1, GetPin(AD_Charge, 1));
  TEST_ASSERT_EQUAL_INT(PinPA3, GetPin(AD_Charge, 2));
  TEST_ASSERT_EQUAL_INT(PinPA4, GetPin(AD_Charge, 3));
  TEST_ASSERT_EQUAL_INT(NoPin, GetPin(AD_Charge, 4));
  TEST_ASSERT_EQUAL_INT(NoPin, GetPin(AD_Charge, 5));
}

void test_function_Variant0Clear(void) {
  Init();
  TEST_ASSERT_EQUAL_INT(Ok, SwitchMap(0));
  TEST_ASSERT_EQUAL_INT(NoPin, GetPin(AD_Charge, 1));
  TEST_ASSERT_EQUAL_INT(1, NoOfPins(AD_Charge));
  TEST_ASSERT_EQUAL_INT(Ok, AddPin(AD_Charge, PinPA1));
  TEST_ASSERT_EQUAL_INT(Ok, AddPin(AD_Charge, PinPA2));
  TEST_ASSERT_EQUAL_INT(Ok, AddPin(AD_Charge, PinPA3));
  TEST_ASSERT_EQUAL_INT(Ok, AddPin(AD_Charge, PinPA4));
  TEST_ASSERT_EQUAL_INT(Ok, ClearSignal(AD_Charge));
  TEST_ASSERT_EQUAL_INT(1, NoOfPins(AD_Charge));
  TEST_ASSERT_EQUAL_INT(PinPA0, GetPin(AD_Charge, 0));
  TEST_ASSERT_EQUAL_INT(NoPin, GetPin(AD_Charge, 1));
  TEST_ASSERT_EQUAL_INT(NoPin, GetPin(AD_Charge, 2));
  TEST_ASSERT_EQUAL_INT(NoPin, GetPin(AD_Charge, 3));
  TEST_ASSERT_EQUAL_INT(NoPin, GetPin(AD_Charge, 4));
  TEST_ASSERT_EQUAL_INT(NoPin, GetPin(AD_Charge, 5));
}

void test_function_Variant0ClrAll(void) {
  Init();
  TEST_ASSERT_EQUAL_INT(Ok, SwitchMap(0));
  TEST_ASSERT_EQUAL_INT(NoPin, GetPin(AD_Load, 1));
  TEST_ASSERT_EQUAL_INT(1, NoOfPins(AD_Load));
  TEST_ASSERT_EQUAL_INT(AlreadyMapped, AddPin(AD_Load, PinPA1));
  TEST_ASSERT_EQUAL_INT(Ok, AddPin(AD_Load, PinPA2));
  TEST_ASSERT_EQUAL_INT(Ok, AddPin(AD_Load, PinPA3));
  TEST_ASSERT_EQUAL_INT(Ok, AddPin(AD_Load, PinPA4));
  TEST_ASSERT_EQUAL_INT(Ok, AddPin(AD_Charge, PinPA5));
  TEST_ASSERT_EQUAL_INT(Ok, AddPin(AD_Charge, PinPA6));
  TEST_ASSERT_EQUAL_INT(Ok, AddPin(AD_Charge, PinPA7));
  TEST_ASSERT_EQUAL_INT(Ok, ClearMap());
  TEST_ASSERT_EQUAL_INT(1, NoOfPins(AD_Load));
  TEST_ASSERT_EQUAL_INT(PinPA1, GetPin(AD_Load, 0));
  TEST_ASSERT_EQUAL_INT(NoPin, GetPin(AD_Load, 1));
  TEST_ASSERT_EQUAL_INT(NoPin, GetPin(AD_Load, 2));
  TEST_ASSERT_EQUAL_INT(NoPin, GetPin(AD_Load, 3));
  TEST_ASSERT_EQUAL_INT(NoPin, GetPin(AD_Load, 4));
  TEST_ASSERT_EQUAL_INT(NoPin, GetPin(AD_Load, 5));
  TEST_ASSERT_EQUAL_INT(PinPA0, GetPin(AD_Charge, 0));
  TEST_ASSERT_EQUAL_INT(NoPin, GetPin(AD_Charge, 1));
  TEST_ASSERT_EQUAL_INT(NoPin, GetPin(AD_Charge, 2));
  TEST_ASSERT_EQUAL_INT(NoPin, GetPin(AD_Charge, 3));
  TEST_ASSERT_EQUAL_INT(NoPin, GetPin(AD_Charge, 4));
  TEST_ASSERT_EQUAL_INT(NoPin, GetPin(AD_Charge, 5));
}

void test_function_Variant0Copy(void) {
  Init();
  TEST_ASSERT_EQUAL_INT(Ok, SwitchMap(0));
  TEST_ASSERT_EQUAL_INT(NoPin, GetPin(AD_Load, 1));
  TEST_ASSERT_EQUAL_INT(1, NoOfPins(AD_Load));
  TEST_ASSERT_EQUAL_INT(AlreadyMapped, AddPin(AD_Load, PinPA1));
  TEST_ASSERT_EQUAL_INT(Ok, AddPin(AD_Load, PinPA2));
  TEST_ASSERT_EQUAL_INT(Ok, AddPin(AD_Load, PinPA3));
  TEST_ASSERT_EQUAL_INT(Ok, AddPin(AD_Load, PinPA4));
  TEST_ASSERT_EQUAL_INT(Ok, AddPin(AD_Charge, PinPA5));
  TEST_ASSERT_EQUAL_INT(Ok, AddPin(AD_Charge, PinPA6));
  TEST_ASSERT_EQUAL_INT(Ok, AddPin(AD_Charge, PinPA7));
  TEST_ASSERT_EQUAL_INT(Ok, CopyMap(1));
  TEST_ASSERT_EQUAL_INT(3, NoOfPins(AD_Load));
  TEST_ASSERT_EQUAL_INT(PinPA1, GetPin(AD_Load, 0));
  TEST_ASSERT_EQUAL_INT(PinPA2, GetPin(AD_Load, 1));
  TEST_ASSERT_EQUAL_INT(PinPA3, GetPin(AD_Load, 2));
  TEST_ASSERT_EQUAL_INT(NoPin, GetPin(AD_Load, 3));
  TEST_ASSERT_EQUAL_INT(NoPin, GetPin(AD_Load, 4));
  TEST_ASSERT_EQUAL_INT(NoPin, GetPin(AD_Load, 5));
  TEST_ASSERT_EQUAL_INT(PinPA0, GetPin(AD_Charge, 0));
  TEST_ASSERT_EQUAL_INT(NoPin, GetPin(AD_Charge, 1));
  TEST_ASSERT_EQUAL_INT(NoPin, GetPin(AD_Charge, 2));
  TEST_ASSERT_EQUAL_INT(NoPin, GetPin(AD_Charge, 3));
  TEST_ASSERT_EQUAL_INT(NoPin, GetPin(AD_Charge, 4));
  TEST_ASSERT_EQUAL_INT(NoPin, GetPin(AD_Charge, 5));
}

void test_function_Variant0List(void) {
  Init();
  TEST_ASSERT_EQUAL_INT(Ok, SwitchMap(0));
  TEST_ASSERT_EQUAL_INT(0, NoOfMappings(0));
  TEST_ASSERT_EQUAL_INT(2, NoOfMappings(1));
  TEST_ASSERT_EQUAL_INT(0, NoOfMappings(2));
  TEST_ASSERT_EQUAL_INT(Ok, CopyMap(1));
  TEST_ASSERT_EQUAL_INT(2, NoOfMappings(0));
  TEST_ASSERT_EQUAL_INT(AD_Load, MappedSignal(0, 0));
  TEST_ASSERT_EQUAL_INT(PinPA2, MappedPin(0, 0));
  TEST_ASSERT_EQUAL_INT(AD_Load, MappedSignal(0, 1));
  TEST_ASSERT_EQUAL_INT(PinPA3, MappedPin(0, 1));
  TEST_ASSERT_EQUAL_INT(NoSignal, MappedSignal(0, 2));
  TEST_ASSERT_EQUAL_INT(NoPin, MappedPin(0, 2));
  TEST_ASSERT_EQUAL_INT(2, NoOfMappings(1));
  TEST_ASSERT_EQUAL_INT(AD_Load, MappedSignal(1, 0));
  TEST_ASSERT_EQUAL_INT(PinPA2, MappedPin(1, 0));
  TEST_ASSERT_EQUAL_INT(AD_Load, MappedSignal(1, 1));
  TEST_ASSERT_EQUAL_INT(PinPA3, MappedPin(1, 1));
  TEST_ASSERT_EQUAL_INT(NoSignal, MappedSignal(1, 2));
  TEST_ASSERT_EQUAL_INT(NoPin, MappedPin(1, 2));
}

void process() {
  UNITY_BEGIN();
  RUN_TEST(test_function_Variant1);
  RUN_TEST(test_function_Variant0Add);
  RUN_TEST(test_function_Variant0Remove);
  RUN_TEST(test_function_Variant0Clear);
  RUN_TEST(test_function_Variant0ClrAll);
  RUN_TEST(test_function_Variant0Copy);
  RUN_TEST(test_function_Variant0List);
  UNITY_END();
}
#ifdef ARDUINO
#include <Arduino.h>
void setup() {
#ifdef LED_BUILTIN
  pinMode(LED_BUILTIN, OUTPUT);
#endif // LED1_EXISTS
  delay(2000);
  process();
}
void loop() {
#ifdef LED_BUILTIN
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
#endif // LED1_EXISTS
}
#else
int main(int argc, char **argv) {
  process();
  return 0;
}
#endif
