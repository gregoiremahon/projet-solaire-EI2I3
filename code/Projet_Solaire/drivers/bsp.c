/*
* bsp.c
*
* Created on: 14 févr. 2021
* Author: darga
*/

#include "bsp.h"

/*
* BSP_LED_Init()
* Initialise la broche PA5 (LED) en sortie, mode Push-pull, vitesse de
rafraichissement High-Speed, pas de resistance de tirage
* Etat initial mus a '0'
*/
void BSP_LED_Init()
{
	//activation de horloge du peripherique GPIOA
	// mettre le bit b17 du registre RCC_AHBENR a '1'
	// voir page 128 du manuel technique (User Manuel) du Microcontrôleur STM32F072RB
	// le bit b17 de RCC_AHBENR est egalement defini = RCC_AHBENR_GPIOAEN dans le fichier stm32f0xx.h
	RCC->AHBENR |= (1<<17); // ou RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	// Configurer la broche PA5 en sortie
	// Ecrire "01" sur les bits b11b10 du registre (GPIOA_MODER)
	GPIOA->MODER &= ~(1<<11);
	GPIOA->MODER |= (1<<10);
	// Choisir option electronique Push-pull pour la sortie PA5
	// Ecrire "0" sur le bit b5 du registre (GPIOA_OTYPER)
	GPIOA->OTYPER &= ~(1<<5);
	// Choisir option electronique high speed pour la vitesse de rafraichissement pour la sortie PA5
	// Ecrire "11" sur les bits b11b10 du registre (GPIOx_OSPEEDR)
	GPIOA->OSPEEDR |= (1<<11);
	GPIOA->OSPEEDR |= (1<<10);
	// Deactiver les resistances de tirages (Pull-up ou Pull-down) pour la sortie PA5
	// Ecrire "00" sur les bits b11b10 du registre (GPIOx_PUPDR)
	GPIOA->PUPDR &= ~(1<<11);
	GPIOA->PUPDR &= ~(1<<10);
	// Mettre l'état initial de PA5 sur OFF
	GPIOA->ODR &= ~(1<<5);
}


/*
* BSP_LED_On()
* Allume la LED lier a la broche PA5
*/
void BSP_LED_On()
{
	// Ecrire "1" sur le bit b5 du registre (GPIOA_ODR)
	GPIOA->ODR |= (1<<5);
}


/*
* BSP_LED_Off()
* Eteint la LED lier a la broche PA5
*/
void BSP_LED_Off()
{
	// Ecrire "0" sur le bit b5 du registre (GPIOA_ODR)
	GPIOA->ODR &= ~(1<<5);
}

/*
* BSP_LED_Toggle()
* Change etat de la LED lier a la broche PA5
*/
void BSP_LED_Toggle()
{
	GPIOA->ODR ^= (1<<5);
}


/*
* BSP_PB_Init()
* Initialise la broche PC13 (Bouton poussoir) en input sans les
resistance de tirages Pull-up/Pull-down
*/
void BSP_PB_Init()
{
	//activation de horloge du peripherique GPIOC
	// mettre le bit b19 du registre RCC_AHBENR a '1'
	RCC->AHBENR |= (1<<19);
	// Configurer la broche PC13 en Input
	// Ecrire "00" sur les bits b27b26 du registre (GPIOC_MODER)
	GPIOC->MODER &= ~(1<<27);
	GPIOC->MODER &= ~(1<<26);

	// Deactiver les resistances de tirages (Pull-up ou Pull-down) pour la sortie PA5
	// Ecrire "00" sur les bits b27b26 du registre (GPIOC_PUPDR)
	GPIOC->PUPDR &= ~(1<<27);
	GPIOC->PUPDR &= ~(1<<26);
}

/*
* BSP_PB_GetState()
* Renvoi etat du bouton (0=Non Appuyer, 1=Appuyer)
*/
uint8_t BSP_PB_GetState()
{
	uint8_t state;
	if ((GPIOC->IDR & (1<<13)) == (1<<13))
	{
		state = 0;
	}
	else
	{
		state = 1;
	}
	return state;
}

