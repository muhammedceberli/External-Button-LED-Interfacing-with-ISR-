/*
 * stm32f407xx.h
 *
 *  Created on: Oct 31, 2023
 *      Author: muhammed
 */

#ifndef INC_STM32F407XX_H_
#define INC_STM32F407XX_H_

#include <stdint.h>
#define __vo volatile

/*********************************************************İşlemciye Özgü Detaylar Başlangıç ( ARM Cortex M4 )****************************************/
/*
 * NVIC ISERx Register Adresleri ( ISER0-ISER7 )
 */
#define NVIC_ISER0								( ( __vo uint32_t* )0xE000E100 )
#define NVIC_ISER1								( ( __vo uint32_t* )0xE000E104 )
#define NVIC_ISER2								( ( __vo uint32_t* )0xE000E108 )
//!!!!! Kullanılan mikrodenetleyicinin ( STM32F405xx/07xx veya STM32F415xx/17xx ) toplam 92 interrupt numarası olduğu için aşağıdakiler kullanılmadı.
#define NVIC_ISER3								( ( __vo uint32_t* )0xE000E10C )
#define NVIC_ISER4								( ( __vo uint32_t* )0xE000E110 )
#define NVIC_ISER5								( ( __vo uint32_t* )0xE000E114 )
#define NVIC_ISER6								( ( __vo uint32_t* )0xE000E118 )
#define NVIC_ISER7								( ( __vo uint32_t* )0xE000E11C )


/*
 * NVIC ICERx Register  Adresleri ( ICER0-ICER7 )
 */
#define NVIC_ICER0								( ( __vo uint32_t* )0xE000E180 )
#define NVIC_ICER1								( ( __vo uint32_t* )0xE000E184 )
#define NVIC_ICER2								( ( __vo uint32_t* )0xE000E188 )
//!!!!! Kullanılan mikrodenetleyicinin ( STM32F405xx/07xx veya STM32F415xx/17xx ) toplam 92 interrupt numarası olduğu için aşağıdakiler kullanılmadı.
#define NVIC_ICER3								( ( __vo uint32_t* )0xE000E18C )
#define NVIC_ICER4								( ( __vo uint32_t* )0xE000E190 )
#define NVIC_ICER5								( ( __vo uint32_t* )0xE000E194 )
#define NVIC_ICER6								( ( __vo uint32_t* )0xE000E198 )
#define NVIC_ICER7								( ( __vo uint32_t* )0xE000E19C )


/*
 * NVIC IPRx Register Adresleri ( IPR0-IPR22 )
 */
#define NVIC_IPR								( ( __vo uint32_t* )0xE000E400 )

/*
 * NVIC_IPRx register'ında 4 bitlik interrupt önceliği[0-15] ayarlanabilir;
 * dolayısıyla öncelik değeri 8 bitlik bölümde ( 8 - ayarlanabilir öncelik bit sayısı ) kadar sola kaydırılmalıdır.
 * Örneğin, 4 bitlik bir öncelik belirleme kullanılabilmesi için IPRx registerında ( 8 - 4 ) bit sola kaydırılmalıdır.
 * Bu özellik işlemciden işlemciye farklılık gösterebilir, kontrol et!
 */
#define NUM_OF_PRIORITY_BITS					4


/**********************************************************İşlemciye Özgü Detaylar Son*****************************************************************/

/*
 * Hafıza başlangıç adresleri
 */
#define FLASH_BASE_ADDR 						0x08000000UL
#define SRAM1_BASE_ADDR 						0x20000000UL // 112 kbyte
#define SRAM2_BASE_ADDR							0x2001C000UL // 16  kbyte
#define SRAM_BASE_ADDR 							SRAM1_BASE_ADDR
#define ROM_BASE_ADDR							0x1FFF0000UL


/*
 * AHBx ve APBx Bus Peripheral Başlangıç Adresleri
 */
#define PERIPH_BASE_ADDR						0x40000000UL
#define APB1_BASE_ADDR							PERIPH_BASE_ADDR
#define APB2_BASE_ADDR							0x40010000UL
#define AHB1_BASE_ADDR 							0x40020000UL
#define AHB2_BASE_ADDR							0x50000000UL
#define AHB3_BASE_ADDR							0xA0000000UL


/*
 * APB1 veriyolunda bulunan peripheral başlangıç adresleri
 */
