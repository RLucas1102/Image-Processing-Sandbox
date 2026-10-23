#include "Fractal.h"

using namespace image;

void image::circle(const ImgProc& in, 
                         ImgProc& out, 
                         float radius, 
                         float bounds,
                         float zoom) 
{

    std::vector<float> black(in.GetNc(),0);
    std::vector<float> white(in.GetNc(),1);

    for(int j = 0; j < in.GetNy(); j++) {
        for (int i = 0; i < in.GetNx(); i++) {

            Point P;
            P.X = 2.0 * bounds * ((double)i / (double)in.GetNx()) - bounds;
            P.Y = 2.0 * bounds * ((double)j / (double)in.GetNy()) - bounds;
            P.X *= zoom;
            P.Y *= zoom;

            double mag = std::sqrt(P.X * P.X + P.Y * P.Y);

            if (mag <= radius) { out.SetValue(i, j, black); }
            else { out.SetValue(i, j, white); }

        }
    }
}


void image::juliaSet(const ImgProc& in, 
                           ImgProc& out, 
                           float radius, 
                           float bounds,
                           float zoom,
                           int N) 
{

    std::vector<float> black(in.GetNc(),0);

    std::vector<float> LUT(N,0);
    for(int m = 0; m < LUT.size(); m++) {
        LUT[m] = (double)m/(double)N;
    }

    for(int j = 0; j < in.GetNy(); j++) {
        for (int i = 0; i < in.GetNx(); i++) {

            Point P;
            P.X = 2.0 * bounds * ((double)i / (double)in.GetNx()) - bounds;
            P.Y = 2.0 * bounds * ((double)j / (double)in.GetNy()) - bounds;
            P.X *= zoom;
            P.Y *= zoom;

            std::complex<long double> z(P.X,P.Y);
            std::complex<long double> c(.274, -0.008);

            int n = 0;
            while (mod2(P) <= radius && n < N) {
                
                z = std::pow(z, 2);
                z += c;

                P.X = z.real();
                P.Y = z.imag();
                
                n++;

            }

            if (mod2(P) <= radius) { out.SetValue(i, j, black); }
            else { 
                float t = LUT[n];

                std::vector<float> red  = {1,0,0};
                std::vector<float> blue = {0,0,1};
                
                std::vector<float> color(in.GetNc(), 0);
                for (int k = 0; k < 3; k++) {
                    color[k] = (1 - t) * red[k] + t * blue[k];
                }

                out.SetValue(i, j, color);
            }

        }
    }
}

double image::mod2(const Point& P)
{
    return std::sqrt(P.X * P.X + P.Y * P.Y);
}