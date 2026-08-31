#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <Arduino.h>
#include "functions.h"

// statuses
volatile bool pir_detected = false;
volatile bool joystick_detected = false;
volatile bool button_detected = false;
volatile bool is_osci = false;
volatile bool device_on = false;
volatile bool is_fan_on = false;
// pins
int motor;
int pir;
int servo;
int joystick;
int buzzer;
// for interrupts
int joystick_button;
int reg_button;
Servo myservo;
// lcd init
LiquidCrystal_I2C lcd(0x3F, 16, 2);

// ISRs
void pir_ISR()
{
  pir_detected = true;
}
void joytick_ISR()
{
  joystick_detected = true;
}
void button_ISR()
{
  button_detected = true;
}
// independent processes


void setinterrupt(int pir,int joystick_button,void (*pir_ISR)(),void (*joystick_ISR)())
{
  attachInterrupt(digitalPinToInterrupt(pir), pir_ISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(joystick_button), pir_ISR, RISING);
}
void intitialise_devices(int motor,int servo,int buzzer)
{
  pinMode(motor, OUTPUT);
  myservo.attach(servo);
  pinMode(buzzer, OUTPUT);
}
  // no initialisation required for joystick
void displaytime()
{
  lcd.print("Turning on...");
}
// fan operation
void fan_on(int motor)
{
  digitalWrite(motor, HIGH);
}
void fan_off(int motor)
{
  digitalWrite(motor, HIGH);
}
// fan movement
void mode_switch()
{
  is_osci = !is_osci;
}
void oscillate()
{
  int ang = 90;
  while (is_osci)
  {
      while ( ang>0)
      {
        myservo.write(ang);
        ang--;
      }
      while ( ang<180)
      {
        myservo.write(ang);
        ang++;
      }
  }
  
}
void custom_dir()
{
  int value;
  int ang = 90;
  while(!is_osci)
  {
    value = analogRead(joystick);
    if (value > 600)
    {
      ang++;
      myservo.write(ang);
    }
    else if (value < 400)
    {
      ang--;
      myservo.write(ang);
    }
  }
}
void reset()
{
  fan_off();
  myservo.write(90);
  pir_detected = false;
 joystick_detected = false;
  button_detected = false;
  is_osci = false;
  device_on = false;
  is_fan_on = false;
}