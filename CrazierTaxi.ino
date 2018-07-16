#include "Canvas.h"
#include "Leds.h"
#include "Car.h"
#include "Player.h"

const int leftPin = 2;
//const int rightPin = 0;
//const int rstPin = 2;

std::vector<std::vector<int>> pins {
    { 3, 4, 5, 6, 7, 8, 9, 10 },
    { 11, 12, 13 },
};
Leds canvas(3, 8, pins);
Player player(&canvas, 1);
std::vector<Car> cars {};

void setup() {
    pinMode(leftPin, INPUT_PULLUP);
//    pinMode(rightPin, INPUT_PULLUP);
//    pinMode(rstPin, INPUT_PULLUP);

    Serial.begin(9600);
    canvas.begin();

//    attachInterrupt(digitalPinToInterrupt(leftPin), moveLeft, CHANGE);
//    attachInterrupt(digitalPinToInterrupt(rightPin), moveRight, CHANGE);
//    attachInterrupt(digitalPinToInterrupt(rstPin), reset, RISING);
}
 
void loop() {
//    if (player.checkCollision(&cars)) reset();
    canvas.clear();
//    for (Car car : cars) car.draw();
    player.draw();
    canvas.render();
}

void moveLeft() {
    player.move(LEFT);
}

void moveRight() {
    player.move(RIGHT);
}

void spawnCar() {
    cars.push_back(Car(&canvas, Vector2<int>{ 8, 0 }, Vector2<int>{ 0, -1 }));
}

void reset() {
    cars.clear();
}
