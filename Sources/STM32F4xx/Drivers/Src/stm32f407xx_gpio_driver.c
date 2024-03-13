/*
 * stm32f407xx_gpio_driver.c
 *
 *  Created on: Nov 15, 2023
 *      Author: muhammed
 */


#include "stm32f407xx_gpio_driver.h"


/*********************************************************************************************
 *
 *@fn			 	-	GPIO_PeriClkControl
 *
 *@özet			 	-	GPIO portu clock sinyali kontrolünü sağlar.
 *
 *@param[0]		 	-	GPIO portu başlangıç adresi pointer'ı
 *@param[1]			-	Clock sinyal kaynağı etkinleştir ya da devre dışı bırak
 *
 *@return			-	none
 *
 *@NOT				-	EnOrDi değişkeni için ENABLE ya da DISABLE makroları kullanılmalı
 *
 **********************************************************************************************/
void GPIO_PeriClkControl( GPIO_RegDef_t *pGPIOx, uint8_t EnOrDi )
{
	if( EnOrDi == ENABLE )
	{
		//saat sinyali kaynağını aktif et.
		if( pGPIOx == GPIOA )
		{
			GPIOA_CLK_EN();
		}
		else if( pGPIOx == GPIOB )
		{
			GPIOB_CLK_EN();
		}
		else if( pGPIOx == GPIOC )
		{
			GPIOC_CLK_EN();
		}
		else if( pGPIOx == GPIOD )
		{
			GPIOD_CLK_EN();
		}
		else if( pGPIOx == GPIOE )
		{
			GPIOE_CLK_EN();
		}
		else if( pGPIOx == GPIOF )
		{
			GPIOF_CLK_EN();
		}
		else if( pGPIOx == GPIOG )
		{
			GPIOG_CLK_EN();
		}
		else if( pGPIOx == GPIOH )
		{
			GPIOH_CLK_EN();
		}
		else if( pGPIOx == GPIOI )
		{
			GPIOI_CLK_EN();
		}
	}
	else
	{
		// saat sinyali kaynağını devre dışı bırak.
		if( pGPIOx == GPIOA )
		{
			GPIOA_CLK_DI();
		}
		else if( pGPIOx == GPIOB )
		{
			GPIOB_CLK_DI();
		}
		else if( pGPIOx == GPIOC )
		{
			GPIOC_CLK_DI();
		}
		else if( pGPIOx == GPIOD )
		{
			GPIOD_CLK_DI();
		}
		else if( pGPIOx == GPIOE )
		{
			GPIOE_CLK_DI();
		}
		else if( pGPIOx == GPIOF )
		{
			GPIOF_CLK_DI();
		}
		else if( pGPIOx == GPIOG )
		{
			GPIOG_CLK_DI();
		}
		else if( pGPIOx == GPIOH )
		{
			GPIOH_CLK_DI();
		}
		else if( pGPIOx == GPIOI )
		{
			GPIOI_CLK_DI();
		}
	}
}


/********************************************************************************************	*
 *
 *@fn			 	-	GPIO_Init
 *
 *@özet			 	-	GPIO pini için belirlenen konfigürasyonu yapar.
 *
 *@param[0]		 	-	GPIO Handle veri yapısı kullanılarak oluşturulmuş pointer
 *
 *@return			-	none
 *
 *@NOT				-	none
 *
 **********************************************************************************************/
