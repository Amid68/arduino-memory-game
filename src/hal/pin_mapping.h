/**
 * @file pin_mapping.h
 * @brief Header for pin mapping utility functions.
 *
 * @author Ameed Othman
 * @date 2024-10-26
 */

#ifndef __PIN_MAPPING_H__
#define __PIN_MAPPING_H__

#include <stdint.h>

/* Function prototype */
void map_pin_to_port(uint8_t pin, volatile uint8_t **ddr, volatile uint8_t **port, volatile uint8_t **pin_reg, uint8_t *bit_mask);

#endif

