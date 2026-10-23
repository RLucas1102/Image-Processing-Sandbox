#include <iostream>

#include "ImgProc.h"
#include "Fractal.h"

using namespace image;

int main() {

    ImgProc temp;
    temp.clear(800, 800, 3);

    ImgProc display = temp;

    float radius = 4;
    float bounds = 5;
    float zoom = 0.1;
    float N = 100;
    // circle(temp, display, radius, bounds, zoom);
    juliaSet(temp, display, radius, bounds, zoom, N);

    display.Write("images/circle.png");

    return 0;
}