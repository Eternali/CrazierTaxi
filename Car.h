#include "Canvas.h"

class Car {

public:
    Car(Canvas *canvas, int x, int y, int vel);

    void draw();
    void update();

    int width = 1;
    int height = 1;
    int x, y, vel;

private:
    Canvas *_canvas;

};