/*
* BSP_Console_Init()
* USART2 @ 115200 Full Duplex
* 1 start - 8-bit - 1 stop
* TX -> PA2 (AF1)
* RX -> PA3 (AF1)
*/
void BSP_Console_Init()
{
	//activer horloge du peripherique GPIOA
	// mettre le bit b17 du registre RCC_AHBENR a '1'
	// voir page 128 du manuel technique (User Manuel) du Microcontrôleur STM32F072RB
	// le bit b17 de RCC_AHBENR est egalement defini = RCC_AHBENR_GPIOAEN dans le fichier stm32f0xx.h
	RCC->AHBENR |= (1<<17); // ou RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	// Choisir le mode Alternate Function (AF) pour les broches PA2 et PA3
	// pour PA2 : ecrire "10" sur les bits b5b4 du registre GPIOA_MODER
	GPIOA->MODER |=(1<<5);
	GPIOA->MODER &=~(1<<4);
	// pour PA3 : ecrire "10" sur les bits b7b6 du registre GPIOA_MODER
	GPIOA->MODER |=(1<<7);
	GPIOA->MODER &=~(1<<6);
	// Choisir la fonction AF1 (USART2) pour les broches PA2 et PA3
	// pour PA2 : ecrire "0001" sur les bits b11b10b9b8 du registre GPIOA_AFRL = GPIO->AFR[0]
	GPIOA->AFR[0] &= ~(1<<11);
	GPIOA->AFR[0] &= ~(1<<10);
	GPIOA->AFR[0] &= ~(1<<9);
	GPIOA->AFR[0] |= (1<<8);
	// Choisir la fonction AF1 (USART2) pour les broches PA2 et PA3
	// pour PA3 : ecrire "0001" sur les bits b15b14b13b12 du registre GPIOA_AFRL = GPIO->AFR[0]
	GPIOA->AFR[0] &= ~(1<<15);
	GPIOA->AFR[0] &= ~(1<<14);
	GPIOA->AFR[0] &= ~(1<<13);
	GPIOA->AFR[0] |= (1<<12);
	//activer horloge du peripherique USART2
	// mettre '1' le bit b17 du registre (RCC_APB1ENR)
	// voir page 131 du manuel technique (User Manuel) du Microcontrôleur STM32F072RB
	RCC -> APB1ENR |= (1<<17);
	//Reset de la configuration de USART2 : Mise a zero des registres de control de USART2
	//USART2_CR1, USART2_CR2 , USART2_CR3
	// On utilise les valeurs par defaut
	// 8-bits de donnees
	// 1 bit START
	// 1 bit STOP
	// desactivation de CTS/RTS
	USART2->CR1 = 0x00000000;
	USART2->CR2 = 0x00000000;
	USART2->CR3 = 0x00000000;
	// Choisir la source PCLK (APB1) comme source horloge de USART2 : Valeur par defaut
	// PCLK -> 48 MHz
	// mettre "00" sur les bits b17b16 du registre (RCC_CFGR3)
	// voir page 140 du reference manual
	RCC->CFGR3 &= ~(1<<17);
	RCC->CFGR3 &= ~(1<<16);
	// Configuration du Baud Rate = 115200
	// sans oversampling 8 bits (OVER8=0) et Fck=48MHz, USARTDIV = 48E6/115200 = 416.6666
	// BRR = 417 -> Baud Rate = 115107.9137 -> 0.08% erreur
	// avec oversampling 8 bits (OVER8=1) and Fck=48MHz, USARTDIV = 2*48E6/115200 = 833.3333
	// BRR = 833 -> Baud Rate = 115246.0984 -> 0.04% error (Meilleur choix)
	// choix oversampling 8 bits (OVER8=1)
	// mettre a '1' le bit b15 de USART2_CR1
	USART2->CR1 |= (1<<15);
	// ecrire la valeur du Baud Rate dans le registre USART2_BRR
	USART2->BRR = 833;
	// Activer la transmision : ecrire '1' sur le bit b3 de USART2_CR1
	USART2->CR1 |= (1<<3);
	// Activer la reception : ecrire '1' sur le bit b2 de USART2_CR1
	USART2->CR1 |= (1<<2);
	// activer le peripherique USART2 en dernier
	// mettre a '1' le bit bit b0 de USART2_CR1
	USART2->CR1 |= (1<<0);
}

