#include "Canvas.h"
#include "Leds.h"

Leds::Leds(unsigned int width, unsigned int height, std::vector<std::vector<int>> pins) : pins(pins), Canvas(width, height) {

}

void Leds::begin() {
    for (std::vector<int> line : pins) {
        for (int pin : line) {
            pinMode(pin, OUTPUT);
        }
    }
}

void Leds::render() {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            digitalWrite(pins[0][j], bmp[i][j]);
            digitalWrite(pins[1][i], !bmp[i][j]);
            if (bmp[i][j]) {
                delay(1);
                digitalWrite(pins[0][j], LOW);
                digitalWrite(pins[1][i], HIGH);
            }
        }
    }
}
