#include "ImgProc.h"

using namespace image;

ImgProc::ImgProc() :
    _Nx(0),
    _Ny(0),
    _Nc(0),
    _Nsize(0),
    _img(0)
    {}

ImgProc::~ImgProc() { clear(); }

void ImgProc::clear() {
    if (_img != 0) {
        delete[] _img;
        _img = 0;
    }

    _Nx    = 0;
    _Ny    = 0;
    _Nc    = 0;
    _Nsize = 0;
    
}

void ImgProc::clear(int Nx, int Ny, int Nc) {
    clear();
    
    _Nx = Nx;
    _Ny = Ny;
    _Nc = Nc;

    _Nsize = (long)_Nx * (long)_Ny * (long)_Nc;
    _img   = new float[_Nsize];

    #pragma omp parallel for
    for(long i = 0; i < _Nsize; i++) {
        _img[i] = 0;
    }
}

int ImgProc::GetNx() const { return _Nx; }

int ImgProc::GetNy() const { return _Ny; }

int ImgProc::GetNc() const { return _Nc; }

std::vector<float> ImgProc::GetValue(int i, int j) const {
    std::vector<float> result(_Nc);

    for (int c = 0; c < _Nc; c++) {
        // Find channel value (c) of given pixel in contiguous memory
        result[c] = _img[c + _Nc*(i + _Nx*j)];
    }

    return result;

}

void ImgProc::SetValue(int i, int j, const std::vector<float>& vals) {
    for(int c = 0; c < _Nc; c++) {
        // Find channel value (c) of given pixel in contiguous memory and overwrite
        _img[c + _Nc*(i + _Nx*j)] = vals[c];
    }
}

ImgProc::ImgProc(const ImgProc& img) {}

ImgProc& ImgProc::operator=(const ImgProc& img) {}