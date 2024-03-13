## External LED Toggle with Push-Button using STM32-DISC1 Development Kit and ISR



This application is an example of interfacing external push buttons and LEDs with STM32F407xx series microcontroller. It uses ISR( Interrupt Service Routine ).<br />
It toggles the relevant LEDs whenever the button(buttons) interrupt(s) is(are) triggered with respective priority order( yellow, red, blue respectively ). <br />
Blue button changes the state of green led!!!<br />
<br />
The source code was written using the STM32 Driver File developed seperately. It has three files( stm32f407xx.h, stm32f407xx_gpio_driver.h, stm32f407xx_gpio_driver.c ) for now. Additionally, these driver files were also added.<br />
<br />
The complete STM32 driver file will be uploaded seperately when the other sections are completed.<br />
<br />
In the main.c source code, delay() function is for testing the driver file that the priority order works properly or not.<br />
The buttons' interrupts are triggered on a falling edge because of their iddle state is logic HIGH(with internal pull-up resistor).<br />
Other configurations can also be made.<br />

Used eqipments<br />
--------------------<br />
3 x External Push Buttons ( Yellow, Red, Blue )<br />
3 x External LEDs ( Yellow, Red, Green )<br />
STM32-DISC1 Development Kit <br />
MM, MF Jumpers<br />
3 x LED Protection Resistors ( typically 180-500 Ohm )<br />
<br />
<br />
!!!!! Pins below must not be used for STM32F407xx series microcontrollers. ( Check the datasheet and reference manual for details. ) !!!!!!<br />
PA15: JTDI in pull-up<br />
PA14: JTCK/SWCLK in pull-down<br />
PA13: JTMS/SWDAT in pull-up<br />
PB4: NJTRST in pull-up<br />
PB3: JTDO in floating state<br />
<br />
Circuit Diagram ( TincerCad )<br />
![image](https://github.com/muhammedceberli/External-Button-LED-Interfacing-with-ISR-/assets/93437771/6b902491-1cff-44d8-8f25-46bb7d9fe88b)<br />
<br />
Breadboard Connections<br />
![WhatsApp Image 2024-01-11 at 15 27 51](https://github.com/muhammedceberli/External-Button-LED-Interfacing-with-ISR-/assets/93437771/9b86d3cc-7a5b-4152-a2da-7680c859f3b5)<br />
<br />
Result<br />
https://github.com/muhammedceberli/External-Button-LED-Interfacing-with-ISR-/assets/93437771/549f7bf2-41f5-46bb-9f8a-b6c29083438a
<br />


