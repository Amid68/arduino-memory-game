/**
 * @file hal_gpio.h
 * @brief Hardware abstraction layer for GPIO operations.
 *
 * @author Ameed Othman
 * @date 2024-10-18
 */

#ifndef __HAL_GPIO_H__
#define __HAL_GPIO_H__

#include <stdint.h>

/* GPIO States */
#define HIGH 1
#define LOW 0

/* Function prototypes */
void GPIO_SetPinInputPullup(uint8_t pin);
void GPIO_SetPinOutput(uint8_t pin);
void GPIO_WritePin(uint8_t pin, uint8_t state);
uint8_t GPIO_ReadPin(uint8_t pin);

#endif
