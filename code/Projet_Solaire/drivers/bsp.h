/*
* bsp.h
*
* Created on: 14 févr. 2021
* Author: darga
*/
#ifndef BSP_INC_BSP_H_
#define BSP_INC_BSP_H_

#include "stm32f0xx.h"

/*
* fonctions du driver LED
*/
void BSP_LED_Init (void);
void BSP_LED_Toggle(void);
void BSP_LED_Off(void);
void BSP_LED_On(void);
void BSP_PB_Init(void);
uint8_t BSP_PB_GetState(void);
void BSP_Console_Init(void);


/*
 *  fonctions Timer
 */
void BSP_TIMER_Timebase_Init (void);

void BSP_TIMER_PWM_Init(void);


/*
 *  fonctions ADC
 */
void BSP_ADC_PA0Init(void);
void BSP_ADC_Init(void);



#endif /* BSP_INC_BSP_H_ */

