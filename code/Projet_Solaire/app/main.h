/*
 * main.h
 *
 *  Created on: Feb 3, 2021
 *      Author: darga
 */

#include "stm32f0xx.h"
#ifndef MAIN_H
#define MAIN_H
#ifndef APP_INC_MAIN_H_
#define APP_INC_MAIN_H_

/*
 * printf() et sprintf() de la lib. printf-stdarg.c (@author : M.Darga)
 */


// Function Prototypes
static void SystemClock_Config(void);
static void Initialize_Variables(void);
static uint16_t Read_PhotoResistor(uint8_t channel);
static void Adjust_ServoAngles(void);



int mon_printf  (const char *format, ...);
int mon_sprintf (char *out, const char *format, ...);

#endif // MAIN_H
