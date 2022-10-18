#include "main.h"
#include <Arduino.h>
#include <TaskManager.h>

HardwareSerial Serial5(PD2, PC12);

void blink()
{
  digitalWrite(PB4, !digitalRead(PB4));
  // Serial.println("turn");
}

void setup()
{
  pinMode(PB4, OUTPUT);
  taskManager.scheduleFixedRate(1000, blink);
  Serial.begin(115200);
  Serial5.begin(9600);
}

void loop()
{
  taskManager.runLoop();
  if (Serial.available())
  {                               // If anything comes in Serial (USB),
    Serial5.write(Serial.read()); // read it and send it out Serial1 (pins 0 & 1)
  }
  if (Serial5.available())
  {                               // If anything comes in Serial1 (pins 0 & 1)
    Serial.write(Serial5.read()); // read it and send it out Serial (USB)
  }
}
