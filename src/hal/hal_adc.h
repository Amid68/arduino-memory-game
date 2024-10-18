/**
 * @file hal_adc.h
 * @brief Hardware abstraction layer for ADC operations.
 *
 * @author Ameed Othman
 * @date 2024-10-18
 */

#ifndef __HAL_ADC_H__
#define __HAL_ADC_H__

#include <stdint.h>

/* Function prototypes */
void ADC_Init(void);
uint16_t ADC_Read(uint8_t channel);

#endif
