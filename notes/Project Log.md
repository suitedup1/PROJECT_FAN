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





|**Battery**|**Voltage \[per cell]**|**Discharge rate**|**capacity range**|**Advantages**|
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







Right so summary of yesterday:

* i wrote the pseudocode logic
* realised i might need structs to be more efficient but im not doing that this project
* soldered and fried 2 buck converters before realising that I inverted the voltage
* Corrected that
* I found a workaround to control the fan with just 1 pwm input - and pulling different pins to high and low by examining the library
* also you DECLARE in the header, DEFINE/ IMPLEMENT in the source file



used parameters when the variables are global - unnecessary

wiring up motor - forgot to connect ground

motor is constantly powered

now theres a wiring issue and nothing is moving but the function is running

battery is charged

none of the pins have let it work

the board is unusuable.

switching to esp32, freeing me up in gpio pin usage 





steps:

* wire up and test motor

motor pins: 32 and 33

forgot to connect gnd

pwm must have power, pulled up to 3.3v logic

* wire up and test joystick

joysticks runs at 5v, dont force it

using a regular button and a pot

wire was in wrong place

fan on and off states were not correct logic

should be changed to falling interrupt as button connect to gnd

i think i need to implement a timer because the button is stopping immediately

timer implemented but its not rrly working the way i inteded. the button is to act as a switch

nevermind again, interrups seem unsuitable for this project i am going to use polling

unpredictable behavior when using this button

testing if the button is actually always pressed so seeing if theres a low output

CHANGED TO SHORTER WIRES

testing potentiometer

forgot to check which pins were adc

using pin 34, input only adc1 pin

* wire up and test servo

pin 18 

turns out i did kind of need an interrupt - to break out of while loops

custom dir function nor eorking

faulty servo

must delay after button press to chekc properly

pir sensor

check pir in every loop

set now inside checker function

* wire up and test LCD



* write basic code logic and test
* write full code logic and tets
* measure dimensions
* design 3D printed housing, and mesh
* download fan design
* 3d print
* assemble




### **FORMATTED**

Setting up ESP8266:



