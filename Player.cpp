#include "Canvas.h"
#include "Car.h"
#include "Player.h"

Player::Player(Canvas *canvas, int pos) : _canvas(canvas), pos(pos) {

}

bool Player::checkCollision(std::vector<Car> *cars) {
    bool collideInX = false;
    bool collideInY = false;

    for (Car car : *cars) {
        if (car.pos.y <= 0) collideInY = true;
    }
    if (!collideInY) return false;

    for (Car car : *cars) {
        if (car.pos.x <= pos && car.pos.x + car.width > pos) {
            collideInX = true;
            break;
        }
    }

    return collideInX;
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

