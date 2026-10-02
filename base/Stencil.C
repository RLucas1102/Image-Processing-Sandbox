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
int image::stencilDim(int halfwidth)
{
    return 2 * halfwidth + 1;
}

Stencil image::blur(float val)
{
    Stencil result = Stencil(1);

    result(0,0) = val;
    result(0,1) = val;
    result(0,2) = val;
    result(1,0) = val;
    result(1,1) = val;
    result(1,2) = val;
    result(2,0) = val;
    result(2,1) = val;
    result(2,2) = val;

    return result;
    
}

Stencil image::random(int halfwidth)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<>dis(-0.1, 0.1);

    Stencil result = Stencil(halfwidth);

    float sum = 0;
    for (int j = 0; j < stencilDim(halfwidth); j++)
    {
        for (int i = 0; i < stencilDim(halfwidth); i++)
        {
            result(i,j) = dis(gen);
            sum += result(i,j);
        }
    }

    sum -= result(stencilDim(halfwidth)/2, stencilDim(halfwidth)/2);

    result(stencilDim(halfwidth)/2, stencilDim(halfwidth)/2) = 1.0 - sum;

    return result;
}

// -------------------------------------------------------------------
