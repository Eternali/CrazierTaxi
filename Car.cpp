#include "Car.h"

Car::Car(Canvas *canvas, int x, int y, int vel)
 : _canvas(canvas), x(x), y(y), vel(vel) {

}

void Car::draw() {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            _canvas->bmp.at(y + j).at(x + i) = 1;
        }
    }
}

void Car::update() {
    x += vel;
}
