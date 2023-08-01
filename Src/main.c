/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Mateusz Salamon
 * @brief          : STM32 na Rejestrach
 ******************************************************************************
 ******************************************************************************

 	 	 	 	 https://msalamon.pl
 	 	 	 	 https://sklep.msalamon.pl
 	 	 	 	 https://kursstm32.pl
 	 	 	 	 https://stm32narejestrach.pl

 */
#include "main.h"

#define LD4_ON GPIOA->BSRR |= GPIO_BSRR_BS5
#define LD4_OFF GPIOA->BSRR |= GPIO_BSRR_BR5

__IO uint32_t Tick;

void ConfigureLD4(void);
void Delay(uint32_t Delay_ms);

int main(void)
{
	// Configure SysTick Timer
	// 1s = 12 000 000
	// 0,001 = X
	SysTick_Config(12000000 / 1000);

	ConfigureLD4();

    /* Loop forever */
	while(1)
	{
		// Set LED on PA5
		LD4_ON;
		Delay(150);

		// Reset LED on PA5
		LD4_OFF;
		Delay(150);
	}
}

void ConfigureLD4(void)
{
	// Enable Clock for PORTD
	RCC->IOPENR |= RCC_IOPENR_GPIOAEN;

	// Configure GPIO Mode - Output
	GPIOA->MODER |= GPIO_MODER_MODE5_0;
	GPIOA->MODER &= ~(GPIO_MODER_MODE5_1);

	// Configure Output Mode - Push-pull
	GPIOA->OTYPER &= ~(GPIO_OTYPER_OT5);

	// Configure GPIO Speed - Low
	GPIOA->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEED5);

	// Configure Pull-up/Pull-down - no PU/PD
	GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD5);
}

void SysTick_Handler(void)
{
	Tick++; // Increase system timer
}

void Delay(uint32_t Delay_ms)
{
	uint32_t StartTime = Tick;

	while(Tick < (StartTime + Delay_ms))
	{
		// Just wait
	}
}






