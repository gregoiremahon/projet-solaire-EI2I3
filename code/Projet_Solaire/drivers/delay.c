/*
* delay.c
*
* Created on: 15 févr. 2021
* Author: darga
*/
#include "delay.h"
/*
* Fonctions Basiques pour temporisation software
*/
void BSP_DELAY_ms(uint32_t delay)
{
    uint32_t i;
    for(i=0; i<(delay*6000); i++) ;
     // adapter la valeur du coef selon la frequence du CPU
}

void BSP_DELAY_us(uint32_t delay)
{
    uint32_t i;
    for(i=0; i<(delay*10); i++);
     // adapter la valeur du coef selon la frequence du CPU
}

/*
 * BSP_DELAY_TIM_init   ()
 * Initialise TIM6 avec
 * Prescaler (PSC)  = 48000 -> periode de comptage = 1ms
 * Auto-reload (ARR) = mis a sa valeur max  -> delais [2ms-65s]
 */

void BSP_DELAY_TIM_init     (void)
{
    // activer horloge du peripherique TIM6
    // mettre a '1' le bit b4 (TIM6EN) du registre RCC_APB1ENR
    // voir page 131 du manuel de reference
    RCC->APB1ENR |= (1<<4);            

    // Faire un Reset de config du TIM6 : mise a zero des registres
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
    TIM6->ARR = (uint16_t) 0xFFFF;
}

/*
 * timer_delay_ms(uint16_t ms)
 * attentes ici pendant du duree ms
 */

void BSP_DELAY_TIM_ms(uint16_t ms)
{
    // On commence par faire 
    // un Reset du compteur du Timer
    // bit b0  du registre TIMx_EGR
    // '0' : Pas effet : rien
    // '1' : reinitialise le compteur (CNT) du Timer 
    //       et met a jour les registres du Timer
    TIM6->EGR |= (1<<0);

    // Demarrer le Timer TIM6
    // Mettre a '1' le bit b0 du registre TIM6_CR1
    TIM6->CR1 |= (1<<0);

    // Attendre jusqua ce que 
    // le compteur de TIM6 atteigne la valeur ms
    while(TIM6->CNT < ms);

    // Arreter le Timer TIM6
    // Mettre a '0' le bit b0 du registre TIM6_CR1
    TIM6->CR1 &= ~(1<<0);
}


/*
 * BSP_DELAY_TIM3_init   ()
 * Initialise TIM3 avec
 * Prescaler (PSC)  = 48000 -> periode de comptage = 1ms
 * Auto-reload (ARR) = mis a sa valeur max  -> delais [2ms-65s]
 */

void BSP_DELAY_TIM3_init     (void)
{
    // activer horloge du peripherique TIM6
    // mettre a '1' le bit b1 (TIM3EN) du registre RCC_APB1ENR
    // voir page 131 du manuel de reference
    RCC->APB1ENR |= (1<<1);            

    // Faire un Reset de config du TIM3 : mise a zero des registres
    // TIM3_CR1 et TIM3_CR2
    // voir page 543 a 544 du manuel de reference
    TIM3->CR1 = 0x0000;
    TIM3->CR2 = 0x0000;

    // Configuration frequence de comptage
    // Prescaler : registre TIM3_PSC
    // Fck = 48MHz -> /48000 = 1KHz frequence de comptage
    TIM3->PSC = (uint16_t) 48000 -1;

    // Configuration periode des evenements
    // Prescaler : registre TIM6_ARR
    // 1000 /1000 = 1s
    TIM3->ARR = (uint16_t) 0xFFFF;
}

/*
 * timer_delay_ms(uint16_t ms)
 * attentes ici pendant du duree ms
 */

void BSP_DELAY_TIM3_ms(uint16_t ms)
{
    // On commence par faire 
    // un Reset du compteur du Timer
    // bit b0  du registre TIMx_EGR
    // '0' : Pas effet : rien
    // '1' : reinitialise le compteur (CNT) du Timer 
    //       et met a jour les registres du Timer
    TIM3->EGR |= (1<<0);

    // Demarrer le Timer TIM3
    // Mettre a '1' le bit b0 du registre TIM3_CR1
    TIM3->CR1 |= (1<<0);

    // Attendre jusqua ce que 
    // le compteur de TIM6 atteigne la valeur ms
    while(TIM3->CNT < ms);

    // Arreter le Timer TIM6
    // Mettre a '0' le bit b0 du registre TIM6_CR1
    TIM3->CR1 &= ~(1<<0);
}