/*
 * BSP_TIMER_Timebase_Init()
 * TIM6 cadenser a 48MHz
 * Prescaler   = 48000 -> periode de comptage = 1ms
 * Auto-reload = 1000  -> periode de mis a jour   = 1s
 */

void BSP_TIMER_Timebase_Init()
{
	// activer horloge du peripherique TIM6
	// mettre a '1' le bit b4 (TIM6EN) du registre RCC_APB1ENR
	// voir page 131 du manuel de reference
	RCC->APB1ENR |= (1<<4);            // le bit b4 est defini comme etant RCC_APB1ENR_TIM6EN

	// Faire un Reset de configuration du TIM6 : mise a zero des registres
	// TIM6_CR1 et TIM6_CR2
	// voir page 543 a 544 du manuel de reference
	TIM6->CR1 = 0x0000;
	TIM6->CR2 = 0x0000;

	// Configuration frequence de comptage
	// Prescaler : registre TIM6_PSC
	// Fck = 48MHz -> /48000 = 1KHz frequence de comptage
	TIM6->PSC = (uint16_t) 48000 -1;

	// Configuration periode des evenements
	// Prescaler : registre TIM6_ARR
	// 1000 /1000 = 1s
	TIM6->ARR = (uint16_t) 1000 -1;

	// Activation auto-reload preload : prechargement
	// mettre a '1' le bit b7 du registre TIM6_CR1
	TIM6->CR1 |= (1<<7);

	// Demarrer le Timer TIM6
	// Mettre a '1' le bit b0 du registre TIM6_CR1
	TIM6->CR1 |= (1<<0);
}

