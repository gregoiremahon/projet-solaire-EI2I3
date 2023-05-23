#include "stm32f0xx.h"

#include "bsp.h"

#include "delay.h"

#include "main.h"

#include <math.h>

#define false 0

#define true 1

static void SystemClock_Config(void);

int main() {



	// Declaration Variables

	uint16_t moyenne;
	uint16_t diff_photo1_2;
	uint16_t diff_photo12_3;
	uint16_t photo1;
	uint16_t photo2;
	uint16_t photo3;
	uint16_t tolerance1;
	uint16_t tolerance2;
	uint8_t horizon;
	uint8_t vertical;

	uint16_t angle_servo1;
	uint16_t angle_servo2;



    // Configure System Clock
    BSP_Console_Init();
		mon_printf("La Console est ready!\r\n");
    // Initialize LED pin
    BSP_LED_Init();
	  
    BSP_TIMER_PWM_Init();
	
		BSP_ADC_Init();
	  mon_printf("ADC ready!\r\n");
    
    



	//Initialize state variables

	angle_servo1 = 2100;
	angle_servo2 = 2100;
	tolerance1 = 100;
	tolerance2 = 100;



	while(1){
		TIM1->CCR1 = angle_servo1;
		TIM1->CCR2 = angle_servo2;
		// Canal 10 (PC2)
		ADC1->CHSELR = ADC_CHSELR_CHSEL10;
    ADC1->CR |= (1<<2); // Démarrer la conversion
    while((ADC1->ISR & (1<<2)) != (1<<2)); // Attente de la fin de conversion
		photo1 = (ADC1->DR)/1.23;
		// Canal 11 (PC0)
		ADC1->CHSELR = ADC_CHSELR_CHSEL11;
		ADC1->CR |= (1<<2);
		while ((ADC1->ISR & (1<<2)) != (1<<2));
		photo2 = (ADC1->DR)/1.23;
		// Canal 12 (PC2)
		ADC1->CHSELR = ADC_CHSELR_CHSEL12;
		ADC1->CR |= (1<<2);
		while ((ADC1->ISR & (1<<2)) != (1<<2));
		photo3 = (ADC1->DR)/1.23;

		//TRAITEMENT VALEUR
		moyenne = (photo1 + photo2) / 2;

		// Gestion de l'angle PWM
		// Horizon

		if (photo1 < photo2){
			diff_photo1_2 = abs(photo2-photo1);
			if(diff_photo1_2 > tolerance1){
				if (angle_servo2 < 2400){
					angle_servo2++;
				}
			}
		}
		if (photo2 < photo1){
			diff_photo1_2 = abs(photo1-photo2);
			if(diff_photo1_2 > tolerance1){
				if (angle_servo2 > 600){
					angle_servo2--;
				}
			}
		}

		// Vertical

		if(moyenne<photo3){
			diff_photo12_3 = abs(moyenne-photo3);
			if(diff_photo12_3 > tolerance2){
				if(angle_servo1 < 2400){
					angle_servo1++;
				}
			}
		}
		if(moyenne>photo3){
			diff_photo12_3 = abs(photo3-moyenne);
			if(diff_photo12_3 > tolerance2){
				if(angle_servo1 > 2000){
					angle_servo1--;
				}
			}
		}

		// Affichage des valeurs via la liaison série
		mon_printf("Valeur photo resistance 1 :  = %d\r\n", photo1);
		mon_printf("Valeur photo resistance 2 :  = %d\r\n", photo2);
		mon_printf("Valeur photo resistance 3 :  = %d\r\n\n", photo3);
		mon_printf("Valeur photo moyenne 12 :  = %d\r\n", moyenne);
		mon_printf("Valeur photo angle1 :  = %d\r\n", angle_servo1);
		mon_printf("Valeur photo angle2 :  = %d\r\n\n\n\n\n", angle_servo2);

	}
}
