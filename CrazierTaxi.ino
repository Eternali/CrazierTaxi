#include "Canvas.h"
#include "Leds.h"
#include "Car.h"
#include "Player.h"

const int leftPin = 2;
const int rightPin = 3;
//const int rstPin = 2;

std::vector<std::vector<int>> pins {
    { 1, 4, 5, 6, 7, 8, 9, 10 },
    { 11, 12, 13 },
};
Leds canvas(3, 8, pins);
Player player(&canvas, 1);
std::vector<Car> cars {};

void setup() {
    cli();
 
    pinMode(leftPin, INPUT_PULLUP);
    pinMode(rightPin, INPUT_PULLUP);
//    pinMode(rstPin, INPUT_PULLUP);

    Serial.begin(9600);
    canvas.begin();

//    attachInterrupt(digitalPinToInterrupt(leftPin), moveLeft, RISING);
//    attachInterrupt(digitalPinToInterrupt(rightPin), moveRight, RISING);
    attachInterrupt(0, moveLeft, RISING);  // digital input pin 2 is mapped to interrupt 0
    attachInterrupt(1, moveRight, RISING);  // digital input pin 3 is mapped to interrupt 0

    sei();
}
 
void loop() {
    if (player.checkCollision(&cars)) reset();
    canvas.clear();
    for (Car car : cars) car.draw();
    player.draw();
    canvas.render();
}

void moveLeft() {
    cli();
    player.move(LEFT);
    sei();
}

void moveRight() {
    cli();
    player.move(RIGHT);
    sei();
}

void spawnCar() {
    cars.push_back(Car(&canvas, Vector2<int>{ 8, 0 }, Vector2<int>{ 0, -1 }));
}

void reset() {
    cli();
    cars.clear();
    sei();
}
