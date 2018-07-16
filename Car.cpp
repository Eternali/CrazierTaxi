#include "Canvas.h"
#include "Car.h"

Car::Car(Canvas *canvas, Vector2<int> pos, Vector2<int> vel)
 : _canvas(canvas), pos(pos), vel(vel) {

}

void Car::draw() {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            _canvas->bmp[pos.x + i][pos.y + j] = 1;
        }
    }
}

void Car::update() {
    pos.x += vel.x;
    pos.y += vel.y;
}