#define SPI2_BASE_ADDR							0x40003800UL
#define SPI3_BASE_ADDR							0x40003C00UL
#define USART2_BASE_ADDR						0x40003C00UL
#define USART3_BASE_ADDR						0x40004800UL
#define UART4_BASE_ADDR							0x40004C00UL
#define UART5_BASE_ADDR							0x40005000UL
#define I2C1_BASE_ADDR							0x40005400UL
#define I2C2_BASE_ADDR							0x40005800UL
#define I2C3_BASE_ADDR							0x40005C00UL


/*
 * APB2 veriyolunda bulunan peripheral başlangıç adresleri
 */
#define USART1_BASE_ADDR						0x40011000UL
#define USART6_BASE_ADDR						0x40011400UL
#define SPI1_BASE_ADDR							0x40013000UL
#define SYSCFG_BASE_ADDR						0x40013800UL
#define EXTI_BASE_ADDR							0x40013C00UL


/*
 * AHB1 veriyolunda bulunan peripheral başlangıç adresleri
 * !!! Geliştirme Kiti kullanıldığı için GPIOJ ve GPIOK başlangıç adres tanımlamaları yapılmadı. !!!
 */
#define GPIOA_BASE_ADDR							0x40020000UL
#define GPIOB_BASE_ADDR							0x40020400UL
#define GPIOC_BASE_ADDR							0x40020800UL
#define GPIOD_BASE_ADDR							0x40020C00UL
#define GPIOE_BASE_ADDR							0x40021000UL
#define GPIOF_BASE_ADDR							0x40021400UL
#define GPIOG_BASE_ADDR							0x40021800UL
#define GPIOH_BASE_ADDR							0x40021C00UL
#define GPIOI_BASE_ADDR							0x40022000UL
#define RCC_BASE_ADDR							0x40023800UL


/*
 * Peripheral Registerları için Struct Yapıları
 */

/***********************GPIO Struct Yapısı***********************/
typedef struct
{
	__vo uint32_t MODER;						/* GPIO port mode register */
	__vo uint32_t OTYPER;						/* GPIO port output type register */
	__vo uint32_t OSPEEDR;						/* GPIO port output speed register */
	__vo uint32_t PUPDR;						/* GPIO port pull-up/pull-down register */
	__vo uint32_t IDR;							/* GPIO port input data register */
	__vo uint32_t ODR;							/* GPIO port output data register */
	__vo uint32_t BSRR;							/* GPIO port bit set/reset register */
	__vo uint32_t LCKR;							/* GPIO port configuration lock register */
	__vo uint32_t AFR[2];						/* AFR[0] : GPIO alternate function low register
	 	 	 	 	 	 	 	 	 	   	   	   AFR[1] : GPIO alternate function high register */
}GPIO_RegDef_t;


/***********************SPI Struct Yapısı***********************/
typedef struct
{
	__vo uint32_t CR1;							/* SPI control register 1 */
	__vo uint32_t CR2;							/* SPI control register 2 */
	__vo uint32_t SR;							/* SPI status register */
	__vo uint32_t DR;							/* SPI data register */
	__vo uint32_t CRCPR;						/* SPI CRC polynomial register */
	__vo uint32_t RXCRCR;						/* SPI RX CRC register */
	__vo uint32_t TXCRCR;						/* SPI TX CRC register */
	__vo uint32_t I2SCFGR;						/* SPI_I2S Configuration Register */
	__vo uint32_t I2SPR;						/* SPI_I2S Prescaler Register */
}SPI_RegDef_t;


