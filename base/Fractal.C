#include "Fractal.h"

using namespace image;

void image::circle(const ImgProc& in, ImgProc& out, float radius, float bounds) {

    std::vector<float> black(in.GetNc(),0);
    std::vector<float> white(in.GetNc(),1);

    for(int j = 0; j < in.GetNy(); j++) {
        for (int i = 0; i < in.GetNx(); i++) {

            Point P;
            P.X = 2.0 * bounds * ((double)i / (double)in.GetNx()) - bounds;
            P.Y = 2.0 * bounds * ((double)j / (double)in.GetNy()) - bounds;

            double mag = std::sqrt(P.X * P.X + P.Y * P.Y);

            if (mag <= radius) { out.SetValue(i, j, black); }
            else { out.SetValue(i, j, white); }

        }
    }
}