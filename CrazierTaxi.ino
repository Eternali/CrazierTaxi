#include <stdlib.h>
#include <time.h>

#include "Shared.h"
#include "Canvas.h"
#include "Leds.h"
#include "Car.h"
#include "Player.h"

const int interruptPin = 2;
volatile int btnVal = 0;

volatile long int ms = 0;
volatile long int lastPressed = 0;
volatile long int spawn = 0;
volatile long int canMove = 0;
volatile int spawnInt = 3;

const int tolerance = 0;

int highScore = 0;

std::vector<std::vector<int>> pins {
  { 3, 4, 5, 6, 7, 8, 9, 10 },
  { 11, 12, 13 },
};
Leds canvas(3, 8, pins);
Player player(&canvas, 1);
std::vector<Car> cars {};

void setup() {
  cli();

  srand(time(NULL));

  pinMode(interruptPin, INPUT_PULLUP);
 
  TCCR1A = 0x0;  // reset Timer1 control registers
  TCCR1B = 0x0;  // set WGM_2:0 = 000
  TCCR1B = 0x3;  // set Timer1 to clk/64
  TIMSK1 = 0x6;  // enable OCR interrupt bits
  OCR1A = 62500;  // set output compare value A to 1/4 second (1 second = 62500)
  OCR1B = 1024;  // set output compare value B

  TCCR0B = 0x2;  // set Timer0 to clk/8

  TCCR2A = 0x0;  // reset Timer1 control registers
  TCCR2B = 0x3;  // set Timer1 to clk/64
  TIMSK2 = 0x6;  // enable OCR interrupt bits
  OCR2A = 256;  // set output compare value A 1 millisecond
  OCR2B = 256;  // set output compare value B


  Serial.begin(9600);
  canvas.begin();

  attachInterrupt(0, btnInterrupt, RISING);  // digital input pin 2 is mapped to interrupt 0
  
  sei();
}

void loop() {

  if (spawn >= spawnInt) {
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

}

void reset() {
  cars.clear();
  highScore = player.loose(highScore);
}

void btnInterrupt() {
  cli();
  btnVal = analogRead(A0);
  
  if (ms - lastPressed > 100) {
    if (btnVal >= 1015 && btnVal <= 1023) {  // left button
      player.move(LEFT);
    } else if (btnVal >= 980 && btnVal <= 990) {  // right button
      player.move(RIGHT);
    } else if (btnVal >= 926 && btnVal <= 936) {  // difficulty decrease button
      spawnInt++;
    } else if (btnVal >= 855 && btnVal <= 865) {  // difficulty increase button
      if (spawnInt > 1) spawnInt--;
    } else if (btnVal >= 700 && btnVal <= 716) {  // reset button
      reset();
    }
    lastPressed = ms;
  }

  sei();
}

void moveLeft() {
  cli();
  // only register button press if more than 80 ms have passed since the last one
  if (ms - lastPressed > 80) {
    player.move(LEFT);
    lastPressed = ms;
  }
  sei();
}

void moveRight() {
  cli();
  // only register button press if more than 80 ms have passed since the last one
  if (ms - lastPressed > 80) {
    player.move(RIGHT);
    lastPressed = ms;
  }
  sei();
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


ISR (TIMER2_COMPA_vect) {
  cli();
  ms += 1;
  TCCR2A = 0x0;
  sei();
}

ISR (TIMER2_COMPB_vect) {
}

