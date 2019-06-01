/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <jonas@jonasotto.com> wrote this file.  As long as you retain this notice
 * you can do whatever you want with this stuff. If we meet some day, and you
 * think this stuff is worth it, you can buy me a beer in return.    Jonas Otto
 * ----------------------------------------------------------------------------
 */

#include "neopixel.h"

#define BITSPERLED (sizeof(Color) * 8)

// 32: 32 Bytes at 5MHz = 51.2µs reset time
static uint8_t spiBuffer[LED_COUNT * BITSPERLED + 32];
static Color ledBuffer[LED_COUNT];

static void buildSPIbuffer() {
    for (int i = 0; i < LED_COUNT; i++) {

        uint8_t m = 0b10000000;
        for (int b = 0; b < 8; b++) {
            spiBuffer[BITSPERLED * i + b] = ledBuffer[i].G & m ? SPI_NEO1 : SPI_NEO0;
            m >>= 1u;
        }

        m = 0b10000000;
        for (int b = 0; b < 8; b++) {
            spiBuffer[BITSPERLED * i + b + 8] = ledBuffer[i].R & m ? SPI_NEO1 : SPI_NEO0;
            m >>= 1u;
        }

        m = 0b10000000;
        for (int b = 0; b < 8; b++) {
            spiBuffer[BITSPERLED * i + b + 16] = ledBuffer[i].B & m ? SPI_NEO1 : SPI_NEO0;
            m >>= 1u;
        }
    }
}

void setLed(int i, Color color) {
    ledBuffer[i] = color;
}

void show(SPI_HandleTypeDef *hspi) {
    buildSPIbuffer();
    HAL_SPI_Transmit_DMA(hspi, spiBuffer, sizeof(spiBuffer));
}

Color hsvColor(float h, float s, float v) {
    Color result;

    fast_hsv2rgb_32bit(h * HSV_HUE_MAX, s * HSV_SAT_MAX, v * HSV_VAL_MAX, &result.R, &result.G, &result.B);

    return result;
}