/************************RCC Struct Yapısı************************/
typedef struct
{
	__vo uint32_t CR;							/* RCC clock control register */
	__vo uint32_t PLLCFGR;						/* RCC PLL configuration register */
	__vo uint32_t CFGR;							/* RCC clock configuration register */
	__vo uint32_t CIR;							/* RCC clock interrupt register */
	__vo uint32_t AHB1RSTR;						/* RCC AHB1 peripheral reset register */
	__vo uint32_t AHB2RSTR;						/* RCC AHB2 peripheral reset register */
	__vo uint32_t AHB3RSTR;						/* RCC AHB3 peripheral reset register */
	uint32_t 	  reserved0;					/* kullanılamaz */
	__vo uint32_t APB1RSTR;						/* RCC APB1 peripheral reset register */
	__vo uint32_t APB2RSTR;						/* RCC APB2 peripheral reset register */
	uint32_t      reserved1[2];					/* kullanılamaz */
	__vo uint32_t AHB1ENR;						/* RCC AHB1 peripheral clock enable register */
	__vo uint32_t AHB2ENR;						/* RCC AHB2 peripheral clock enable register */
	__vo uint32_t AHB3ENR;						/* RCC AHB3 peripheral clock enable register */
	uint32_t      reserved2;					/* kullanılamaz */
	__vo uint32_t APB1ENR;						/* RCC APB1 peripheral clock enable register */
	__vo uint32_t APB2ENR;						/* RCC APB2 peripheral clock enable register */
	uint32_t 	  reserved3[2];					/* kullanılamaz */
	__vo uint32_t AHB1LPENR;					/* RCC AHB1 peripheral clock enable in low power mode register */
	__vo uint32_t AHB2LPENR;					/* RCC AHB2 peripheral clock enable in low power mode register */
	__vo uint32_t AHB3LPENR;					/* RCC AHB3 peripheral clock enable in low power mode register */
	uint32_t      reserved4;					/* kullanılamaz */
	__vo uint32_t APB1LPENR;					/* RCC APB1 peripheral clock enable in low power mode register */
	__vo uint32_t APB2LPENR;					/* RCC APB2 peripheral clock enable in low power mode register */
	uint32_t      reserved5[2];					/* kullanılamaz */
	__vo uint32_t BDCR;							/* RCC Backup domain control register */
	__vo uint32_t CSR;							/* RCC clock control & status register */
	uint32_t      reserved6[2];					/* kullanılamaz */
	__vo uint32_t SSCGR;						/* RCC spread spectrum clock generation register */
	__vo uint32_t PLLI2SCFGR;					/* RCC PLLI2S configuration register */
}RCC_RegDef_t;


/************************EXTI Struct Yapısı************************/
typedef struct
{
	__vo uint32_t EXTI_IMR;						/* Interrupt mask register */
	__vo uint32_t EXTI_EMR;						/* Event mask register */
	__vo uint32_t EXTI_RTSR;					/* Rising trigger selection register */
	__vo uint32_t EXTI_FTSR;					/* Falling trigger selection register */
	__vo uint32_t EXTI_SWIER;					/* Software interrupt event register */
	__vo uint32_t EXTI_PR;						/* Pending register */
}EXTI_RegDef_t;


/************************SYSCFG Struct Yapısı************************/
typedef struct
{
	__vo uint32_t SYSCFG_MEMRMP;				/* SYSCFG memory remap register */
	__vo uint32_t SYSCFG_PMC;					/* SYSCFG peripheral mode configuration register */
	__vo uint32_t SYSCFG_EXTICR[4];				/* SYSCFG external interrupt configuration register */
	uint32_t reserved[2];
	__vo uint32_t SYSCFG_CMPCR;					/* Compensation cell control register */
}SYSCFG_RegDef_t;


/*
 * Peripheral Makro Tanımlamaları
 */

#define GPIOA									((GPIO_RegDef_t*) GPIOA_BASE_ADDR)
#define GPIOB									((GPIO_RegDef_t*) GPIOB_BASE_ADDR)
#define GPIOC									((GPIO_RegDef_t*) GPIOC_BASE_ADDR)
#define GPIOD									((GPIO_RegDef_t*) GPIOD_BASE_ADDR)
#define GPIOE									((GPIO_RegDef_t*) GPIOE_BASE_ADDR)
#define GPIOF									((GPIO_RegDef_t*) GPIOF_BASE_ADDR)
#define GPIOG									((GPIO_RegDef_t*) GPIOG_BASE_ADDR)
#define GPIOH									((GPIO_RegDef_t*) GPIOH_BASE_ADDR)
#define GPIOI									((GPIO_RegDef_t*) GPIOI_BASE_ADDR)

#define SPI1									((SPI_RegDef_t*) SPI1_BASE_ADDR)
#define SPI2									((SPI_RegDef_t*) SPI2_BASE_ADDR)
#define SPI3									((SPI_RegDef_t*) SPI3_BASE_ADDR)

#define RCC										((RCC_RegDef_t*) RCC_BASE_ADDR)

#define EXTI									((EXTI_RegDef_t*) EXTI_BASE_ADDR)

#define SYSCFG									((SYSCFG_RegDef_t*) SYSCFG_BASE_ADDR)


/*
 * GPIOx Peripheral Clock Enable Makroları
 */
