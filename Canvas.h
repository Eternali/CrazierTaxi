#include <Arduino.h>
#include <StandardCplusplus.h>
#include <vector>

class Canvas {

public:
    Canvas(unsigned int width, unsigned int height);

    virtual void begin() = 0;
    void clear();
    virtual void render() = 0;

    unsigned int width, height;
    std::vector<std::vector<int>> bmp;
    
};
