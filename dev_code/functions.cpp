#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <Arduino.h>

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
// statuses
volatile bool pir_detected = false;
volatile bool joystick_detected = false;
volatile bool is_osci = false;
volatile bool device_on = false;
volatile bool is_fan_on = false;
// pins
int STANDBY;
int IN1;
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
// independent processes
void setinterrupt(int pir,int joystick_button,void (*pir_ISR)(),void (*joystick_ISR)())
{
  attachInterrupt(digitalPinToInterrupt(pir), pir_ISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(joystick_button), pir_ISR, RISING);
}
void intitialise_devices(motor, servo, joystick, buzzer)
  pinMode(motor, OUTPUT);
  myservo.attach(servo);
  pinMode(buzzer, OUTPUT);
  // no initialisation required for joystick
void displaytime()
{
  lcd.print("Turning on...")
}
// fan operation
void fan_on(motor)
{
  digitalWrite(motor, HIGH);
}
void fan_off(motor)
{
  digitalWrite(motor, HIGH);
}
// fan movement
void mode_switch()
{
  is_osci = !is_osci;
}