#define GPIOA_CLK_EN()							( RCC->AHB1ENR |= ( 1 << 0 ) )
#define GPIOB_CLK_EN()							( RCC->AHB1ENR |= ( 1 << 1 ) )
#define GPIOC_CLK_EN()							( RCC->AHB1ENR |= ( 1 << 2 ) )
#define GPIOD_CLK_EN()							( RCC->AHB1ENR |= ( 1 << 3 ) )
#define GPIOE_CLK_EN()							( RCC->AHB1ENR |= ( 1 << 4 ) )
#define GPIOF_CLK_EN()							( RCC->AHB1ENR |= ( 1 << 5 ) )
#define GPIOG_CLK_EN()							( RCC->AHB1ENR |= ( 1 << 6 ) )
#define GPIOH_CLK_EN()							( RCC->AHB1ENR |= ( 1 << 7 ) )
#define GPIOI_CLK_EN()							( RCC->AHB1ENR |= ( 1 << 8 ) )


/*
 * I2Cx Peripheral Clock Enable Makroları
 */
#define I2C1_CLK_EN()							( RCC->APB1ENR |= ( 1 << 21 ) )
#define I2C2_CLK_EN()							( RCC->APB1ENR |= ( 1 << 22 ) )
#define I2C3_CLK_EN()							( RCC->APB1ENR |= ( 1 << 23 ) )


/*
 * SPIx Peripheral Clock Enable Makroları
 */
#define SPI1_CLK_EN()							( RCC->APB2ENR |= ( 1 << 12 ) )
#define SPI2_CLK_EN()							( RCC->APB1ENR |= ( 1 << 14 ) )
#define SPI3_CLK_EN()							( RCC->APB1ENR |= ( 1 << 15 ) )


/*
 * USARTx Peripheral Clock Enable Makroları
 */
#define USART1_CLK_EN()							( RCC->APB2ENR |= ( 1 << 4 ) )
#define USART2_CLK_EN()							( RCC->APB1ENR |= ( 1 << 17 ) )
#define USART3_CLK_EN()							( RCC->APB1ENR |= ( 1 << 18 ) )
#define USART6_CLK_EN()							( RCC->APB2ENR |= ( 1 << 5 ) )


/*
 * UARTx Peripheral Clock Enable Makroları
 */
#define UART4_CLK_EN()							( RCC->APB1ENR |= ( 1 << 19 ) )
#define UART5_CLK_EN()							( RCC->APB1ENR |= ( 1 << 20 ) )


/*
 * SYSCFG Peripheral Clock Enable Makroları
 */
#define SYSCFG_CLK_EN()							( RCC->APB2ENR |= ( 1 << 14 ) )


/*
 * GPIOx Peripheral Clock Disable Makroları
 */
#define GPIOA_CLK_DI()							( RCC->AHB1ENR &= ~( 1 << 0 ) )
#define GPIOB_CLK_DI()							( RCC->AHB1ENR &= ~( 1 << 1 ) )
#define GPIOC_CLK_DI()							( RCC->AHB1ENR &= ~( 1 << 2 ) )
#define GPIOD_CLK_DI()							( RCC->AHB1ENR &= ~( 1 << 3 ) )
#define GPIOE_CLK_DI()							( RCC->AHB1ENR &= ~( 1 << 4 ) )
#define GPIOF_CLK_DI()							( RCC->AHB1ENR &= ~( 1 << 5 ) )
#define GPIOG_CLK_DI()							( RCC->AHB1ENR &= ~( 1 << 6 ) )
#define GPIOH_CLK_DI()							( RCC->AHB1ENR &= ~( 1 << 7 ) )
#define GPIOI_CLK_DI()							( RCC->AHB1ENR &= ~( 1 << 8 ) )


/*
 * I2Cx Peripheral Clock Disable Makroları
 */
#define I2C1_CLK_DI()							( RCC->APB1ENR &= ~( 1 << 21 ) )
#define I2C2_CLK_DI()							( RCC->APB1ENR &= ~( 1 << 22 ) )
#define I2C3_CLK_DI()							( RCC->APB1ENR &= ~( 1 << 23 ) )


/*
 * SPIx Peripheral Clock Disable Makroları
 */
#define SPI1_CLK_DI()							( RCC->APB2ENR &= ~( 1 << 12 ) )
#define SPI2_CLK_DI()							( RCC->APB1ENR &= ~( 1 << 14 ) )
#define SPI3_CLK_DI()							( RCC->APB1ENR &= ~( 1 << 15 ) )


/*
 * USARTx Peripheral Clock Disable Makroları
 */
