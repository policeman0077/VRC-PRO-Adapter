/* 
   This program is modified based on:
   https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode
   I deleted smoothing and the dalay for better response.
 */

#include <Joystick.h>
#include "AVRPort23.h"

#define CHAN1 D,0
#define _INT1 0
#define CHAN2 D,1
#define _INT2 1
#define CHAN3 D,3
#define _INT3 3
#define CHAN4 D,2
#define _INT4 2
#define RXLED B,0
#define TXLED D,5

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  0, 0,                 // Button Count, Hat Switch Count
  true, true, false,  // X, Y, Z
  true, true, false,  // Rx, Ry, Rz
  false, false,          // Rudder, Throttle
  false, false, false);    // Accelerator, Brake, Steering

void setup()
{
  portMode(CHAN1, INPUT, HIGH);
  portMode(CHAN2, INPUT, HIGH);
  portMode(CHAN3, INPUT, HIGH);
  portMode(CHAN4, INPUT, HIGH);
  portMode(RXLED, OUTPUT, LOW);
  portMode(TXLED, OUTPUT, LOW);
  
  Joystick.begin();
  Joystick.setXAxisRange(2250, 750);
  Joystick.setYAxisRange(2250, 750);
  Joystick.setRxAxisRange(2250, 750);
  Joystick.setRyAxisRange(2250, 750);
  
  attachInterrupt(_INT1, isr1, CHANGE);
  attachInterrupt(_INT2, isr2, CHANGE);
  attachInterrupt(_INT3, isr3, CHANGE);
  attachInterrupt(_INT4, isr4, CHANGE);
}

volatile unsigned long Time[4];
volatile unsigned int Value[4];
volatile bool ValChanged[4];


void loop()
{   
  if (ValChanged[0])
  {
    
    Joystick.setXAxis(Value[0]);
    ValChanged[0] = false;
  }

  if (ValChanged[1])
  {
    
    Joystick.setYAxis(Value[1]);
    ValChanged[1] = false;
  }
  
   if (ValChanged[2])
  { 
    Joystick.setRxAxis(Value[2]);
    ValChanged[2] = false;
  }
  
   if (ValChanged[3])
  {
    Joystick.setRyAxis(Value[3]);
    ValChanged[3] = false;
  }
  
\
}

void isr1()
{
  if (portRead(CHAN1)) Time[0] = micros();
  else
  {
    Value[0] = micros()-Time[0];
    ValChanged[0] = true;
  }
}

void isr2()
{
  if (portRead(CHAN2)) Time[1] = micros();
  else
  {
    Value[1] = micros()-Time[1];
    ValChanged[1] = true;
  }
}

void isr3()
{
  if (portRead(CHAN3)) Time[2] = micros();
  else
  {
    Value[2] = micros()-Time[2];
    ValChanged[2] = true;
  }
}

void isr4()
{
  if (portRead(CHAN4)) Time[3] = micros();
  else
  {
    Value[3] = micros()-Time[3];
    ValChanged[3] = true;
  }
}
