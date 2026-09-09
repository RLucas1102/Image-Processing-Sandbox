#include <vector>
#include <OpenImageIO/imageio.h>

#include "ImgProc.h"

using namespace OIIO;
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

float* ImgProc::GetRaw() const { return _img; }

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

bool ImgProc::Load(const std::string& filename) {
    bool result = false;
    
    auto in = ImageInput::open(filename.c_str());
    
    if (in) {
        const ImageSpec &spec = in->spec();

        clear(spec.width, spec.height, spec.nchannels);

        // Find the size of each scanline based on the type stored in image (float) [1]
        int scanlinesize = spec.width * spec.nchannels * sizeof(_img[0]);

        in->read_image(0, 0, 0, spec.nchannels, 
                       TypeDesc::FLOAT, 
                       _img + (spec.height - 1) * spec.width * spec.nchannels, // offset to end
                       AutoStride,                                             // x stride
                       -scanlinesize);                                         // y stride
        in->close();
        
        result = true;

    }
    
    return result;

}


/**
 * Notes:
 * [1] If the image is 500 by 500 with 3 channels then the resulting scanlinesize will
 *     be 6000. OpenImageIO documentation gives an example for reading an image in such
 *     a way that is flips it (https://openimageio.readthedocs.io/en/v3.1.17.0/imageinput.html#data-strides).
 *     (char *)pixels+(yres-1)*scanlinesize does not work because pointer arithmetic already multiplies
 *     the number by the sizeof() the type. So, the offset for the image will be out of memory if
 *     scanlinesize is used (6000 * 4 = 24000 Bad -> 1500 * 4 = 6000 Good).
 * 
 * 
 * 
 * 
 * 
 * 
 */