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

