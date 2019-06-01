/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <jonas@jonasotto.com> wrote this file.  As long as you retain this notice
 * you can do whatever you want with this stuff. If we meet some day, and you
 * think this stuff is worth it, you can buy me a beer in return.    Jonas Otto
 * ----------------------------------------------------------------------------
 */

#ifndef STMNEOPIXEL_NEOPIXEL_H
#define STMNEOPIXEL_NEOPIXEL_H

#include <stm32l4xx_hal.h>
#include "fast_hsv2rgb.h"

#define LED_COUNT 64

#define SPI_NEO0 ((uint8_t) 0b11000000)
#define SPI_NEO1 ((uint8_t) 0b11111000)

typedef struct color {
    uint8_t G;
    uint8_t R;
    uint8_t B;
} Color;

void setLed(int i, Color color);

/**
 * Output LED Data vie DMI
 * @param hspi SPI Handle, should be set to 5MHz, Data Size 8Bit, CPHA = 1 ("2 Edge" in CubeMX)
 */
void show(SPI_HandleTypeDef *hspi);

/**
 * Create RGB color from HSV values.
 * All values in range 0-1
 * @param h Hue (Range: 0-1)
 * @param s Saturation (Range: 0-1)
 * @param v Value (Range: 0-1)
 */
Color hsvColor(float h, float s, float l);

#endif //STMNEOPIXEL_NEOPIXEL_H
