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
// #include <LowPower.h>


// pins for arduino mini pro 5V 16MHz
// [left side (digital) out, right side (half analog) in]
const byte inPins[8] = {10, 11, 12, 13, A0, A1, A2, A3};
const byte outPins[8] = {9, 8, 7, 6, 5, 4, 3, 2};
// bool pinStates[8] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW};

// const byte a = 0b00000001;
// const byte b = 0b00000010;
// const byte c = 0b00000100;
// const byte d = 0b00001000;
// const byte e = 0b00010000;
// const byte f = 0b00100000;
// const byte g = 0b01000000;
// const byte h = 0b10000000;

// time between write/reads see below
bool runOnce = true; // or what?

void setup()
{
  // // forDEBUG
  // Serial.begin(115200);

  // while (!Serial)
  // {
  // } // wait for serial port to connect. Needed for native USB port only

  // put your setup code here, to run once:
  for (int index = 0; index <= 7; index++) // set in/out pins (insgesamt 8 mal)
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

  // // Allow wake up pin to trigger interrupt on low.
  // attachInterrupt(0, wakeUp, LOW);

  // LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
  // // Disable external pin interrupt on wake up pin.

  // detachInterrupt(0);

  // // Do something here
  // delay(1000);s

  // Prüfe den Wert vom Zähler (insgesamt 8 mal)
  // we write first then read, to avoid, bootup togglesituation
  for (int index = 0; index <= 7; index++) // set in/out pins (insgesamt 8 mal)
  {
    if (digitalRead(inPins[index]) == HIGH)
      digitalWrite(outPins[index], HIGH);
    if (digitalRead(inPins[index]) == LOW)
      digitalWrite(outPins[index], LOW);
  }
  // byte input = 0;
  // if (digitalRead(PinA))
  //   input += 0b10000000;
  // if (digitalRead(PinB))
  //   input += 0b01000000;
  // if (digitalRead(PinC))
  //   input += 0b00100000;
  // if (digitalRead(PinD))
  //   input += 0b00010000;
  // if (digitalRead(PinE))
  //   input += 0b00001000;
  // if (digitalRead(PinF))
  //   input += 0b00000100;
  // if (digitalRead(PinG))
  //   input += 0b00000010;
  // if (digitalRead(PinH))
  //   input += 0b00000001;

  // switch (input)
  // {
  // case a:
  //   // Put code for pattern 'a' here
  //   Serial.println(input, BIN);
  //   break;

  // case b:
  //   // Put code for pattern 'b' here
  //   Serial.println(input);
  //   break;

  // case c:
  //   // Put code for pattern 'c' here
  //   break;

  // case d:
  //   // Put code for pattern 'd' here
  //   break;

  // case e:
  //   // Put code for pattern 'd' here
  //   break;

  // case f:
  //   // Put code for pattern 'd' here
  //   break;

  // case g:
  //   // Put code for pattern 'd' here
  //   Serial.println(input);
  //   break;

  // case h:
  //   // Put code for pattern 'd' here
  //   Serial.println(input);
  //   break;

  // default:
  //   // Error condition!  Did not match any of the patterns
  //   Serial.println(input);
  //   break;
  // }
}
