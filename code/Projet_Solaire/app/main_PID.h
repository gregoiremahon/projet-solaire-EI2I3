//
//  main_PID.h
//  
//
//  Created by Grégoire Mahon on 05/06/2023.
//

#ifndef main_PID_h
#define main_PID_h

#include <stdio.h>
#include "stm32f0xx.h"


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


#endif /* main_PID_h */
