#include <iostream>

#include "Stencil.h"

using namespace image;

int main() {

    Stencil myStencil = Stencil(1);

    myStencil(0,0) = -1;
    myStencil(0,1) = -1;
    myStencil(0,2) = -1;
    myStencil(1,0) = -1;
    myStencil(1,1) =  0;
    myStencil(1,2) = -1;
    myStencil(2,0) = -1;
    myStencil(2,1) = -1;
    myStencil(2,2) = -1;
    
    myStencil.print();

    return 0;
}