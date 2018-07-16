#include <stdlib.h>
#include <time.h>

#include "Canvas.h"
#include "Leds.h"
#include "Car.h"
#include "Player.h"

const int leftPin = 2;
const int rightPin = 3;
//const int rstPin = 2;

volatile long int ms = 0;
const int ms = 256;
const int interval = ms * ;
const int spawnInt = 1000;

std::vector<std::vector<int>> pins {
    { 1, 4, 5, 6, 7, 8, 9, 10 },
    { 11, 12, 13 },
};
Leds canvas(3, 8, pins);
Player player(&canvas, 1);
std::vector<Car> cars {};

void setup() {
    cli();

    srand(time(NULL));
 
    pinMode(leftPin, INPUT_PULLUP);
    pinMode(rightPin, INPUT_PULLUP);
//    pinMode(rstPin, INPUT_PULLUP);

    TCCR1A = 0x0;  // reset Timer1 control registers
    TCCR1B = 0x0;  // set WGM_2:0 = 000
    TCCR1B = 0x4;  // set Timer1 to clk/256
    TIMSK1 = 0x6;  // enable OCR interrupt bits
    OCR1A = interval;  // set output compare value A

    Serial.begin(9600);
    canvas.begin();

//    attachInterrupt(digitalPinToInterrupt(leftPin), moveLeft, RISING);
//    attachInterrupt(digitalPinToInterrupt(rightPin), moveRight, RISING);
    attachInterrupt(0, moveLeft, RISING);  // digital input pin 2 is mapped to interrupt 0
    attachInterrupt(1, moveRight, RISING);  // digital input pin 3 is mapped to interrupt 0

    sei();
}
 
void loop() {
    if (ms % spawnInt == 0) {
      cars.push_back(Car(&canvas, Vector2<int>{ 8, rand() % 3 }, Vector2<int>{ 0, -1 }, 1000));
    }
    for (Car car : cars) {
        if (ms % car.updateInt == 0) {
            car.update();
        }
    }

//    if (player.checkCollision(&cars)) reset();
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

void reset() {
    cli();
    cars.clear();
    sei();
}

ISR (TIMER1_COMPA_vect) {
    for (Car car : cars) {
        if (interval % car.updateInt == 0) car.canMove = HIGH;
    }
    TCCR1A = 0x0;
}

ISR (TIMER1_COMPB_vect) {
    cars.push_back(Car(&canvas, Vector2<int>{ 8, rand() % 3 }, Vector2<int>{ 0, -1 }, 1000));
    TCCR1A = 0x0;
}

