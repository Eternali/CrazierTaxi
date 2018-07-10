#include "Canvas.h"

Canvas::Canvas(unsigned int width, unsigned int height)
 : width(width), height(height) {
     clear();
}

void Canvas::clear() {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            bmp.at(j).at(i) = 0;
        }
    }
}