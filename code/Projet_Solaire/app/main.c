#include "stm32f0xx.h"
#include "bsp.h"
#include "delay.h"
#include "main.h"


int rotationCounter = 0;
int main()
{
    uint16_t pulse_A = 1000; // 5% de la période (20 ms)
    uint16_t pulse_B = 2000; // 10% de la période (20 ms)
    int direction = 1;
    
    // Configure System Clock
    BSP_Console_Init();
    // Initialize LED pin
    BSP_LED_Init();
    BSP_TIMER_PWM_Init();
    TIM1->CCR1 = pulse_A;
    TIM1->CCR2 = pulse_B;
    
    while(1){
        BSP_LED_Toggle();
        BSP_DELAY_ms(20);
        
        if (direction == 1) {
            pulse_A += 25;
            pulse_B -= 25;

            if (pulse_A >= 2000 || pulse_B <= 1000) {
                direction = -1;
            }
        } else {
            pulse_A -= 25;
            pulse_B += 25;

            if (pulse_A <= 1000 || pulse_B >= 2000) {
                direction = 1;
            }
        }

        TIM1->CCR1 = pulse_A;
        TIM1->CCR2 = pulse_B;
    }
}