#define USART1_CLK_DI()							( RCC->APB2ENR &= ~( 1 << 4 ) )
#define USART2_CLK_DI()							( RCC->APB1ENR &= ~( 1 << 17 ) )
#define USART3_CLK_DI()							( RCC->APB1ENR &= ~( 1 << 18 ) )
#define USART6_CLK_DI()							( RCC->APB2ENR &= ~( 1 << 5 ) )


/*
 * UARTx Peripheral Clock Disable Makroları
 */
#define UART4_CLK_DI()							( RCC->APB1ENR &= ~( 1 << 19 ) )
#define UART5_CLK_DI()							( RCC->APB1ENR &= ~( 1 << 20 ) )


/*
 * SYSCFG Peripheral Clock Disable Makroları
 */
#define SYSCFG_CLK_DI()							( RCC->APB2ENR &= ~( 1 << 14 ) )


/*
 * GPIOx Peripheral Resetleme Makroları
 */
#define GPIOA_RESET()							do { ( RCC->AHB1RSTR |= 1 << 0 ); ( RCC->AHB1RSTR &= ~( 1 << 0 ) ); }while( 0 )
#define GPIOB_RESET()							do { ( RCC->AHB1RSTR |= 1 << 1 ); ( RCC->AHB1RSTR &= ~( 1 << 1 ) ); }while( 0 )
#define GPIOC_RESET()							do { ( RCC->AHB1RSTR |= 1 << 2 ); ( RCC->AHB1RSTR &= ~( 1 << 2 ) ); }while( 0 )
#define GPIOD_RESET()							do { ( RCC->AHB1RSTR |= 1 << 3 ); ( RCC->AHB1RSTR &= ~( 1 << 3 ) ); }while( 0 )
#define GPIOE_RESET()							do { ( RCC->AHB1RSTR |= 1 << 4 ); ( RCC->AHB1RSTR &= ~( 1 << 4 ) ); }while( 0 )
#define GPIOF_RESET()							do { ( RCC->AHB1RSTR |= 1 << 5 ); ( RCC->AHB1RSTR &= ~( 1 << 5 ) ); }while( 0 )
#define GPIOG_RESET()							do { ( RCC->AHB1RSTR |= 1 << 6 ); ( RCC->AHB1RSTR &= ~( 1 << 6 ) ); }while( 0 )
#define GPIOH_RESET()							do { ( RCC->AHB1RSTR |= 1 << 7 ); ( RCC->AHB1RSTR &= ~( 1 << 7 ) ); }while( 0 )
#define GPIOI_RESET()							do { ( RCC->AHB1RSTR |= 1 << 8 ); ( RCC->AHB1RSTR &= ~( 1 << 8 ) ); }while( 0 )


/*
 * SPIx Peripheral Resetleme Makroları
 */
#define SPI1_RESET()							do{ ( RCC->APB2RSTR |= 1 << 12 ); ( RCC->APB2RSTR &= ~( 1 << 12 ) ); }while( 0 )
#define SPI2_RESET()							do{ ( RCC->APB1RSTR |= 1 << 14 ); ( RCC->APB1RSTR &= ~( 1 << 14 ) ); }while( 0 )
#define SPI3_RESET()							do{ ( RCC->APB1RSTR |= 1 << 15 ); ( RCC->APB1RSTR &= ~( 1 << 15 ) ); }while( 0 )


/*
 * GPIOx portu base adresine karşılık gelen port kodunu veren makro
 * !! SYSCFG->EXTICR registerları için oluşturuldu. Farklı yerlerde kullanılabilme ihtimaline karşılık bu dosyada tutuluyor. !!
 */
#define GPIO_BASE_ADDR_TO_CODE( x )				( ( x == GPIOA ) ? 0 :\
												  ( x == GPIOB ) ? 1 :\
												  ( x == GPIOC ) ? 2 :\
												  ( x == GPIOD ) ? 3 :\
												  ( x == GPIOE ) ? 4 :\
												  ( x == GPIOF ) ? 5 :\
												  ( x == GPIOG ) ? 6 :\
												  ( x == GPIOH ) ? 7 :\
												  ( x == GPIOI ) ? 8 : 255 ) // A,...,I portlarından herhangi biri değilse 255(8 bit) değerini döndür.


/*
 * STM32F407x mikrodenetleyicisine ait IRQ( Interrupt Request ) numaraları
 * !! Tüm IRQ numaraları yerine kullanılması planlanan IRQ numaraları oluşturuldu. !!
 */
