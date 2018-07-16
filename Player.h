enum Direction {
    LEFT,
    RIGHT
};

class Player {

public:
    Player(Canvas *canvas, int pos);

    void draw();
    void move(Direction dir);
    void win();
    void loose();

    int pos;
    long int lastLost = 0;

private:
    Canvas *_canvas;

};
