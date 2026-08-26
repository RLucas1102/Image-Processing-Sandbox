//*******************************************************************
//
//   LinearAlgebra.h
//
//
//   Performs linear algebra operation: vectors combined with matrices
//   Also other operations such as exponentiation, trace, determinant
//   and outer product.
//
//  Copyright (c) 2017 Jerry Tessendorf
//
//*******************************************************************

#ifndef STARTER_LINEARALGEBRA_H
#define STARTER_LINEARALGEBRA_H

#include "Vector.h"
#include "Matrix.h"



namespace starter{


// basic functions
const Vector cross_product( const Vector& v1, const Vector& v2 );
const Vector rotation( const Vector& v, const Vector& axis, const double angle );
const double dot_product( const Vector& v1, const Vector& v2 );


// Matrix times a Vector
const Vector operator* ( const Vector& v, const Matrix& m );
const Vector operator* ( const Matrix& m, const Vector& v );

// outer product
const Matrix operator& (const Vector& v1, const Vector& v2 );
// outer product in place
void outer_product( const Vector& v1, const Vector& v2, Matrix& m );

const Vector mat_prod_vec ( const Matrix& m, const Vector& v );
const Vector vec_prod_mat ( const Vector& v, const Matrix& m );

const Matrix exp( const Matrix& m );
const Matrix sinch( const Matrix& m );
const Matrix inverse( const Matrix& m ); 
const double det( const Matrix& m ); 
const double trace( const Matrix& m );

// construction a rotation matrix
const Matrix rotation( const Vector& axis, const double angle );

const Matrix unitMatrix();

const Matrix orderedSinch( const Matrix& a, const Matrix& b );

const Matrix Pauli0();
const Matrix Pauli1();
const Matrix Pauli2();

}
#endif

