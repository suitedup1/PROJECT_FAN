#include <LiquidCrystal_I2C.h>
#include <ESP32Servo.h>
#include "functions.h"
// ISRs
void ARDUINO_ISR_ATTR pir_ISR()
{
  pir_detected = true;
}
int mapangle()
{
  int val = analogRead(pot);
  int ang = map(val, 0, 4096, 0, 180);
  Serial.println(ang);
  return ang;
}
// independent processes
bool is_pressed()
{
  return digitalRead(button);
}

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
  
  Serial.println("in custom dir");
  
  int value;
  int ang = 120;
  myservo.write(ang);
  /*
  while(true)//testing
  {
    int ang2 = mapangle();
    Serial.println(ang2);
    if (ang2 >= ang)
    {
      for (int i = ang2; i >= ang; ang--)
      {
        myservo.write(i);
        delay(15);
      }
    }
    else 
    {
      for (int i = ang2; i <= ang; ang++)
      {
        myservo.write(i);
        delay(15);
      }
    }
    
  }
  */
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