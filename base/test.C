#include <iostream>

#include "Stencil.h"

using namespace image;

int main() {

    Stencil myStencil = Stencil(1);

    myStencil(-1,-1) = -1;
    myStencil(-1,0) = -1;
    myStencil(-1,1) = -1;
    myStencil(0,-1) = -1;
    myStencil(0,0) =  0;
    myStencil(0,1) = -1;
    myStencil(1,-1) = -1;
    myStencil(1,0) = -1;
    myStencil(1,1) = -1;
    
    myStencil.print();

    return 0;
}