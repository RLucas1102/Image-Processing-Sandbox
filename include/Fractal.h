#ifndef FRACTAL_H
#define FRACTAL_H

#include <complex>

#include "ImgProc.h"

namespace image {

    struct Point {
        double X;
        double Y;
    };

    // Create a circle on the complex plane with a given radius and bounds
    void circle(const ImgProc& in, 
                      ImgProc& out, 
                      float radius, 
                      float bounds,
                      float zoom);

    // Create a Julia set on the complex plane
    void juliaSet(const ImgProc& in, 
                        ImgProc& out, 
                        float radius, 
                        float bounds,
                        double zoom,
                        int N,
                  const Point& center);

    // Find magnitude of a complex number
    double mod2(const Point& P);

} // namespace img

#endif