\* Install the correct driver from \[https://www.silabs.com/software-and-tools/usb-to-uart-bridge-vcp-drivers?tab=downloads](https://www.silabs.com/software-and-tools/usb-to-uart-bridge-vcp-drivers?tab=downloads)

\* Ensure that the USB cable being used is appropriate for data transmission.

\* Set up the Arduino IDE for the board using the tutorial from Last Minute Engineers.



Using the PIR sensor:



\* It senses movement and then writes HIGH to a data pin before changing it back to LOW.

\* Use interrupts.

\* Set motion to true, then set it back to false once it has been processed in the main program.

NOTE 2:

\* 60-second startup time.

\* Had to power it using 3.3V by connecting to a different pin on the board: \[https://techgurka.blogspot.com/2013/05/cheap-pyroelectric-infrared-pir-motion.html](https://techgurka.blogspot.com/2013/05/cheap-pyroelectric-infrared-pir-motion.html)

\* Having major issues with it being unreliable and activating periodically.

\* The baud rate for the ESP8266 is 115200.

\* Changing the sensitivity of the sensor didn't do anything.

\* Changing the delay for the sensor didn't help either.

\* Turns out my code is of poor quality.



NOTES FOR PROGRAMMING PRINCIPLES EMBEDDED SYSTEMS #1



\* Interrupts are used because you don't need to constantly check the current value of a pin. When a change is detected, an event is triggered.

\* For Arduino and ESP32, use the `attachInterrupt()` function to program interrupts.

\* Parameters are:

1\. GPIO \[use `digitalPinToInterrupt(pin)`]

2\. The ISR \[notes below]

3\. The mode:

\* LOW: triggers the interrupt whenever the pin is LOW.

\* HIGH: triggers the interrupt whenever the pin is HIGH.

\* CHANGE: triggers the interrupt whenever the pin changes value (e.g., from HIGH to LOW or LOW to HIGH).

\* FALLING: triggers when the pin goes from HIGH to LOW.

\* RISING: triggers when the pin goes from LOW to HIGH.











KEY NOTES FOR ISRs:



\* Another important detail about ISRs is that you should keep their code as fast and simple as possible. Avoid complex operations, writing to the Serial Monitor, or using `delay()`. Instead, use a flag or counter to indicate that the interrupt happened, and then handle whatever you need to do in the main code or `loop()` section.

\* Variables that are used inside ISRs and throughout the rest of the code should preferably be declared as `volatile`. This prevents the compiler from caching values in registers (and skipping memory access), ensuring reads and writes always access the actual memory location to reflect unexpected changes caused by the interrupt.



USING TIMERS:



\* We don't use the `delay()` function because it blocks code execution and doesn't allow anything else to run, making simultaneous actions impossible.



The `millis()` function:



\* This function returns the number of milliseconds passed since the program started. It's useful because it allows us to check how much time has passed since a certain event without blocking the code execution.

Etiquette:

\* Use `unsigned long` for variables that hold time values.

\* Use constants for variables that don't change.

\* When using timers, save moments in time when causing an event to happen by setting `previousMillis = currentMillis`.

\* Use a `bool` variable to maintain status on whether the timer is currently running (activated in the ISR).



Had to replace the 4-digit 7-segment display because it was a common anode, and I'm not inverting that tutorial.

Switching to an LCD screen...



First, find the address using the code supplied by Last Minute Engineers.

Address: 0x3F



Use the LiquidCrystal\_I2C library installed on the Arduino IDE.



\* Include the library.

\* Create an object of the LiquidCrystal\_I2C class using the code below:

`// Enter the I2C address and the dimensions of your LCD here`

`LiquidCrystal\_I2C lcd(address, width, height);`

\* `lcd.init()` // Initializes interface to LCD

\* `lcd.clear()` // Erases screen and moves cursor to top-left corner

\* `lcd.backlight()` // Turns on backlight

\* `lcd.setCursor(2,0)` // Moves cursor to column 3, row 1

(The cursor tells the LCD where to place new text on the screen)

\* `lcd.print(text)` // Self-explanatory

\* `lcd.blink()` and `lcd.noBlink()` // Turn on and off a blinking cursor



For a message longer than 16 characters, you can scroll the display:



```cpp

void loop() {

&#x20; lcd.scrollDisplayLeft(); // Scroll everything to the left by one position

&#x20; delay(300);              // Small delay for visible scrolling speed

}



```



What actually is Vin?



Note:

GPIO4 and GPIO5 are the safest GPIOs to use if you want to operate relays.



Vin can be used to power the board, but it has also been shown to provide voltage output, according to this comment on Circuit Digest:



"The answer to your query is both yes and no. Yes, because if you connect your NodeMCU to your Laptop/PC through a USB cable, the output voltage of the USB port is 5.0V (which you measured at 4.9V). You can use this power as input for the NodeMCU as well as the other sensors attached to it. But on the other side, no, because the USB port has a very low current rating (max 500mA). If you connect the NodeMCU and several sensors to power them both up, there is a high chance your PC's USB port could get damaged."



In short, let's not risk frying my laptop from now on.



However, we have a problem.

The LCD, PIR sensor, and Joystick all operate at 5V, with the DC motor ideally needing 6V. However, I only have an unresearched 9V battery.



Battery comparison:



\* Li-Ion | Voltage: 3.6-3.7V per cell | Discharge rate: High | Capacity range: High | Advantages: High energy density, long life cycle

\* Li-Po | Voltage: 3.7V per cell | Discharge rate: Very high | Capacity range: Medium-High | Advantages: Light, high discharge, flexible shape

\* NiMH | Voltage: 1.2V per cell | Discharge rate: Medium | Capacity range: Low-Medium | Advantages: Safe, inexpensive



Shape: The best choice is LiPo due to its flat, soft pouches.

"Drones, small robots, and robotic arms frequently use LiPo since it is the sole material that allows for extremely flexible sizing."

Slight power issue here.



LiPo offers the highest discharge rate, making it ideal for robotics like racing bots, RC robots, and quadcopters that need quick power bursts.



Li-Ion: Best overall for multi-hour robotic work cycles.

NiMH: Best for simple, low-cost robotics.



Of all the lithium chemistries, LiFePO4 (a subcategory of Li-Ion) is the safest.



The maximum level of protection and BMS oversight are necessary for standard LiPo packs.



Although NiMH is stable, it lacks the power required for sophisticated robotics.



Safety issues:

Why BMS (Battery Management System) matters:

Li-Ion/LiPo packs of any size run the risk of overcharging or deep discharging, which can possibly cause them to catch fire. Safety is greatly increased by adding a basic PCB protection board.



A voltage regulator has 3 pins:



\* Output

\* Input

\* Ground



Input comes from the original power source.

Ground is connected to GND.

Output provides the regulated voltage.



For a DC motor, I need to use an L298N motor driver.

For the joystick, a 5V input is still required.

If I can order some voltage regulators, they should solve the power issue.

Never mind, they are extremely inefficient and waste power as heat.

However, they do provide a stable voltage and low noise, though I don't really care about that.



Switching regulators are more expensive.

Options are buck converters or voltage regulators.



Batteries:



\* Lithium-ion (Li-Ion)

\* Lithium-polymer (Li-Po)

\* Nickel-metal hydride (NiMH)



Summary of yesterday:

I wrote the pseudocode logic.

Realized I might need structs to be more efficient, but I'm not doing that for this project.

Soldered and fried two buck converters before realizing that I inverted the voltage.

Corrected that mistake.

I found a workaround to control the fan with just one PWM input by examining the library to pull different pins to HIGH and LOW.

Also, remember: declare functions in the header file, and define/implement them in the source file.



Used parameters when the variables were already global, which was unnecessary.

Wired up the motor, but forgot to connect the ground.

The motor is constantly powered.

Now there is a wiring issue where nothing is moving, even though the function is running.

The battery is charged.

None of the pins have made it work.

The board is now unusable.

Switching to the ESP32, which frees up my GPIO pin usage.



Steps:



1\. Wire up and test the motor.

\* Motor pins: 32 and 33.

\* Forgot to connect GND.

\* PWM must have power; pulled up to 3.3V logic.





2\. Wire up and test the joystick.

\* The joystick runs at 5V, so don't force lower voltages into it.

\* Using a regular button and a potentiometer instead.

\* A wire was in the wrong place.

\* Fan ON and OFF states had incorrect logic.

\* Should be changed to a FALLING interrupt, as the button connects to GND.

\* I think I need to implement a timer because the button is stopping immediately.

\* Timer implemented, but it's not working the way I intended. The button is supposed to act as a switch.

\* Never mind again; interrupts seem unsuitable for this project, so I am going to use polling.

\* Unpredictable behavior when using this button.

\* Testing if the button is actually always pressed by checking for a LOW output.

\* CHANGED TO SHORTER WIRES.





3\. Testing the potentiometer:

\* Forgot to check which pins were ADC.

\* Using pin 34, which is an input-only ADC1 pin.





4\. Wire up and test the servo:

\* Pin 18.

\* Turns out I did kind of need an interrupt to break out of `while` loops.

\* Custom `dir` function is not working.

\* Faulty servo.

\* Must add a delay after a button press to check properly.





5\. PIR sensor:

\* Check the PIR sensor in every loop.

\* State set now inside the checker function.





6\. Wire up and test the LCD.

7\. Write basic code logic and test.

8\. Write full code logic and test.

9\. Measure dimensions.

10\. Design 3D-printed housing and mesh.

11\. Download fan design.

12\. 3D print components.

13\. Assemble.

