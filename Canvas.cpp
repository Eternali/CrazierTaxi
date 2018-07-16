#include "Canvas.h"

Canvas::Canvas(unsigned int width, unsigned int height)
 : width(width), height(height) {
    for (int i = 0; i < width; i++) {
        bmp.push_back(std::vector<int>());
        for (int j = 0; j < height; j++) {
            bmp[i].push_back(0);
        }
    }
}

void Canvas::clear(int col) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            bmp[i][j] = col;
        }
    }
}
