#pragma once

// statuses
extern volatile bool pir_detected;
extern volatile bool button_detected;
extern volatile bool is_osci;
extern volatile bool device_on;
extern volatile bool is_fan_on;
// pins
extern int motor1;
extern int motor2;
extern int pir;
extern int servo;
extern int pot;
extern int buzzer;
extern volatile long current_time;
extern volatile long prev_time;

// for interrupts
extern int button;
extern Servo myservo;
// lcd init
extern LiquidCrystal_I2C lcd;
// lcd init

void ARDUINO_ISR_ATTR pir_ISR();
int mapangle();
bool is_pressed();
void setinterrupt();
void initialise_devices();
void displaytime();
void fan_on();
void fan_off();
void mode_switch();
void oscillate();
void custom_dir();
void reset();