#pragma once
#include "../../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal.h"

/**
 * @brief Ustaw pin jako output
 * 
 * @param GPIOx Szereg portu GPIO
 * @param GPIO_Pin Port GPIO
 */
void Set_Pin_Output (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

/**
 * @brief Ustaw pin jako input
 * 
 * @param GPIOx Szereg portu GPIO
 * @param GPIO_Pin Port GPIO
 */
void Set_Pin_Input (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

/**
 * @brief Delay na mikrosekundę
 * 
 * @param us ilość mikrosekund opóźnienia
 */
void delay_us(uint16_t us);