void GPIO_Init( GPIO_Handle_t *pGPIOHandle )
{
	// Peripheral saat sinyalini aktif etme
	GPIO_PeriClkControl(pGPIOHandle->pGPIOx, ENABLE);

	uint32_t temp = 0; // registerları ayarlamak için geçici değişken

	// 1. GPIO pininin modunu ayarla.
	if( pGPIOHandle->GPIO_PinConfig.GPIO_PinMode < GPIO_MODE_IT_FT )
	{
		temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << ( 2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );
		pGPIOHandle->pGPIOx->MODER &= ~( 0x3 << 2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber ); 	// ilgili register bölümünü temizle.
		pGPIOHandle->pGPIOx->MODER |= temp; 													// ilgili register bölümünü ayarla.
		temp = 0;
	}else
	{
		// GPIO interrupt modu
		if( pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT )
		{
			// falling trigger konfigürasyonu ( FTSR )
			EXTI->EXTI_FTSR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );
			// RTSR registerında ilgili pini temizleme
			EXTI->EXTI_RTSR &= ~( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );

		}else if( pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT )
		{
			// rising trigger konfigürasyonu ( RTSR )
			EXTI->EXTI_RTSR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );
			// FTSR registerında ilgili pini temizleme
			EXTI->EXTI_FTSR &= ~( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );

		}else if ( pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT_RT )
		{
			// rising ve falling trigger konfigürasyonu ( FTSRT and RTSR )
			EXTI->EXTI_FTSR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );
			EXTI->EXTI_RTSR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );
		}

		// SYSCFG_EXTICR üzerinden GPIO port seçimini ayarla.
		uint8_t portCode = GPIO_BASE_ADDR_TO_CODE( pGPIOHandle->pGPIOx );
		uint8_t temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4;
		uint8_t temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4;
		SYSCFG_CLK_EN();
		SYSCFG->SYSCFG_EXTICR[temp1] |= ( portCode << (4*temp2) );

		// IMR registerı üzerinden EXTI interrupt teslimatını ayarla.
		EXTI->EXTI_IMR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );

	}

	// 2. GPIO pini çıkış modu olarak seçilmişse çıkış hızını ve çıkış türünü( Open_Drain/Push-Pull ) ayarla.
	if( pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_OUT )
	{
		temp = pGPIOHandle->GPIO_PinConfig.GPIO_Pin_O_Speed << ( 2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );
		pGPIOHandle->pGPIOx->OSPEEDR &= ~( 0x3 << 2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );	// ilgili register bölümünü temizle.
		pGPIOHandle->pGPIOx->OSPEEDR |= temp;													// ilgili register bölümünü ayarla.
		temp = 0;
	}

	// 3. GPIO pini çıkış modu ya da alternatif fonksiyon modu olarak seçilmişse çıkış türünü belirle.
	if( pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_OUT || pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFUN )
	{
		temp = pGPIOHandle->GPIO_PinConfig.GPIO_Pin_O_Type << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber;
		pGPIOHandle->pGPIOx->OTYPER &= ~( 0x1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );	// ilgili register bölümünü temizle.
		pGPIOHandle->pGPIOx->OTYPER |= temp;													// ilgili register bölümünü ayarla.
		temp = 0;
	}

	// 4. Pull_Up/Down ayarlamalarını yap.
	temp = pGPIOHandle->GPIO_PinConfig.GPIO_Pin_PUPD << ( 2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );
	pGPIOHandle->pGPIOx->PUPDR &= ~( 0x3 << 2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );		// ilgili register bölümünü temizle.
	pGPIOHandle->pGPIOx->PUPDR |= temp;															// ilgili register bölümünü ayarla.
	temp = 0;

	// 5. GPIO pini alternatif fonksiyon modunda seçilmişse gerekli ayarlamaları yap.
	if( pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFUN )
	{
		uint8_t temp1 = ( pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber )/8;
		uint8_t temp2 = ( pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber )%8;
		pGPIOHandle->pGPIOx->AFR[ temp1 ] &= ~( 0xF << 4*temp2 );									// ilgili register bölümünü temizle.
		pGPIOHandle->pGPIOx->AFR[ temp1 ] |= ( pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFun << ( 4*temp2 ));												// ilgili register bölümünü ayarla.
		temp1 = 0;
		temp2 = 0;
	}
}


/*********************************************************************************************
 *
 *@fn			 	-	GPIO_DeInit
 *
 *@özet			 	-	Belirtilen GPIO portunu resetler.
 *
 *@param[0]		 	-	GPIO portu başlangıç adresi pointer'ı
 *
 *@return			-	none
 *
 *@NOT				-	none
 *
 **********************************************************************************************/
