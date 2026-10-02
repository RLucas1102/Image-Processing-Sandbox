#ifndef STENCIL_H
#define STENCIL_H

#include <memory>
#include <vector>
#include <iostream>
#include <random>

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

    // Helper functions
    // Functions to create and work with stencils outside of class

    // Find stencil based on halfwidth
    int stencilDim(int halfwidth);

    // Create a blur stencil
    Stencil blur(float val);

    // Create a random stencil
    Stencil random(int halfwidth);

    // -------------------------------------------------------------------

}

#endif