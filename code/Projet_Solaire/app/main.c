# @author : Grégoire MAHON
# EI2I 3 - II

#include "stm32f0xx.h"
#include "bsp.h"
#include "delay.h"
#include "main.h"
#include <math.h>

#define FALSE 0
#define TRUE 1

// Function Prototypes
static void SystemClock_Config(void);
static void Initialize_Variables(void);
static uint16_t Read_PhotoResistor(uint8_t channel);
static void Adjust_ServoAngles(void);

// Global Variables
uint16_t average_light_intensity;
uint16_t diff_light_intensity_1_2;
uint16_t diff_light_intensity_12_3;
uint16_t light_intensity_1;
uint16_t light_intensity_2;
uint16_t light_intensity_3;
uint16_t tolerance_horizontal;
uint16_t tolerance_vertical;
uint8_t horizon;
uint8_t vertical;
uint16_t servo_angle_1;
uint16_t servo_angle_2;

int main() {
    // Configure System Clock
    BSP_Console_Init();
    mon_printf("Intialisation de la console OK!\r\n");

    // Initialize LED pin
    BSP_LED_Init();
    BSP_TIMER_PWM_Init();
    BSP_ADC_Init();
    mon_printf("Initialisation de l'ADC OK!\r\n");

    // Initialize state variables
    Initialize_Variables();

    while(1){
        light_intensity_1 = Read_PhotoResistor(10);
        light_intensity_2 = Read_PhotoResistor(11);
        light_intensity_3 = Read_PhotoResistor(12);
        Adjust_ServoAngles();
        BSP_DELAY_ms(1);
    }
}

static void Initialize_Variables(void) {
    servo_angle_1 = 2100;
    servo_angle_2 = 1200;
    tolerance_horizontal = 100; // 100 both
    tolerance_vertical = 100;
}

static uint16_t Read_PhotoResistor(uint8_t channel) {
    uint16_t light_intensity;
    ADC1->CHSELR = ADC_CHSELR_CHSEL10 + channel;
    ADC1->CR |= (1<<2); // Start conversion
    while((ADC1->ISR & (1<<2)) != (1<<2)); // Wait for conversion to finish
    light_intensity = (ADC1->DR)/1.23;
    return light_intensity;
}

static void Adjust_ServoAngles(void) {
    TIM1->CCR1 = servo_angle_1;
    TIM1->CCR2 = servo_angle_2;

    // Compute average light intensity
    average_light_intensity = (light_intensity_1 + light_intensity_2) / 2;

    // Adjust horizontal servo angle
    if (light_intensity_1 < light_intensity_2){
        diff_light_intensity_1_2 = abs(light_intensity_2 - light_intensity_1);
        if(diff_light_intensity_1_2 > tolerance_horizontal){
            if (servo_angle_2 < 2400){
                servo_angle_2++;
            }
        }
    }
    if (light_intensity_2 < light_intensity_1){
        diff_light_intensity_1_2 = abs(light_intensity_1 - light_intensity_2);
        if(diff_light_intensity_1_2 > tolerance_horizontal){
            if (servo_angle_2 > 600){
                servo_angle_2--;
            }
        }
    }

    // Adjust vertical servo angle
    if(average_light_intensity < light_intensity_3){
        diff_light_intensity_12_3 = abs(average_light_intensity - light_intensity_3);
        if(diff_light_intensity_12_3 > tolerance_vertical){
            if(servo_angle_1 < 3000){
                servo_angle_1++;
            }
        }
    }
    
    if(average_light_intensity > light_intensity_3){
        diff_light_intensity_12_3 = abs(light_intensity_3 - average_light_intensity);
        if(diff_light_intensity_12_3 > tolerance_vertical){
            if(servo_angle_1 > 1000){
                servo_angle_1--;
            }
        }
    }
}
