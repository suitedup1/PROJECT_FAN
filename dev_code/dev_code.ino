#include <LiquidCrystal_I2C.h>
#include <ESP32Servo.h>
#include "functions.h"
volatile bool pir_detected;
volatile bool button_detected;
volatile bool is_osci;
volatile bool device_on;
volatile bool is_fan_on;
volatile long current_time;
volatile long prev_time;

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
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);
}

void loop() {
  //update time
  
  
  custom_dir();
}