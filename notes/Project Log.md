\#Project Log



###### Setting up ESP8266:

\- install correct driver from https://www.silabs.com/software-and-tools/usb-to-uart-bridge-vcp-drivers?tab=downloads

\- ensure that the usb cable being used is appropriate to transmit data

\- setup arduino IDE with the board with tutorial from lastminuteengineers



##### **using pir sensor:**

\- senses movement, then writes HIGH to a data pin before changing it back to low

\- use interrupts

so i simply set motion to true then set it back to false once ive dealt with it in main program

NOTE 2:

60s startup time

had to power it using 3.3v v by using a different pin on the board

https://techgurka.blogspot.com/2013/05/cheap-pyroelectric-infrared-pir-motion.html

having major issues with it being unrealiable and just activating periodically

baud rate for esp8266 is 115200

changing sensitivity of sensor, didn't do anything

changing delay for sensor

Turns out my code is of a poor quality



###### **NOTES FOR PROGRAMMING PRINCIPLES EMBEDDED SYSTEMS #1**

interrupts are used because you dont need to constantly check the current value of a pin. when a change is detected, an event is triggered



for Arduino and ESP32, use attachInterrupt() function to program interrupts

parameters are: GPIO \[use digitalPinToInterrupt(pin)], the ISR \[notes on that below], and the mode:

* LOW: to trigger the interrupt whenever the pin is LOW;
* HIGH: to trigger the interrupt whenever the pin is HIGH;
* CHANGE: to trigger the interrupt whenever the pin changes value – for example, from HIGH to LOW or LOW to HIGH;
* FALLING: for when the pin goes from HIGH to LOW;
* RISING: to trigger when the pin goes from LOW to HIGH.





**KEY NOTES FOR ISRs**

Another important thing about ISRs is that you should keep their code as fast and simple as possible and avoid things like complex operations, writing to the Serial Monitor, or using delay(). Instead, you should use a flag or counter to indicate that the interrupt happened, and then handle whatever you need to do in the main code or loop() section.



Variables that are used inside ISRs and throughout the code should preferably be volatile. This prevents the compiler from caching values in registers (and skipping memory access), so reads/writes always access the actual memory location and reflect unexpected changes caused by the interrupt.



**USING TIMERS**

We don't use a delay function because it blocks code and doesn't allow anything else to happen, making simultaneous action impossible



the *millis()* function

This function returns the number of ms passed since the start of the program. It's useful because it allows us to check how much time has passed since a certain event without blocking the code

**etiquette:**

* use unsigned long for variables that hold time
* use constants for variables that don't change
* when using timers, save moments in time when you are causing an event to happen by setting previousMillis = currentMillis
* use a bool variable to have a status on whether teh timer is currently running \[activated in ISR]







Had to replace 4 digit 7 segment display because it was common anode and I'm not inverting that tutorial. 

###### **Using LCD screen...**



First find the address using the code supplied by lastminuteengineers

address: 0x3F



use LiquidCrystal\_I2C library install on Arduino ide



include library

create an object of the LiquidCrystal I2C class with code below

// enter the I2C address and the dimensions of your LCD here

LiquidCrystal\_I2C lcd(address, width, height);





lcd.init() //intialises interface to lcd

lcd.clear() //erases screen and moves cursor to top left corner

lcd.backlight() //turns on backlight

lcd.setcursor(2,0) moves cursor to row 1, col 3

the cursor tells the lcd where to place new text on the screen

lcd.print(text) //self explanatory

lcd.blink() and lcd.noBlink() //turn on and off a blinking cursor



for a message longer than 16 characters, you can scroll the display

void loop() {

&#x20; lcd.scrollDisplayLeft();   // scroll everything to the left by one position

&#x20; delay(300);                // small delay for visible scrolling speed

}



###### **What actually is Vin?**



note:

GPIO4 and GPIO5 are the most safe to use GPIOs if you want to operate relays.



Vin can be used to power the board, but it has been shown to provide output

according to this comment on circuit digest:



"The answer to your query is both yes and no. Yes for that because you say that you connect your NodeMCU with your Laptop/PC through USB cable, where the voltage of the USB port out is 5.0V, which you measured, shown 4.9V, you can use this power as input for nodemcu and as well as the other sensors attached with it. But on the other side, no because the USB port has very low current rating i.e., max by 500mA. If you connect NodeMCU and some kind of sensor to power up both of these, there might be maximum chance of your PC USB port get damaged"



In short lets not risk frying my laptop from now on.



However, we have a problem.

The LCD, PIR sensor, and Joystick all operate at 5v,  with the DC motor needing 6v ideally. However I only have a 9V battery that is NOT researched





|**Battery** |**Voltage \[per cell]**|**Discharge rate**|**capacity range**|**Advantages**|
|-|-|-|-|-|
|Li-Ion|3.6-3.7V|High|High|High energy density, long life cycle|
|Li-Po|3.7V|Very high|medium-high|light, high discharge, flexible shape|
|NiMH|1.2V|Medium|low-medium|safe,inexpensive|





Shape: best is Lipo with flat soft pouches

"drones, small robots, and robotic arms frequently like LiPo since it is the sole material that allows for extremely flexible sizing."

Slight power issue here.



LiPo offers the highest discharge rate, making it ideal for robotics like racing bots, RC robots, and quadcopters that need quick power bursts.



Li-ion: Best overall for multi-hour robotic work cycles.

NiMH: Best for simple, low-cost robotics.



Of all the lithium chemistries, LiFePO4, a subcategory of Li-ion, is the safest.





The maximum level of protection and BMS oversight are necessary for standard LiPo packs.





Although NiMH is stable, it lacks the power required for sophisticated robotics.

safety issues:



Why BMS \[battery management systemSo i] matters:



Li-ion/LiPo packs of any size run the risk of overcharging or deep discharging, possibly letting it catch fire



Safety is greatly increased by a basic PCB protection board.







a voltage regulator as 3 pins:

* output
* input
* ground



input is from the original source

ground is just connected to gnd

output spits out regulated voltage



For a DC motor i need to use a motor driver l298n

for the joystick a 5v input is still required

Okay if i can order some voltage regulators they should solves the power issue

nevermind they are extremely inefficient and waste power as heat 

But they do provide a stable voltage and low noise t really care about that. 



switching regulators are more expensive



options are buck converters or voltage regulator



Batteries:

* Lithium-ion \[Li-in]
* Lithium-polymer \[Li-P]
* Nickel metal hydride \[NiMH]



