/***********************************************************************
 * 
 * ImgProc.C
 * 
 * Desc: ImgProc acts a robust data container to load, write, and 
 *       manipulate image data by using OpenImageIO
 * 
 * Created by: Lucas Robenolt
 * 
 * 
 ***********************************************************************/


#include <vector>
#include <OpenImageIO/imageio.h>

#include "ImgProc.h"

using namespace OIIO;
using namespace image;

// --------
// ImgProc
// --------
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

int image::ImgProc::GetNsize() const { return _Nsize; }

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

ImgProc::ImgProc(const ImgProc& v) :
    _Nx (v.GetNx()),
    _Ny (v.GetNy()),
    _Nc (v.GetNc()),
    _Nsize (v.GetNsize())
{
    _img = new float[_Nsize];
    #pragma omp parallel for
    for( long i=0; i< _Nsize; i++){ _img[i] = v.GetRaw()[i]; }
}

ImgProc& ImgProc::operator=(const ImgProc& v)
{
    if( this == &v ){ return *this; }
    if( _Nx != v.GetNx() || _Ny != v.GetNy() || _Nc != v.GetNc() )
    {
        clear(v.GetNx(), v.GetNy(), v.GetNc());
        _Nsize = v.GetNsize();
        _img = new float[_Nsize];
    }
    #pragma omp parallel for
    for( long i=0; i<_Nsize; i++){ _img[i] = v.GetRaw()[i]; }
    return *this;
}

// A variation of the method used in OpenImageIO documentation
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

// From OpenImageIO documentation
bool ImgProc::Write( const std::string& filename) const {

    std::unique_ptr<ImageOutput> out = ImageOutput::create(filename.c_str());
    
    if (!out) { return false; } // error
    
    ImageSpec spec(_Nx, _Ny, _Nc, TypeDesc::FLOAT);
    
    out->open(filename.c_str(), spec);
    
    out->write_image(TypeDesc::FLOAT, _img);
    
    out->close();
    
    return true;
}

void ImgProc::gamma(float s) 
{
    #pragma omp parallel for
    for (long i = 0; i < _Nsize; i++) {
        _img[i] = std::pow(_img[i], s);
    }
}

void ImgProc::unboundedLinearConvolution(const Stencil &stencil, ImgProc &out) const
{
    out.clear( this->GetNx(), this->GetNy(), this->GetNc() );

    for( int j=0;j<out.GetNy();j++)
    { 
        #pragma omp parallel for
        for(int i=0;i<out.GetNx();i++)
        {
            std::vector<float> pixel(out.GetNc(),0.0);
            std::vector<float> sample(this->GetNc(),0.0);

            for(int jj=-stencil.getHalfW();jj<=stencil.getHalfW();jj++)
            {
                int stencilj = jj + stencil.getHalfW();
                int jjj = j + jj;
                if(jjj < 0 ){ jjj += out.GetNy(); }
                if(jjj >= out.GetNy() ){ jjj -= out.GetNy(); }

                for(int ii=-stencil.getHalfW();ii<=stencil.getHalfW();ii++)
                {
                    int stencili = ii + stencil.getHalfW();
                    int iii = i + ii;
                    if(iii < 0 ){ iii += out.GetNx(); }
                    if(iii >= out.GetNx() ){ iii -= out.GetNx(); }
                    const float& stencil_value = stencil(stencili, stencilj);
                    sample = this->GetValue(iii,jjj);
                    for(size_t c=0;c<sample.size();c++){ pixel[c] += sample[c] * stencil_value; }
                }
            }
            
            out.SetValue(i,j,pixel);
        }
    }
}

//----------------------------------------------------------------

// ----------------
// Helper Functions
// -----------------

// Pixel-by-pixel image manipulation
void image::gamma(float s, ImgProc &img)
{
    img.gamma(s);
}

// Convolution image manipulation
void image::unboundedLinearConvolution(const Stencil& stencil, const ImgProc& in, ImgProc& out) 
{
    in.unboundedLinearConvolution(stencil, out);
}

//----------------------------------------------------------------


/**
 * Notes:
 * [1] If the image is 500 by 500 with 3 channels then the resulting scanlinesize will
 *     be 6000. OpenImageIO documentation gives an example for reading an image in such
 *     a way that is flips it (https://openimageio.readthedocs.io/en/v3.1.17.0/imageinput.html#data-strides).
 *     (char *)pixels+(yres-1)*scanlinesize does not work because pointer arithmetic already multiplies
 *     the number by the sizeof() the type. So, the offset for the image will be out of memory if
 *     scanlinesize is used (6000 * 4 = 24000 Bad -> 1500 * 4 = 6000 Good).
 * 
 * [2] Doing an internal/external hybrid for class operations has several benefits
 *     1. Allows nested called like gamma(bias(copy(img)))
 *     2. Operation can be parallel friendly
 *     3. Allows implicit type casting
 * 
 * [3] Passing by const type& allows for temporary variables like literals and
 *     function returns to be passed into functions directly, essentially passing
 *     by value, and high perfomance with passing the pointer to the object
 * 
 * 
 */