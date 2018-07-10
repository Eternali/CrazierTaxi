#include "Canvas.h"
#include "Leds.h"
#include "Car.h"
#include "Player.h"

const int leftPin = 1;
const int rightPin = 0;

std::vector<std::vector<int>> pins {
    { 3, 4, 5, 6, 7, 8, 9, 10 },
    { 11, 12 },
};
Leds canvas(2, 8, pins);
Player player(&canvas, 1);
// Car cars[10];

void setup() {
    pinMode(leftPin, INPUT_PULLUP);
    pinMode(rightPin, INPUT_PULLUP);
    Serial.begin(9600);
    canvas.begin();
    attachInterrupt(digitalPinToInterrupt(leftPin), moveLeft, CHANGE);
    attachInterrupt(digitalPinToInterrupt(rightPin), moveRight, CHANGE);
}
 
void loop() {
    canvas.clear();
    // for (Car car : cars) car.draw();
    player.draw();
    canvas.render();
}

void moveLeft() {
    player.move(LEFT);
}

void moveRight() {
    player.move(RIGHT);
}
