#include <Arduino.h>
#include "Leds.h"

Leds::Leds(unsigned int width, unsigned int height) : Canvas(width, height) {

}

void Leds::begin() {

}

void Leds::render() {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            digitalWrite(pins[j][i], bmp[j][i]);
        }
    }
}
