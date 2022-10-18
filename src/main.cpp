#include "main.h"
#include <Arduino.h>
#include <TaskManager.h>

void blink()
{
  digitalWrite(!digitalRead(PinLED1));
}

void setup()
{
  pinMode(PinLED1, OUTPUT);
  taskManager.scheduleFixedRate(1000, blink);
}

void loop()
{
  taskManager.runLoop();
}
