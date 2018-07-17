#include <stdlib.h>
#include <time.h>

#include "Canvas.h"
#include "Leds.h"
#include "Car.h"
#include "Player.h"

const int leftPin = 3;
const int rightPin = 2;
//const int rstPin = 2;

volatile long int lastPressed = 0;
volatile long int spawn = 0;
volatile long int canMove = 0;

volatile long int frozenms = 0;
const int spawnInt = 2;
const int tolerance = 0;

int highScore = 0;

std::vector<std::vector<int>> pins {
  { 4, 5, 6, 7, 8, 9, 10 },
  { 11, 12, 13 },
};
Leds canvas(3, 7, pins);
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
  TCCR1B = 0x3;  // set Timer1 to clk/64
  TCCR0B = 0x2;  // set Timer0 to clk/8
  TIMSK1 = 0x6;  // enable OCR interrupt bits
  OCR1A = 62500;  // set output compare value A to 1/4 second (1 second = 62500)
  OCR1B = 1024;  // set output compare value B

  Serial.begin(9600);
  canvas.begin();

  //    attachInterrupt(digitalPinToInterrupt(leftPin), moveLeft, RISING);
  //    attachInterrupt(digitalPinToInterrupt(rightPin), moveRight, RISING);
      attachInterrupt(0, moveRight, RISING);  // digital input pin 2 is mapped to interrupt 0
  attachInterrupt(1, moveLeft, RISING);  // digital input pin 3 is mapped to interrupt 0

  sei();
}

void loop() {
//  frozenms = ms;
  //    Serial.println(frozenms);

  if (spawn >= spawnInt) {
//          Serial.println(frozenms);
    cars.push_back(Car(&canvas, Vector2<int> { rand() % 3, 8 }, Vector2<int> { 0, -1 }, rand() % 3 + 1));
    spawn = 0;
  }
  if (canMove) {
  for (int c = 0; c < cars.size(); c++) {
      if (cars[c].update()) {
        if (cars[c].pos.x == player.pos) {
          reset();
          break;
        }
        cars.erase(cars.begin() + c);
        c--;
      }
    }
    canMove = 0;
  }

  canvas.clear(0);
  for (Car car : cars) car.draw();
  player.draw();
  canvas.render();

  //    ms = frozenms;
}

void moveLeft() {
  cli();
  if (millis() - lastPressed > 640) {
    player.move(LEFT);
    lastPressed = millis();
  }
  sei();
}

void moveRight() {
  cli();
  if (millis() - lastPressed > 640) {
    player.move(RIGHT);
    lastPressed = millis();
  }
  sei();
}

void reset() {
  cars.clear();
  highScore = player.loose(highScore);
}

ISR (TIMER1_COMPA_vect) {
  cli();
  spawn += 1;
  canMove = 1;
  TCCR1A = 0x0;
  sei();
}

ISR (TIMER1_COMPB_vect) {
}

