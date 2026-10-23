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

    std::vector<std::vector<float>> LUT = {
        {1.0f,1.0f,0.0f},
        {0.0f,1.0f,0.0f},
        {0.0f,0.0f,1.0f}
    };

    int M = LUT.size();

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

                double weight    = (double)n/(double)N;
                double weightLUT = (double)M * weight;

                int m1 = std::floor(weightLUT);
                if (m1 >= M) { m1 = M - 1; }

                int m2 = std::ceil(weightLUT);
                if (m2 >= M) { m2 = M - 1; }

                std::vector<float> color1 = LUT[m1];
                std::vector<float> color2 = LUT[m2];
                std::vector<float> output(in.GetNc(), 0);

                for (int m = 0; m < 3; m++) {
                    output[m] = (1 - weight) * (double)color1[m] + weight * (double)color2[m];
                }

                out.SetValue(i, j, output);

            }

        }
    }
}

double image::mod2(const Point& P)
{
    return std::sqrt(P.X * P.X + P.Y * P.Y);
}