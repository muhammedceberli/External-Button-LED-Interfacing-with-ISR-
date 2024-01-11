/*
 * extBtn_ISR.c
 *
 *  Created on: Jan 10, 2024
 *      Author: muhammed
 */

#include "stm32f407xx.h"
#include "string.h"

void delay( void );

// Butonlara her basıldığında öncelik sırasına göre ledlerin güncel durumunu değiştir.
// Interrupt butona basıldığı anda düşen kenarda( falling edge ) tetiklenmelidir.
// Sarı buton     -> PC0 falling trigger
// Kırmızı buton  -> PC1 falling trigger
// Mavi buton     -> PC2 falling trigger
/*
 * Sarı   	Led   -> PE2
 * Kırmızı  Led   -> PE3
 * Yeşil    Led   -> PE4
 */

GPIO_Handle_t extYellowBtn, extRedBtn, extBlueBtn;
GPIO_Handle_t extYellowLed, extRedLed, extGreenLed;


int main( void )
{
	memset( &extYellowBtn, 0, sizeof( extYellowBtn ) );
	memset( &extRedBtn, 0, sizeof( extYellowBtn ) );
	memset( &extBlueBtn, 0, sizeof( extYellowBtn ) );
	memset( &extYellowLed, 0, sizeof( extYellowBtn ) );
	memset( &extRedLed, 0, sizeof( extYellowBtn ) );
	memset( &extGreenLed, 0, sizeof( extYellowBtn ) );

	GPIO_PeriClkControl(GPIOC, ENABLE);

	extYellowBtn.pGPIOx = GPIOC;
	extYellowBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
	extYellowBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_0;
	extYellowBtn.GPIO_PinConfig.GPIO_Pin_PUPD = GPIO_PIN_PU;
	GPIO_Init(&extYellowBtn);

	extRedBtn.pGPIOx = GPIOC;
	extRedBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
	extRedBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_1;
	extRedBtn.GPIO_PinConfig.GPIO_Pin_PUPD = GPIO_PIN_PU;
	GPIO_Init(&extRedBtn);

	extBlueBtn.pGPIOx = GPIOC;
	extBlueBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
	extBlueBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_2;
	extBlueBtn.GPIO_PinConfig.GPIO_Pin_PUPD = GPIO_PIN_PU;
	GPIO_Init(&extBlueBtn);

	GPIO_PeriClkControl(GPIOE, ENABLE);

	extYellowLed.pGPIOx = GPIOE;
	extYellowLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	extYellowLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_2;
	extYellowLed.GPIO_PinConfig.GPIO_Pin_O_Speed = GPIO_OSPEED_V_HIGH;
	extYellowLed.GPIO_PinConfig.GPIO_Pin_O_Type = GPIO_OTYPE_PP;
	extYellowLed.GPIO_PinConfig.GPIO_Pin_PUPD = GPIO_PIN_NO_PUPD;
	GPIO_Init(&extYellowLed);

	extRedLed.pGPIOx = GPIOE;
	extRedLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	extRedLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_3;
	extRedLed.GPIO_PinConfig.GPIO_Pin_O_Speed = GPIO_OSPEED_V_HIGH;
	extRedLed.GPIO_PinConfig.GPIO_Pin_O_Type = GPIO_OTYPE_PP;
	extRedLed.GPIO_PinConfig.GPIO_Pin_PUPD = GPIO_PIN_NO_PUPD;
	GPIO_Init(&extRedLed);

	extGreenLed.pGPIOx = GPIOE;
	extGreenLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	extGreenLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_4;
	extGreenLed.GPIO_PinConfig.GPIO_Pin_O_Speed = GPIO_OSPEED_V_HIGH;
	extGreenLed.GPIO_PinConfig.GPIO_Pin_O_Type = GPIO_OTYPE_PP;
	extGreenLed.GPIO_PinConfig.GPIO_Pin_PUPD = GPIO_PIN_NO_PUPD;
	GPIO_Init(&extGreenLed);

	/*
	 * IRQ konfigürasyonları
	 */
	// Sarı buton - Yüksek öncelikli
	GPIO_IRQ_Interrupt_Config(IRQ_NO_EXTI0, ENABLE);
	GPIO_IRQ_PriorityConfig(IRQ_NO_EXTI0, NVIC_IRQ_PRIO_0);

	// Kırmızı buton - Orta öncelikli
	GPIO_IRQ_Interrupt_Config(IRQ_NO_EXTI1, ENABLE);
	GPIO_IRQ_PriorityConfig(IRQ_NO_EXTI1, NVIC_IRQ_PRIO_1);

	// Mavi buton - Düşük öncelikli
	GPIO_IRQ_Interrupt_Config(IRQ_NO_EXTI2, ENABLE);
	GPIO_IRQ_PriorityConfig(IRQ_NO_EXTI2, NVIC_IRQ_PRIO_2);

	while(1);

	return 0;
}


void EXTI0_IRQHandler( void )
{
	GPIO_IRQHandling(extYellowBtn.GPIO_PinConfig.GPIO_PinNumber);
	delay();
	GPIO_ToggleOutputPin(extYellowLed.pGPIOx, extYellowLed.GPIO_PinConfig.GPIO_PinNumber);
}


void EXTI1_IRQHandler( void )
{
	GPIO_IRQHandling(extRedBtn.GPIO_PinConfig.GPIO_PinNumber);
	delay();
	GPIO_ToggleOutputPin(extRedLed.pGPIOx, extRedLed.GPIO_PinConfig.GPIO_PinNumber);
}


void EXTI2_IRQHandler( void )
{
	GPIO_IRQHandling(extBlueBtn.GPIO_PinConfig.GPIO_PinNumber);
	delay();
	GPIO_ToggleOutputPin(extGreenLed.pGPIOx, extGreenLed.GPIO_PinConfig.GPIO_PinNumber);
}


void delay( void )
{
	for( uint32_t i = 0; i < 1000000; i++ );
}
