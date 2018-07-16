template <typename T>
struct Vector2 {
    T x;
    T y;
};

class Car {

public:
    Car(Canvas *canvas, Vector2<int> pos, Vector2<int> vel);

    void draw();
    void update();

    Vector2<int> pos;
    Vector2<int> vel;
    int width = 1;
    int height = 1;

private:
    Canvas *_canvas;

};