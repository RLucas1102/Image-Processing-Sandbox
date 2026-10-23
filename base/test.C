#include <iostream>
#include <sstream>
#include <iomanip>

#include "ImgProc.h"
#include "Fractal.h"

using namespace image;

int main() {

    int n_frames = 240;
    double start_zoom_pow = 0;
    double end_zoom_pow = -6;
    double zoom_inc_pow = (end_zoom_pow - start_zoom_pow) / n_frames;
    double start_zoom = 1.0 * std::pow(10, start_zoom_pow);

    ImgProc temp;
    temp.clear(800, 800, 3);

    ImgProc display = temp;

    float radius = 4;
    float bounds = 5;
    double zoom = start_zoom;
    float N = 100;
    
    Point center;
    center.X = 0.03811;
    center.Y = 0.01329;
    
    for(int k = 0; k <= n_frames; k++) {
        std::cout << zoom << std::endl;
        juliaSet(temp, display, radius, bounds, zoom, N, center);
        zoom *= std::pow(10, zoom_inc_pow);
        
        std::stringstream ss;
        ss << "images/fractal_N100/fractal_N100." << std::setw(4) << std::setfill('0') << k << ".exr";
        std::string filename = ss.str();
        display.Write(filename);

        std::cout << "\n" << ss.str() << " complete!" << std::endl;
    }


    return 0;
}