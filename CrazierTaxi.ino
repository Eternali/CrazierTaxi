#include <stdlib.h>
#include <time.h>

#include "Canvas.h"
#include "Leds.h"
#include "Car.h"
#include "Player.h"

//const int leftPin = 2;
const int rightPin = 3;
//const int rstPin = 2;

volatile long int ms = 0;
long int frozenms = 0;
const int spawnInt = 1000;

std::vector<std::vector<int>> pins {
    { 2, 4, 5, 6, 7, 8, 9, 10 },
    { 11, 12, 13 },
};
Leds canvas(3, 8, pins);
Player player(&canvas, 1);
std::vector<Car> cars {};

void setup() {
    cli();

    srand(time(NULL));
 
//    pinMode(leftPin, INPUT_PULLUP);
    pinMode(rightPin, INPUT_PULLUP);
//    pinMode(rstPin, INPUT_PULLUP);

    TCCR0A = 0x0;  // reset Timer1 control registers
    TCCR0B = 0x0;  // set WGM_2:0 = 000
    TCCR0B = 0x3;  // set Timer1 to clk/64
    TIMSK0 = 0x6;  // enable OCR interrupt bits
    OCR0A = 256;  // set output compare value A
    OCR0B = 1024;  // set output compare value B

    Serial.begin(9600);
    canvas.begin();

//    attachInterrupt(digitalPinToInterrupt(leftPin), moveLeft, RISING);
//    attachInterrupt(digitalPinToInterrupt(rightPin), moveRight, RISING);
//    attachInterrupt(0, moveLeft, RISING);  // digital input pin 2 is mapped to interrupt 0
    attachInterrupt(1, moveRight, RISING);  // digital input pin 3 is mapped to interrupt 0

    sei();
}

void loop() {
    frozenms = ms;
//    Serial.println(frozenms);
  
    if (frozenms % spawnInt == 0) {
      cars.push_back(Car(&canvas, Vector2<int>{ rand() % 3, 7 }, Vector2<int>{ 0, -1 }, 800));
    }
    for (int c = 0; c < cars.size(); c++) {
        if (frozenms % cars[c].updateInt == 0) {
            if (cars[c].update()) {
              if (cars[c].pos.x == player.pos) {
                reset();
                break;
              }
              cars.erase(cars.begin() + c);
              c--;
            }
        }
    }

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

ISR (TIMER0_COMPA_vect) {
    cli();
    ms += 1;
    TCCR0A = 0x0;
    sei();
}

ISR (TIMER0_COMPB_vect) {
}

