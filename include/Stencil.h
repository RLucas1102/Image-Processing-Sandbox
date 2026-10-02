#ifndef STENCIL_H
#define STENCIL_H

#include <memory>
#include <vector>
#include <iostream>

namespace image {

    // Stencil
    // Used for linear convolutions
    class Stencil
    { 
        public:

            Stencil(int halfwidth);
            ~Stencil() = default;

            // Accesors
            int getHalfW() const {return _hw;}

            // Overload to return stencil value
            float& operator()(int i, int j); 

            const float& operator()(int i, int j) const;

            void print();

        private:

            int _hw;
            std::vector<float> _stencil; // 1-D array of stencil values

    };

    // -------------------------------------------------------------------

    // Defining SSP to be a shared pointer of a stencil
    using SSP = std::shared_ptr<Stencil>;
    
    // -------------------------------------------------------------------

    // Helper functions
    // Functions to create and work with stencils outside of class

    // Create stencil
    SSP stencil(int halfwidth);

    // Find stencil based on halfwidth
    int stencilDim(int halfwidth);

    // -------------------------------------------------------------------

}

#endif