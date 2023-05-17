#include "stm32f0xx.h"
#include "bsp.h"
#include "delay.h"
#include "main.h"


int rotationCounter = 0;
int main()
{
    uint16_t pulse_A = 1000; // 5% de la période (20 ms)
    uint16_t pulse_B = 3000; // 10% de la période (20 ms)
    int direction = 1;
    int result;
    // Configure System Clock
    BSP_Console_Init();
		mon_printf("La Console est ready!\r\n");
    // Initialize LED pin
    BSP_LED_Init();
	  
    BSP_TIMER_PWM_Init();
	
		BSP_ADC_Init();
	  mon_printf("ADC ready!\r\n");
    TIM1->CCR1 = pulse_A;
    TIM1->CCR2 = pulse_B;
    
	  
    while(1){
			
			// Le code commenté ci dessous permet de faire tourner la tourelle (aller retour)
       /* BSP_LED_Toggle();
        BSP_DELAY_ms(20);
        
        if (direction == 1) {
            pulse_A += 10;
            pulse_B -= 10;

            if (pulse_A >= 3000 || pulse_B <= 1000) {
                direction = -1;
            }
        } else {
            pulse_A -= 10;
            pulse_B += 10;

            if (pulse_A <= 1000 || pulse_B >= 3000) {
                direction = 1;
            }
        }

        TIM1->CCR1 = pulse_A;
        TIM1->CCR2 = pulse_B;
				*/
		BSP_LED_Toggle();
		 // Canal 10 (PC2)
    ADC1->CHSELR = ADC_CHSELR_CHSEL10;
    ADC1->CR |= (1<<2); // Démarrer la conversion
    while((ADC1->ISR & (1<<2)) != (1<<2)); // Attente de la fin de conversion
    result = (ADC1->DR)/1.23;
		if (result >= 3329){
			mon_printf("ADC1 (PC2) SATURE (PAS DE LUMIERE)\r\n");
			}
		else{
			mon_printf("ADC1 (PC2) value = %d\r\n", (int)result);}
    
    // Canal 11 (PC0)
    ADC1->CHSELR = ADC_CHSELR_CHSEL11;
    ADC1->CR |= (1<<2); // Démarrer la conversion
    while((ADC1->ISR & (1<<2)) != (1<<2)); // Attente de la fin de conversion
    result = (ADC1->DR)/1.23;
		if (result >= 3329){
			mon_printf("ADC2 (PC0) SATURE (PAS DE LUMIERE)\r\n");
			}
		else{
			mon_printf("ADC2 (PC0) value = %d\r\n", (int)result);
		}
    
    // Canal 12 (PC2)
    ADC1->CHSELR = ADC_CHSELR_CHSEL12;
    ADC1->CR |= (1<<2); // Démarrer la conversion
    while((ADC1->ISR & (1<<2)) != (1<<2)); // Attente de la fin de conversion
    result = (ADC1->DR)/1.23;
		if (result >= 3329){
			mon_printf("ADC3 (PC1) SATURE (PAS DE LUMIERE)\r\n");
			}
		else{
			mon_printf("ADC3 (PC1) value = %d\r\n\n\n", (int)result);
		}
    
    BSP_DELAY_ms(600);
	}
}


// TODO : Mettre en place l'algo qui permet de corriger la position des tourelles en fonction des valeurs lues par l'ADC:

// Au plus il y a de lumière, au plus la valeur de sortie du montage est faible (éclairage max -> 0V)
