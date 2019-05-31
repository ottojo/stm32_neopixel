#include "neopixel.h"

#define BITSPERLED (sizeof(Color) * 8)

static uint8_t SPIbuffer[LED_COUNT * BITSPERLED];
static Color ledBuffer[LED_COUNT];

static void buildSPIbuffer() {
    for (int i = 0; i < LED_COUNT; i++) {

        uint8_t m = 0b10000000;
        for (int b = 0; b < 8; b++) {
            SPIbuffer[BITSPERLED * i + b] = ledBuffer[i].G & m ? SPI_NEO1 : SPI_NEO0;
            m >>= 1u;
        }

        m = 0b10000000;
        for (int b = 0; b < 8; b++) {
            SPIbuffer[BITSPERLED * i + b + 8] = ledBuffer[i].R & m ? SPI_NEO1 : SPI_NEO0;
            m >>= 1u;
        }

        m = 0b10000000;
        for (int b = 0; b < 8; b++) {
            SPIbuffer[BITSPERLED * i + b + 16] = ledBuffer[i].B & m ? SPI_NEO1 : SPI_NEO0;
            m >>= 1u;
        }
    }
}

void setLed(int i, Color color) {
    ledBuffer[i] = color;
}

void show(SPI_HandleTypeDef *hspi) {
    buildSPIbuffer();
    HAL_SPI_Transmit_DMA(hspi, SPIbuffer, LED_COUNT * BITSPERLED);
}