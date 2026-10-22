#include <iostream>

#include "ImgProc.h"
#include "Fractal.h"

using namespace image;

int main() {

    ImgProc temp;
    temp.clear(800, 800, 3);

    ImgProc display = temp;

    circle(temp, display, 4, 10);

    display.Write("images/circle.png");

    return 0;
}