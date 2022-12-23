/* 
   This program is modified based on:
   https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode
   I deleted smoothing and the dalay for better response.
   2ch version should have better report rate than 4ch version.
   If you use this program for playing VRC Pro, 2ch version should give you better result.
 */

#include <Joystick.h>
#include "AVRPort23.h"

#define CHAN1 D,0
#define _INT1 0
#define CHAN2 D,1
#define _INT2 1


Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  0, 0,                 // Button Count, Hat Switch Count
  true, true, false,  // X, Y, Z
  false, false, false,  // Rx, Ry, Rz
  false, false,          // Rudder, Throttle
  false, false, false);    // Accelerator, Brake, Steering

void setup()
{
  portMode(CHAN1, INPUT, HIGH);
  portMode(CHAN2, INPUT, HIGH);

  
  Joystick.begin();
  Joystick.setXAxisRange(2250, 750);
  Joystick.setYAxisRange(2250, 750);

  
  attachInterrupt(_INT1, isr1, CHANGE);
  attachInterrupt(_INT2, isr2, CHANGE);
  
}

volatile unsigned long Time[2];
volatile unsigned int Value[2];
volatile bool ValChanged[2];


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
