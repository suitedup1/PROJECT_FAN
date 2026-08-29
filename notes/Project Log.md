\#Project Log



Setting up ESP8266:

\- install correct driver from https://www.silabs.com/software-and-tools/usb-to-uart-bridge-vcp-drivers?tab=downloads

\- ensure that the usb cable being used is appropriate to transmit data

\- setup arduino IDE with the board with tutorial from lastminuteengineers



using pir sensor:

\- senses movement, then writes HIGH to a data pin before changing it back to low

\- use interrupts

**KEY NOTE**

Another important thing about ISRs is that you should keep their code as fast and simple as possible and avoid things like complex operations, writing to the Serial Monitor, or using delay(). Instead, you should use a flag or counter to indicate that the interrupt happened, and then handle whatever you need to do in the main code or loop() section.

so i simply set motion to true then set it back to false once ive dealt with it in main program

