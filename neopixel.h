#ifndef STMNEOPIXEL_NEOPIXEL_H
#define STMNEOPIXEL_NEOPIXEL_H

#include <stm32l4xx_hal.h>

#define LED_COUNT 9

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

#endif //STMNEOPIXEL_NEOPIXEL_H
