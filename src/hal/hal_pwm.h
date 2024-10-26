/**
 * @file hal_pwm.h
 * @brief Hardware abstraction layer for PWM operations.
 *
 * @author Ameed Othman
 * @date 2024-10-26
 */

#ifndef __HAL_PWM_H__
#define __HAL_PWM_H__

#include <stdint.h>

void PWM_Init(void);
void PWM_PlayTone(uint8_t pin, uint16_t frequency);
void PWM_StopTone(uint8_t pin);

#endif
