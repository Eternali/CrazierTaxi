#include <vector>
#include "Canvas.h"

class Leds : public Canvas {

public:
    Leds(unsigned int width, unsigned int height);
// 
    void begin();
    void render();

private:
    std::vector<std::vector<int>> pins = {};

};