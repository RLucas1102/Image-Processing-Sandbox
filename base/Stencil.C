#include "Stencil.h"

using namespace image;

// --------
// Stencil
// --------
image::Stencil::Stencil(int halfwidth) : _hw(halfwidth)
{
    
    int ssize = stencilDim(_hw) * stencilDim(_hw);

    _stencil.resize(ssize);

    #pragma omp parallel for
    for(long i = 0; i < ssize; i++) {
        _stencil[i] = 0;
    }
}

float &image::Stencil::operator()(int i, int j)
{
    return _stencil[i + stencilDim(_hw) * j];
}

const float &image::Stencil::operator()(int i, int j) const
{
    return _stencil[i + stencilDim(_hw) * j];
}

void image::Stencil::print()
{

    int ssize = stencilDim(_hw) * stencilDim(_hw);

    for(long i = 0; i < ssize; i++) {
        std::cout << _stencil[i] << std::endl;
    }
}

// -------------------------------------------------------------------

// -----------------
// Helper Functions
// -----------------
SSP image::stencil(int halfwidth)
{
    return std::make_shared<Stencil>(halfwidth);
}

int image::stencilDim(int halfwidth)
{
    return 2 * halfwidth + 1;
}

// -------------------------------------------------------------------
