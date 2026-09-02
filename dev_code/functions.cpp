#include <LiquidCrystal_I2C.h>
#include <ESP32Servo.h>
#include "functions.h"
// ISRs
void ARDUINO_ISR_ATTR pir_ISR()
{
  pir_detected = true;
}
// check button
void check_button()
{
  button_detected = !digitalRead(button);
}
int mapangle()
{
  int val = analogRead(pot);
  int ang = map(val, 0, 4096, 0, 180);
  Serial.println(ang);
  return ang;
}
// independent processes


void setinterrupt()
{
  attachInterrupt(digitalPinToInterrupt(pir), pir_ISR, RISING);
}
void initialise_devices()
{
  
  // statuses
  pir_detected = false;
  button_detected = false;
  is_osci = false; //for testing
  device_on = false;
  is_fan_on = false;
  //servo timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);
  //timer
  last_trigger = 0;
  // pins
  motor1 = 33;
  motor2 = 32;
  pir = 1;
  servo = 18;
  pot = 34;
  // for interrupts
  button = 19;
  // lcd init
  LiquidCrystal_I2C lcd(0x3F, 16, 2);
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  myservo.attach(servo, 500, 2400);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  Serial.begin(115200);
  //pinMode(buzzer, OUTPUT);
}
  // no initialisation required for joystick
void display()
{
  lcd.print("???");
}
// fan operation
void fan_on()
{
  digitalWrite(motor1, HIGH);
  digitalWrite(motor2, LOW);
  Serial.println("spinning");
  is_fan_on = !is_fan_on;
}
void fan_off()
{
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, LOW);
  Serial.println("stopping");
  is_fan_on = !is_fan_on;
}
// fan movement
void mode_switch()
{
  is_osci = false;
}
void oscillate()
{
  Serial.println("in oscillating mode");
  int ang = 90;
  while (is_osci)
  {
      while ( ang>0)
      {
        myservo.write(ang);
        ang--;
        check_button();
        if (button_detected)
        {
          is_osci = false;
          button_detected = false;
          break;
        }
      }
      while ( ang<180)
      {
        myservo.write(ang);
        ang++;
        check_button();
        if (button_detected)
        {
          is_osci = false;
          button_detected = false;
          break;
        }
      }
      
  }
  delay(400);
  
}
void custom_dir()
{
  
  Serial.println("in custom dir");
  
  int value;
  int current_ang = 90;
  myservo.write(current_ang);
  
  while(!is_osci)//testing
  {
    int target = mapangle();
    Serial.println("Target:");
    Serial.println(target);
    to_target(current_ang, target);
    current_ang = mapangle();
    check_button();
    if (button_detected)
      {
        Serial.println("detected in custom dir");
        is_osci = true;
        button_detected = false;
        delay(400);
      }
  }
  
}
void to_target(int current_ang, int target)
{
  if (current_ang > target)
    {
      for (int i = current_ang; i > target; i--)
      {
        myservo.write(i);
        delay(15);
      }
    }
  else if (current_ang > target)
  {
    for (int i = current_ang; i < target; i++)
    {
      myservo.write(i);
      delay(15);
    }
  }
  else
  {
    Serial.println("at postion");
  }
}
void reset()
{
  fan_off();
  myservo.write(90);
  pir_detected = false;
  button_detected = false;
  is_osci = false;
  device_on = false;
  is_fan_on = false;
}