enum Direction {
    LEFT,
    RIGHT
};

class Player {

public:
    Player(Canvas *canvas, int pos);

    bool checkCollision(std::vector<Car> *cars);
    void draw();
    void move(Direction dir);

    int pos;

private:
    Canvas *_canvas;

};
