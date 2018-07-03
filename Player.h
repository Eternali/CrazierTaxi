#include "Canvas.h"

enum Direction {
    LEFT,
    RIGHT
};

class Player {

public:
    Player(Canvas *canvas, int pos);

    void draw();
    void move(Direction dir);

    int pos;

private:
    Canvas *_canvas;

};