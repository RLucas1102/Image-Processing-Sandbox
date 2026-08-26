#include "ImgProc.h"

using namespace image;

ImgProc::ImgProc() :
    _Nx(0),
    _Ny(0),
    _Nc(0),
    _Nsize(0),
    _img(0)
    {}

ImgProc::~ImgProc() {}

void ImgProc::clear() {}

void ImgProc::clear(int Nx, int Ny, int Nc) {}

int ImgProc::GetNx() const {}

int ImgProc::GetNy() const {}

int ImgProc::GetNc() const {}

std::vector<float> ImgProc::GetValue(int i, int j) const {}

void ImgProc::SetValue(int i, int j, const std::vector<float>& vals) {}

ImgProc::ImgProc(const ImgProc& img) {}

ImgProc& ImgProc::operator=(const ImgProc& img) {}