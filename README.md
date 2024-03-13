## External LED Toggle with Push-Button using STM32-DISC1 Development Kit and ISR

### Overview:
This project showcases a circuit where an external LED is toggled by interrupt service routines (ISR) triggered by pressing an external push-button. It is designed for use with the STM32-DISC1 Development Kit and utilizes jumper wires for connections, an LED protection resistor to limit current, and a specific STM32F4xx driver file for GPIO control.

!!!!! Pins below must not be used for STM32F407xx series microcontrollers. ( Check the datasheet and reference manual for details. ) !!!!!!<br />
PA15: JTDI in pull-up<br />
PA14: JTCK/SWCLK in pull-down<br />
PA13: JTMS/SWDAT in pull-up<br />
PB4: NJTRST in pull-up<br />
PB3: JTDO in floating state<br />

### Hardware Components:
- STM32-DISC1 Development Kit
- External push-button
- Jumper wires
- External LED
- LED protection resistor

### Software Components:
- STM32F4xx driver file for GPIO control

### Circuit Diagram:
![image](https://github.com/muhammedceberli/External-Button-LED-Interfacing-with-ISR-/assets/93437771/6b902491-1cff-44d8-8f25-46bb7d9fe88b)

### Usage:
1. Connect the external push-button and LED to the STM32-DISC1 Development Kit as per the wiring diagram.
2. Upload the STM32F4xx driver file and the project code to the development kit.
3. Press the external push-button to trigger the ISR and toggle the external LED.

### Results:
https://github.com/muhammedceberli/External-Button-LED-Interfacing-with-ISR-/assets/93437771/549f7bf2-41f5-46bb-9f8a-b6c29083438a
