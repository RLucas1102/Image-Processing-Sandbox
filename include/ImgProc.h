#ifndef IMGPROC_H
#define IMGPROC_H

#include <vector>

namespace image {

    class ImgProc
    {
        private:
            int _Nx;        // Number of pixels along x-axis
            int _Ny;        // Number of pixels along y-axis
            int _Nc;        // Number of channels per pixel
            long _Nsize;     // How big image is
            float* _img;    // Image data stored contiguously

        public:
            ImgProc();
            ~ImgProc();

            void clear();
            void clear(int Nx, int Ny, int Nc);

            // Accessors
            int GetNx() const;
            int GetNy() const;
            int GetNc() const;

            std::vector<float> GetValue(int i, int j) const; // Get value for specific pixel

            // Mutators
            void SetValue(int i, int j, const std::vector<float>& vals); // Set value for specific pixel

            ImgProc(const ImgProc& img); // Copy constructor
            ImgProc& operator=(const ImgProc& img); // Copy assignment
            


    };
}

#endif