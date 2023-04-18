#include "stm32f0xx.h"
#include "bsp.h"
#include "delay.h"
#include "main.h"

int main()
{
   // Configure System Clock
	SystemClock_Config();
	// Initialize LED pin
	BSP_LED_Init();
	//main loop
	
	while(1){
		BSP_LED_Toggle();
		BSP_DELAY_ms(500);
	}
}