#include "functions.h"
void setup() {
  // put your setup code here, to run once:
  void intitialise_devices(int motor,int servo,int buzzer);
  void setinterrupt(int pir,int joystick_button,void (*pir_ISR)(),void (*joystick_ISR)());
}

void loop() {
  // put your main code here, to run repeatedly:
  displaytime();
  if (button_detected)
  {
    if (!device_on)
    {
      device_on = true;
      fan_on(motor);
    }
    else:
    {
      reset();
    }
  }
  else:
  {
    if (device_on)
    {
      if (joystick_detected)
      {
        mode_switch();
      }
      else if (!is_osci)
      {
        custom_dir();
      }
      else if (is_osci)
      {
        oscillate();
      }
    }
  }
}