void GPIO_DeInit( GPIO_RegDef_t *pGPIOx )
{
	if( pGPIOx == GPIOA )
	{
		GPIOA_RESET();
	}else if( pGPIOx == GPIOB )
	{
		GPIOB_RESET();
	}else if( pGPIOx == GPIOC )
	{
		GPIOC_RESET();
	}else if( pGPIOx == GPIOD )
	{
		GPIOD_RESET();
	}else if( pGPIOx == GPIOE )
	{
		GPIOE_RESET();
	}else if( pGPIOx == GPIOF )
	{
		GPIOF_RESET();
	}else if( pGPIOx == GPIOG )
	{
		GPIOG_RESET();
	}else if( pGPIOx == GPIOH )
	{
		GPIOH_RESET();
	}else if( pGPIOx == GPIOI )
	{
		GPIOI_RESET();
	}
}


/*********************************************************************************************
 *
 *@fn			 	-	GPIO_ReadFromInputPin
 *
 *@özet			 	-	Belirtilen GPIO pininden okuma sağlayıp değeri sonuç olarak döndürür.
 *
 *@param[0]		 	-	GPIO portu başlangıç adresi pointer'ı
 *@param[1]			-	GPIO pin numarası
 *
 *@return			-	unsigned integer[1/0]
 *
 *@NOT				-	none
 *
 **********************************************************************************************/
uint8_t GPIO_ReadFromInputPin( GPIO_RegDef_t *pGPIOx, uint8_t PinNumber )
{
	uint8_t val = 0;
	val = ( uint8_t )( ( pGPIOx->IDR >> PinNumber ) & 0x1 );
	return val;
}


/*********************************************************************************************
 *
 *@fn			 	-	GPIO_ReadFromInputPort
 *
 *@özet			 	-	Belirtilen GPIO portundan okuma sağlayıp değeri sonuç olarak döndürür.
 *
 *@param[0]		 	-	GPIO portu başlangıç adresi pointer'ı
 *
 *@return			-	16 bit unsigned integer
 *
 *@NOT				-	none
 *
 **********************************************************************************************/
uint16_t GPIO_ReadFromInputPort( GPIO_RegDef_t *pGPIOx )
{
	uint16_t val = 0;
	val = ( uint16_t )pGPIOx->IDR;

	return val;
}


/*********************************************************************************************
 *
 *@fn			 	-	GPIO_WriteToOutputPin
 *
 *@özet			 	-	Belirtilen GPIO pinine belirtilen değeri yazdırır.
 *
 *@param[0]		 	-	GPIO portu başlangıç adresi pointer'ı
 *@param[1]			-	GPIO pin numarası
 *@param[2]			-	Yazdırılacak değer[0/1]
 *
 *@return			-	none
 *
 *@NOT				-	val değeri için GPIO_PIN_SET ya da GPIO_PIN_RESET makroları kullanılmalı
 *
 **********************************************************************************************/
void GPIO_WriteToOutputPin( GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t val )
{
	if( val == GPIO_PIN_SET )
	{
		// pine 1 yazdır.
		pGPIOx->ODR |= ( 1 << PinNumber );
	}else if( val == GPIO_PIN_RESET )
	{
		// pine 0 yazdır.
		pGPIOx->ODR &= ~( 1 << PinNumber );
	}
}


/*********************************************************************************************
 *
 *@fn			 	-	GPIO_WriteToOutputPort
 *
 *@özet			 	-	Belirtilen GPIO portuna belirtilen değeri yazdırır.
 *
 *@param[0]		 	-	GPIO portu başlangıç adresi pointer'ı
 *@param[2]			-	Yazdırılacak değer[ 16 bit unsigned integer ]
 *
 *@return			-	none
 *
 *@NOT				-	none
 *
 **********************************************************************************************/
void GPIO_WriteToOutputPort( GPIO_RegDef_t *pGPIOx, uint16_t val )
{
	pGPIOx->ODR = val;
}


/*********************************************************************************************
 *
 *@fn			 	-	GPIO_ToggleOutputPin
 *
 *@özet			 	-	Belirtilen GPIO pininin güncel değerini değiştirir.[ 1->0 , 0->1 ]
 *
 *@param[0]		 	-	GPIO portu başlangıç adresi pointer'ı
 *@param[1]			-	GPIO pin numarası
 *
 *@return			-	none
 *
 *@NOT				-	none
 *
 **********************************************************************************************/
void GPIO_ToggleOutputPin( GPIO_RegDef_t *pGPIOx, uint8_t PinNumber )
{
	pGPIOx->ODR ^= ( 1 << PinNumber ); // ^ işareti XOR anlamındadır.
}


