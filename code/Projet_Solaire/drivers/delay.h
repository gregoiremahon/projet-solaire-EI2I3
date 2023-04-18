/*
* delay.h
*
* Created on: 15 févr. 2021
* Author: darga
*/
#ifndef BSP_INC_DELAY_H_
#define BSP_INC_DELAY_H_
#include "stm32f0xx.h"
/*
* Delais attentes ou temporisation Software
*/
void BSP_DELAY_ms (uint32_t delay);
void BSP_DELAY_us (uint32_t delay);

/*
 * Delais avec un Timer : TIM6
 */

void BSP_DELAY_TIM_init     (void);
void BSP_DELAY_TIM_ms       (uint16_t ms);

void BSP_DELAY_TIM3_init     (void);
void BSP_DELAY_TIM3_ms(uint16_t ms);

#endif /* BSP_INC_DELAY_H_ */
