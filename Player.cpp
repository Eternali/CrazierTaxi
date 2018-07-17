#include "Shared.h"
#include "Canvas.h"
#include "Car.h"
#include "Player.h"

Player::Player(Canvas *canvas, int pos) : _canvas(canvas), pos(pos) {

}

void Player::draw() {
    _canvas->bmp[pos][0] = 1;
}

void Player::move(Direction dir) {
    switch (dir) {
        case LEFT:
            if (pos > 0) pos--;
            break;
        case RIGHT:
            if (pos < _canvas->width - 1) pos++;
            break;
    }
}

int Player::loose(int highScore) {
  int score = (ms - lastLost) / 1000;
  Serial.print("High score: ");
  Serial.print(highScore);
  Serial.println(" seconds");
  Serial.print("Your time: ");
  Serial.print(score);
  Serial.println(" seconds");
  if (score > highScore) {
    Serial.println("Congratulations! You have beaten the old highscore!");
  }

  for (int i = 0; i < 5; i++) {
    _canvas->clear(1);
    _canvas->render();
    delay(250 * 8);
    _canvas->clear(0);
    _canvas->render();
    delay(250 * 8);
  }
  lastLost = ms;

  Serial.println("");
  return score > highScore ? score : highScore;
}

