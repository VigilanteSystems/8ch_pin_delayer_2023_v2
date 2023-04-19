// ***************************************************************************
// 8 channel pin signal(HIGH) delay(er)
// - by Philipp Rauch - VigilanteSystems - opensource - 23.03.2023
// ***************************************************************************
// It delays signals from 8 channel parallel port signals to relays
// to avoid toggling relays at system reboot/bootup etc.

// 8CH_PIN_DELAYER_2023_v4

#include <Arduino.h>
#include <LowPower.h>
#include <digitalWriteFast.h>

// Pins for Arduino Mini Pro 5V 16MHz
const byte inPins[] = {10, 11, 12, 13, A0, A1, A2, A3};
const byte outPins[] = {9, 8, 7, 6, 5, 4, 3, 2};

void setup()
{
  // Set input/output pins
  for (int i = 0; i < 8; i++) 
  {
    pinMode(inPins[i], INPUT);
    pinMode(outPins[i], OUTPUT);
    digitalWrite(outPins[i], LOW);
  }

  // Wait for 4 seconds before starting to read input pins
  delay(4000);
}

void loop()
{
  // Read input pins and set corresponding output pins
  for (int i = 0; i < 8; i++)
  {
    digitalWrite(outPins[i], digitalReadFast(inPins[i]));
  }

  // Put the Arduino into low-power standby mode for 1 second
  LowPower.powerStandby(SLEEP_2S, ADC_OFF, BOD_OFF);
}
