#include "stm32f0xx.h"
#include "bsp.h"
#include "delay.h"
#include "main.h"

int main()
{
	uint16_t pulse_A = 0;
	uint16_t pulse_B = 0;
   // Configure System Clock
	BSP_Console_Init();
	// Initialize LED pin
	BSP_LED_Init();
	BSP_TIMER_PWM_Init();
	TIM1->CCR1 = pulse_A;
	TIM2->CCR2 = pulse_B;
	
	while(1){
		BSP_LED_Toggle();
		//BSP_DELAY_ms(20);
		pulse_A++;
		pulse_B--;
	}
}