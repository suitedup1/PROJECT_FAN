#pragma once
/*
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
*/
void pir_ISR();
void joytick_ISR();
void button_ISR();
void setinterrupt(int pir,int joystick_button,void (*pir_ISR)(),void (*joystick_ISR)());
void intitialise_devices(int motor,int servo,int buzzer);
void displaytime();
void fan_on(int motor);
void fan_off(int motor);
void mode_switch();
void oscillate();
void custom_dir();