#include "Canvas.h"
#include "Car.h"

Car::Car(Canvas *canvas, Vector2<int> pos, Vector2<int> vel, int updateInt)
 : _canvas(canvas), pos(pos), vel(vel), updateInt(updateInt) {

}

void Car::draw() {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            _canvas->bmp[pos.x + i][pos.y + j] = 1;
        }
    }
}

bool Car::update() {
    pos.x += vel.x;
    pos.y += vel.y;

    return pos.y <= 0;
}
