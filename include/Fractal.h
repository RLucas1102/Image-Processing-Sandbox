#ifndef FRACTAL_H
#define FRACTAL_H

#include <complex>

#include "ImgProc.h"

namespace image {

    struct Point {
        double X;
        double Y;
    };

    // Create a circle on the complex plane with a given radius
    void circle(const ImgProc& in, ImgProc& out, float radius, float bounds);

} // namespace img

#endif