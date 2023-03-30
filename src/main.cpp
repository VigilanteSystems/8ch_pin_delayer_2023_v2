// ***************************************************************************
// 8 channel pin signal(HIGH) delay(er)
// - by Philipp Rauch - VigilanteSystems - opensource - 23.03.2023
// ***************************************************************************
// its to delay signals from 8 channel parallel port signals to relays
// to avoid toggling relays at system reboot/bootup etc ... bootup toggle...
// ***************************************************************************

// 8CH_PIN_DELAYER_2023_v2

// **** INCLUDES *****
#include <Arduino.h>

// pins for arduino mini pro 5V 16MHz
// [left side (digital) out, right side (half analog) in]
const byte inPins[8] = {10, 11, 12, 13, A0, A1, A2, A3};
const byte outPins[8] = {9, 8, 7, 6, 5, 4, 3, 2};
bool runOnce = true; // or what?

void setup()
{
  // // forDEBUG
  // Serial.begin(115200);

  // while (!Serial)
  // {
  // } // wait for serial port to connect. Needed for native USB port only

// set in/out pins (insgesamt 8 mal)
  for (int index = 0; index <= 7; index++) 
  {
    // set input/output pins
    pinMode(inPins[index], INPUT);
    pinMode(outPins[index], OUTPUT);
    // set all low, also this turns off PWM on the analog ports
    digitalWrite(inPins[index], LOW);
    digitalWrite(outPins[index], LOW);
    // Serial.println("*****"); // 10000000
  }
}

void loop()
{
  if (runOnce)
  {
    delay(4000);
    runOnce = false;
  }
  // Prüfe den Wert vom Zähler (insgesamt 8 mal)
  // we write first then read, to avoid, bootup togglesituation
  for (int index = 0; index <= 7; index++) // set in/out pins (insgesamt 8 mal)
  {
    if (digitalRead(inPins[index]) == LOW)
      digitalWrite(outPins[index], LOW);
    if (digitalRead(inPins[index]) == HIGH)
      digitalWrite(outPins[index], HIGH);
  }
}
