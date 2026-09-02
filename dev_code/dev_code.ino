#include <LiquidCrystal_I2C.h>
#include <ESP32Servo.h>
#include "functions.h"
volatile bool pir_detected;
volatile bool button_detected;
volatile bool is_osci;
volatile bool device_on;
volatile bool is_fan_on;
volatile long now;
volatile long last_trigger;
ESP32PWM pwm;
// pins
int motor1;
int motor2;
int pir;
int servo;
int pot;
int buzzer;
// for interrupts
int button;
Servo myservo;
LiquidCrystal_I2C lcd(0x3F, 16, 2);
void setup() {
  
  initialise_devices();
  setinterrupt();

}

void loop() {
  //update time
  long now = millis();
  check_button();
  if (button_detected)
  {
    Serial.println("detected");
    is_osci = !is_osci;
  }
  if (is_osci)
  {
    oscillate();
  }
  else if (!is_osci)
  {
    custom_dir();
  }
  if (pir_detected && now )
  {
    pir_detected = false;
  }
}