void BSP_TIMER_PWM_Init()
{
	// Activer horloge du GPIOA
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

	// Configurer PA8 et PA9 en mode Alternate Function
	GPIOA->MODER &=~((1<<16)|(1<<18));
	GPIOA->MODER |= ((1<<17) | (1<<19));

	// methode 3 pour ecrire 0010 sur les bits b3b2b1b0 et sur les bits b7b6b5b4 du registre AFRH
	GPIOA->AFR[1] &= ~(0x000000FF);
	GPIOA->AFR[1] |=  (0x00000022);

	// Activer horloge du Timer TIM1
	RCC -> APB2ENR |= RCC_APB2ENR_TIM1EN;

	// Faire un Reset de la configuration du TIM1 
	TIM1->CR1  = 0x0000;
	TIM1->CR2  = 0x0000;
	TIM1->CCER = 0x0000;

	// Configuration frequence de comptage
	// Prescaler : registre TIM61PSC
	// Fck = 48MHz -> /48 = 1MHz frequence de comptage : 1us de resolution
	TIM1->PSC = (uint16_t) 48 -1;


	// Configuration periode des evenements
	//ARR: registre TIM6_ARR
	// periode PWM = 11 ms 
	TIM1->ARR = (uint16_t) 11000;

	// Activer le registre Auto-Reload Preload 
	// prechargement 
	TIM1->CR1 |= TIM_CR1_ARPE;

	// Reset de la configuration 
	TIM1->CCMR1 = 0x0000;
	TIM1->CCMR2 = 0x0000;

	// Choix du mode PWM mode 1 pour les 2 cannaux 
	TIM1->CCMR1 |= (0x06 << 4) | TIM_CCMR1_OC1PE;
	TIM1->CCMR1 |= (0x06 << 12) | TIM_CCMR1_OC2PE;

	// Definir les valeurs initiales pour le rapport cyclique des 2 PWM 
	TIM1->CCR1 = 1500;
	TIM1->CCR2 = 1500;

	// Activer les sorties 
	TIM1->CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E;

	// Activer la sortie principale
	TIM1->BDTR |= TIM_BDTR_MOE;

	// Lancer le Timer TIM1 
	TIM1->CR1 |= TIM_CR1_CEN;
}
/*
* ADC_Init()
* Initialise ADC pour la conversion sur un seul canal
* canal 11 -> pin PC1
*/
void BSP_ADC_Init()
{
	// Activation de horloge du GPIOC
	// Mettre a '1' le bit b19 du registre RCC_AHBENR
	RCC->AHBENR |= (1<<18);
	
	// Configure les pins PC0 PC1 et PC2 en mode Analog
	// Mettre à "11" les bits b3b2 etc... du registre GPIOC_MODER
	//GPIOC->MODER &= ~GPIO_MODER_MODER1_Msk;
	GPIOC->MODER |= (0x03);
	GPIOC->MODER |= (0x03 <<2);
	GPIOC->MODER |= (0x03 <<4);
	
	// Activation de horloge de ADC
	// Mettre a '1' le bit b9 du registre RCC_APB2ENR
	// voir page 130 pour les autres bits
	RCC->APB2ENR |= (1<<9);
	
	// Reset de la configuration de ADC
	// Mise a zero des regsitres de configuration de ADC
	ADC1->CR = 0x00000000;
	ADC1->CFGR1 = 0x00000000;
	ADC1->CFGR2 = 0x00000000;
	ADC1->CHSELR = 0x00000000;
	
	// Choix du mode de conversion
	// bit b13 (CONT) du registre ADC1_CFGR1
	// '0' : conversion une seule fois : a la demande
	// '1' : conversion une en continue
	ADC1->CFGR1 |= (1<<13);
	
	// Choix de la resolution (nombre de bits des data)
	// bits b4b3 (Data resolution)
	// 00: 12 bits
	// 01: 10 bits
	// 10: 8 bits
	// 11: 6 bits
	ADC1->CFGR1 &= ~(0x03 <<4);
	
	// Choix de la source horloge pour ADC
	// bits b31b30 CKMODE[1:0]: ADC clock mode
	// 00: ADCCLK (Asynchronous clock mode), generated at product level (refer to RCC section)
	// 01: PCLK/2 (Synchronous clock mode)
	// 10: PCLK/4 (Synchronous clock mode)
	// 11: Reserved
	ADC1->CFGR2 |= (0x01 <<31UL);
	
	// Choix de la periode chantillonnage
	// Bits b2b1b0 (SMP[2:0]: Sampling time selection) du registre ADC sampling time register (ADC_SMPR)
	// 000: 1.5 ADC clock cycles
	// 001: 7.5 ADC clock cycles
	// 010: 13.5 ADC clock cycles
	// 011: 28.5 ADC clock cycles
	// 100: 41.5 ADC clock cycles
	// 101: 55.5 ADC clock cycles
	// 110: 71.5 ADC clock cycles
	// 111: 239.5 ADC clock cycles
	ADC1->SMPR = 0x03;
	
	// Selectionner le canal 11 pour la conversion
	// bit b11 du registre ADC channel selection register (ADC_CHSELR)
	// Select channel 10
	ADC1->CHSELR |= ADC_CHSELR_CHSEL10;
	
	// Mode single
	ADC1->CFGR1 &= ~(1<<13);
	
	// Activer ADC
	// Mettre a '1' le bit b0 du registre ADC_CR
	ADC1->CR |= (1<<0);
	
	// Demarrer la conversion
	// Mettre a '1' le bit b2 du registre ADC_CR
	ADC1->CR |= (1<<2);
}