/*********************************************************************************************
 *
 *@fn			 	-	GPIO_IRQ_Interrupt_Config
 *
 *@özet			 	-	Peripheral tarafında ayarlanan interrupt'ın işlemci tarafında aktif edilmesini sağlar.
 *@özet			 	-   Belirtilen IRQ numarasına ait interrupt'ı aktif eder ya da devre dışı bırakır.
 *
 *@param[0]		 	-	Interrupt numarası
 *@param[1]			-	Interrupt'ı etkinleştir ya da devre dışı bırak
 *
 *@return			-	none
 *
 *@NOT				-	EnOrDi değişkeni için ENABLE ya da DISABLE makroları kullanılmalı
 *
 **********************************************************************************************/
void GPIO_IRQ_Interrupt_Config( uint8_t IRQNumber, uint8_t EnOrDi )
{
	if ( EnOrDi == ENABLE )
	{
		if( IRQNumber <= 31 ) // 0-31 arası
		{
			// ISER0 registerını programla.
			( *NVIC_ISER0 ) |= ( 1 << IRQNumber );
		}else if( IRQNumber > 31 && IRQNumber < 64 ) // 32-63 arası
		{
			// ISER1 registerını programla.
			( *NVIC_ISER1 ) |= ( 1 << ( IRQNumber%32 ) );
		}else if( IRQNumber > 63 && IRQNumber < 96 ) // 64-95 arası
		{
			// ISER2 registerını programla.
			( *NVIC_ISER2 ) |= ( 1 << ( IRQNumber%32 ) );
		}
	}else
	{
		if( IRQNumber <= 31 )
		{
			// ICER0 registerını programla.
			( *NVIC_ICER0 ) |= ( 1 << IRQNumber );
		}else if( IRQNumber > 31 && IRQNumber < 64 )
		{
			// ICER1 registerını programla.
			( *NVIC_ICER1 ) |= ( 1 << ( IRQNumber%32 ) );
		}else if( IRQNumber > 63 && IRQNumber < 96 )
		{
			// ICER2 registerını programla.
			( *NVIC_ICER2 ) |= ( 1 << ( IRQNumber%32 ) );
		}
	}
}


/*********************************************************************************************
 *
 *@fn			 	-	GPIO_IRQ_PriorityConfig
 *
 *@özet			 	-   Belirtilen IRQ numarasına belirlenen öncelik değerini[0-15] atar. Öncelik değeri düşük olan interrupt daha yüksek önceliklidir. Örneğin 7 > 10
 *
 *@param[0]		 	-	Interrupt numarası
 *@param[1]			-	Interrupt öncelik değeri[0-15]
 *
 *@return			-	none
 *
 *@NOT				-	IRQPriority değeri 0-15 arasında olmalıdır!
 *
 **********************************************************************************************/
void GPIO_IRQ_PriorityConfig( uint8_t IRQNumber, uint8_t IRQPriority )
{
	uint8_t IPRx = IRQNumber / 4;
	uint8_t IPRxSection = IRQNumber % 4;
	uint8_t shiftAmount = ( 8 * IPRxSection ) + ( 8 - NUM_OF_PRIORITY_BITS );
	*( NVIC_IPR + IPRx ) |= ( IRQPriority << shiftAmount );
	//NVIC_IPR[ IRQNumber/4 ] |= ( IRQPriority << 8*( IRQNumber%4 ) );
}


/*********************************************************************************************
 *
 *@fn			 	-	GPIO_IRQHandling
 *
 *@özet			 	-	Belirlenen pin numarasına ait interrupt'ı işler.
 *
 *@param[0]		 	-	Pin numarası
 *
 *@return			-	none
 *
 *@NOT				-	none
 *
 **********************************************************************************************/
void GPIO_IRQHandling( uint8_t PinNumber )
{
	// EXTI_PR registerındaki pin numarasına karşılık gelen biti temizle.
	// !!! Temizleme işlemi ilgili bite 1 yazarak gerçekleştirilir. ( Reference Manual kontrol et! )
	if( EXTI->EXTI_PR & ( 1 << PinNumber ) )
	{
		// temizle.
		EXTI->EXTI_PR |= ( 1 << PinNumber );
	}

}
