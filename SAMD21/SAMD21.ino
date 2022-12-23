/*
  This program reads PWM signal from RC receiver and emulates a HID gamepad.
  HID Project is used for HID emulation:
  https://github.com/NicoHood/HID/wiki/Gamepad-API
  Please install HID Project library before using this code.
*/

#include "HID-Project.h"


void setup() {

  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(A0),isr1,CHANGE);
  attachInterrupt(digitalPinToInterrupt(A1),isr2,CHANGE);
  // Sends a clean report to the host. This is important on any Arduino type.
  Gamepad.begin();
}

volatile unsigned long Time[2];
volatile unsigned int Value[2];
volatile bool ValChanged[2];
void loop() {


    // Move x/y Axis to a new position (16bit)
    if (ValChanged[0])
    {
      Gamepad.xAxis(Value[0]);
      Gamepad.write();
      ValChanged[0] = false;
    }

    if (ValChanged[1])
    {
      Gamepad.yAxis(Value[1]);
      Gamepad.write();
      ValChanged[1] = false;
    }
}

void isr1()
{
  if (digitalRead(A0)) Time[0] = micros();
  else
  {
    Value[0] = micros()-Time[0];
    ValChanged[0] = true;
  }
}


void isr2()
{
  if (digitalRead(A1)) Time[1] = micros();
  else 
  {
    Value[1] = micros()-Time[1];
    ValChanged[1] = true;
  }
}