#define IRQ_NO_EXTI0 							6  //EXTI Line0 interrupt
#define IRQ_NO_EXTI1 							7  //EXTI Line1 interrupt
#define IRQ_NO_EXTI2 							8  //EXTI Line2 interrupt
#define IRQ_NO_EXTI3 							9  //EXTI Line3 interrupt
#define IRQ_NO_EXTI4 							10 //EXTI Line4 interrupt
#define IRQ_NO_EXTI5_9 							23 //EXTI Line5_9 interrupt
#define IRQ_NO_EXTI10_15 						40 //EXTI Line10_15 interrupt

#define IRQ_NO_I2C1_EV 							31 //I2C1 event interrupt
#define IRQ_NO_I2C1_ER							32 //I2C1 error interrupt
#define IRQ_NO_I2C2_EV							33 //I2C2 event interrupt
#define IRQ_NO_I2C2_ER							34 //I2C2 error interrupt
#define IRQ_NO_I2C3_EV							72 //I2C3 event interrupt
#define IRQ_NO_I2C3_ER							73 //I2C3 error interrupt

#define IRQ_NO_SPI1								35 //SPI1 global interrupt
#define IRQ_NO_SPI2								36 //SPI2 global interrupt
#define IRQ_NO_SPI3								51 //SPI3 global interrupt

#define IRQ_NO_USART1							37 //USART1 global interrupt
#define IRQ_NO_USART2							38 //USART2 global interrupt
#define IRQ_NO_USART3							39 //USART3 global interrupt

#define IRQ_NO_UART4							52 //UART4 global interrupt
#define IRQ_NO_UART5							53 //UART5 global interrupt


/*
 * STM32F407x mikrodenetleyicisine ait IRQ( Interrupt Request ) Öncelik numara makroları
 * 4 bitlik öncelik biti olduğu için 0-15 arasında değerler oluşturuldu!!!
 */
#define NVIC_IRQ_PRIO_0							0
#define NVIC_IRQ_PRIO_1							1
#define NVIC_IRQ_PRIO_2							2
#define NVIC_IRQ_PRIO_3							3
#define NVIC_IRQ_PRIO_4							4
#define NVIC_IRQ_PRIO_5							5
#define NVIC_IRQ_PRIO_6							6
#define NVIC_IRQ_PRIO_7							7
#define NVIC_IRQ_PRIO_8							8
#define NVIC_IRQ_PRIO_9							9
#define NVIC_IRQ_PRIO_10						10
#define NVIC_IRQ_PRIO_11						11
#define NVIC_IRQ_PRIO_12						12
#define NVIC_IRQ_PRIO_13						13
#define NVIC_IRQ_PRIO_14						14
#define NVIC_IRQ_PRIO_15						15


/*
 * Kullanılabilir makrolar
 */
#define ENABLE 									1
#define DISABLE 								0
#define SET 									ENABLE
#define RESET 									DISABLE
#define GPIO_PIN_SET 							SET
#define GPIO_PIN_RESET							RESET
#define FLAG_SET								SET
#define FLAG_RESET								RESET


/*
 * SPI peripheral registerlarına ait bit konumu makroları
 */
#define SPI_CR1_CPHA							0
#define SPI_CR1_CPOL							1
#define SPI_CR1_MSTR							2
#define SPI_CR1_BR_START						3
#define SPI_CR1_SPE								6
#define SPI_CR1_LSBFIRST						7
#define SPI_CR1_SSI								8
#define SPI_CR1_SSM								9
#define SPI_CR1_RXONLY							10
#define SPI_CR1_DFF								11
#define SPI_CR1_CRCNEXT							12
#define SPI_CR1_CRCEN							13
#define SPI_CR1_BIDIOE							14
#define SPI_CR1_BIDIMODE						15

#define SPI_CR2_RXDMAEN							0
#define SPI_CR2_TXDMAEN							1
#define SPI_CR2_SSOE							2
#define SPI_CR2_FRF								4
#define SPI_CR2_ERRIE							5
#define SPI_CR2_RXNEIE							6
#define SPI_CR2_TXEIE							7


#define SPI_SR_RXNE								0
#define SPI_SR_TXE								1
#define SPI_SR_CRCERR							4
#define SPI_SR_MODF								5
#define SPI_SR_BSY								7
#define SPI_SR_FRE								8


#include "stm32f407xx_gpio_driver.h"
#include "stm32f407xx_spi_driver.h"


#endif /* INC_STM32F407XX_H_ */
