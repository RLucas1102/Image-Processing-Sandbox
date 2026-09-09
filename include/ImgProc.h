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
            long _Nsize;    // How big img data is
            float* _img;    // Image data stored contiguously

        public:
            ImgProc();
            ~ImgProc();

            void clear(); // Clean up image data and leave blank
            void clear(int Nx, int Ny, int Nc); // Clean up image data and reinitialize with new size

            // Accessors
            int GetNx() const;
            int GetNy() const;
            int GetNc() const;
            float* GetRaw() const;

            std::vector<float> GetValue(int i, int j) const; // Get value for specific pixel

            // Mutators
            void SetValue(int i, int j, const std::vector<float>& vals); // Set value for specific pixel

            // Deep copy methods
            ImgProc(const ImgProc& img); // Copy constructor
            ImgProc& operator=(const ImgProc& img); // Copy assignment

            // Open file
            bool Load(const std::string& filename);
            
    };
}

#endif