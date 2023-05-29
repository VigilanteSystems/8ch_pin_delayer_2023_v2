// ***************************************************************************
// 8 channel pin signal(HIGH) delay(er)
// - by Philipp Rauch - VigilanteSystems - opensource - 23.03.2023
// ***************************************************************************
// It delays signals from 8 channel parallel port signals to relays
// to avoid toggling relays at system reboot/bootup etc.

// 8CH_PIN_DELAYER_2023_v4

#include <Arduino.h>
#include <LowPower.h>

// Pins for Arduino Mini Pro 5V 16MHz
const byte inPins[] = {10, 11, 12, 13, A0, A1, A2, A3};
const byte outPins[] = {2, 3, 4, 5, 6, 7, 8, 9};
unsigned long startMillis = millis();

void setup()
{
  // Set input/output pins
  for (int i = 0; i < 8; i++)
  {
    pinMode(inPins[i], INPUT);
    pinMode(outPins[i], OUTPUT);
    digitalWrite(outPins[i], LOW);
  }
  startMillis = millis();
  while (millis() - startMillis < 4000)
  {
    // do nothing, just wait 4000 ms
  }
}

void loop()
{
  // Put the Arduino into low-power standby mode for 4 second
  LowPower.powerStandby(SLEEP_4S, ADC_OFF, BOD_OFF);
  startMillis = millis();
  while (millis() - startMillis < 500)
  {
    // do nothing, just wait  500 ms to wake up
  }
  // Read input pins and set corresponding output pins
  for (int i = 0; i < 8; i++)
  {
    digitalWrite(outPins[i], digitalRead(inPins[i]));
  }
}
