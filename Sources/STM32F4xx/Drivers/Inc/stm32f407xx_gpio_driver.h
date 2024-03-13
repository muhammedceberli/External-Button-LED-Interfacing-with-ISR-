/*
 * stm32f407xx_gpio_driver.h
 *
 *  Created on: Nov 15, 2023
 *      Author: muhammed
 */

#ifndef INC_STM32F407XX_GPIO_DRIVER_H_
#define INC_STM32F407XX_GPIO_DRIVER_H_


#include "stm32f407xx.h"


/*
 * GPIO Konfigürasyonu için Gerekli Veri Yapısı
 */
typedef struct
{
	uint8_t GPIO_PinNumber;			// Pin Numarası @GPIO_Pins
	uint8_t GPIO_PinMode;			// Modlar [ Giriş/Çıkış/Alternatif fonksiyon ] @GPIO_PinModes
	uint8_t GPIO_Pin_O_Speed;   	// Çıkış hızı @GPIO_OutputSpeeds
	uint8_t GPIO_Pin_O_Type;        // Çıkış modu Konfigürasyonu [ Open Drain / Push-Pull ] @GPIO_OutputTypes
	uint8_t GPIO_Pin_PUPD;			// Pull-Up Pull_Down Direnci @GPIO_PinPull_UpDown
	uint8_t GPIO_PinAltFun;			// Alternatif Fonksiyon Numarası [ AF0-AF15 ] @GPIO_AF_Modes
}GPIO_PinConfig_t;


/*
 * GPIO Handle Yapısı
 */
typedef struct
{
	// GPIO peripheral başlangıç adresini tutan pointer
	GPIO_RegDef_t *pGPIOx;

	// GPIO peripheral kullanıcı konfigürasyonunu sağlayan değişken
	GPIO_PinConfig_t GPIO_PinConfig;

}GPIO_Handle_t;


/*
 * @GPIO_Pins
 * GPIO pin adı makroları
 */
#define GPIO_PIN_0							0
#define GPIO_PIN_1							1
#define GPIO_PIN_2							2
#define GPIO_PIN_3							3
#define GPIO_PIN_4							4
#define GPIO_PIN_5							5
#define GPIO_PIN_6							6
#define GPIO_PIN_7							7
#define GPIO_PIN_8							8
#define GPIO_PIN_9							9
#define GPIO_PIN_10							10
#define GPIO_PIN_11							11
#define GPIO_PIN_12							12
#define GPIO_PIN_13							13
#define GPIO_PIN_14							14
#define GPIO_PIN_15							15


/*
 * @GPIO_PinModes
 * GPIO pin modları makroları
 */
#define GPIO_MODE_IN						0 // Giriş modu
#define GPIO_MODE_OUT						1 // Çıkış modu
#define GPIO_MODE_ALTFUN					2 // Alternatif fonksiyon modu
#define GPIO_MODE_ANALOG					3 // Analog modu
#define GPIO_MODE_IT_FT						4 // Interrrupt falling trigger modu
#define GPIO_MODE_IT_RT						5 // Interrupt rising trigger modu
#define GPIO_MODE_IT_FT_RT					6 // Interrupt falling ve rising trigger modu


/*
 * @GPIO_OutputTypes
 * GPIO çıkış modu tipi makroları
 */
#define GPIO_OTYPE_PP						0 // Push-Pull konfigürasyonu
#define GPIO_OTYPE_OD						1 // Open-Drain konfigürasyonu


/*
 * @GPIO_OutputSpeeds
 * GPIO çıkış modu hızı makroları
 */
#define GPIO_OSPEED_LOW						0 // düşük hız
#define GPIO_OSPEED_MED						1 // orta hız
#define GPIO_OSPEED_HIGH					2 // yüksek hız
#define GPIO_OSPEED_V_HIGH					3 // en yüksek hız


/*
 * @GPIO_PinPull_UpDown
 * GPIO pini Pull-Up/Pull-Down Maktroları
 */
#define GPIO_PIN_NO_PUPD						0 // Pull-Up/Pull-Down devre dışı
#define GPIO_PIN_PU								1 // Pull-Up aktif
#define GPIO_PIN_PD								2 // Pull-Down aktif


/*
 * @GPIO_AF_Modes
 * GPIO pini Alternatif Fonksiyon Modu Makroları
 */
#define GPIO_AF_0							0  // Alternatif fonksiyon modu 0
#define GPIO_AF_1							1  // Alternatif fonksiyon modu 1
#define GPIO_AF_2							2  // Alternatif fonksiyon modu 2
#define GPIO_AF_3							3  // Alternatif fonksiyon modu 3
#define GPIO_AF_4							4  // Alternatif fonksiyon modu 4
#define GPIO_AF_5							5  // Alternatif fonksiyon modu 5
#define GPIO_AF_6							6  // Alternatif fonksiyon modu 6
#define GPIO_AF_7							7  // Alternatif fonksiyon modu 7
#define GPIO_AF_8							8  // Alternatif fonksiyon modu 8
#define GPIO_AF_9							9  // Alternatif fonksiyon modu 9
#define GPIO_AF_10							10 // Alternatif fonksiyon modu 10
#define GPIO_AF_11							11 // Alternatif fonksiyon modu 11
#define GPIO_AF_12							12 // Alternatif fonksiyon modu 12
#define GPIO_AF_13							13 // Alternatif fonksiyon modu 13
#define GPIO_AF_14							14 // Alternatif fonksiyon modu 14
#define GPIO_AF_15							15 // Alternatif fonksiyon modu 15


/***********************************************************************
 * 			Bu driver dosyası tarafından desteklenen API'lar
 * 	Daha fazla bilgi için fonksiyon açıklamalarına bak.
 ***********************************************************************/

/*
 * Peripheral Clock Kurulumu
 */
void GPIO_PeriClkControl( GPIO_RegDef_t *pGPIOx, uint8_t EnOrDi );


/*
 * Peripheral Başlatma ve Sonlandırma
 */
void GPIO_Init( GPIO_Handle_t *pGPIOHandle );
void GPIO_DeInit( GPIO_RegDef_t *pGPIOx );


/*
 * Peripheral Pin veya Porttan Okuma
 */
uint8_t GPIO_ReadFromInputPin( GPIO_RegDef_t *pGPIOx, uint8_t PinNumber );
uint16_t GPIO_ReadFromInputPort( GPIO_RegDef_t *pGPIOx );


/*
 * Peripheral Pin veya Porta Yazma
 */
void GPIO_WriteToOutputPin( GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t val );
void GPIO_WriteToOutputPort( GPIO_RegDef_t *pGPIOx, uint16_t val );


/*
 * Peripheral Pin Durumu Değiştirme
 */
void GPIO_ToggleOutputPin( GPIO_RegDef_t *pGPIOx, uint8_t PinNumber );


/*
 * Peripheral Interrupt Ayarlaması ve Kullanımı
 */
void GPIO_IRQ_Interrupt_Config( uint8_t IRQNumber, uint8_t EnOrDi );
void GPIO_IRQ_PriorityConfig( uint8_t IRQNumber, uint8_t IRQPriority );
void GPIO_IRQHandling( uint8_t PinNumber );








#endif /* INC_STM32F407XX_GPIO_DRIVER_H_ */
