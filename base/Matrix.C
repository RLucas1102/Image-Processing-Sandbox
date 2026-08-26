//*******************************************************************
//
//   Matrix.h
//
// 3D matrix class 
//
//*******************************************************************


#include <iostream>
#include <cmath>

#include "Matrix.h"

using namespace starter;

const Matrix Matrix::operator+        (const Matrix& v) const
{
  double newmat[3][3];
  for(int i=0;i<3;i++)
  {
    for(int j=0;j<3;j++)
    {
       newmat[i][j] = m[i][j] + v.m[i][j];
    }
  }
  return Matrix(newmat);
}

const Matrix Matrix::operator-        (const Matrix& v) const
{
  double newmat[3][3];
  for(int i=0;i<3;i++)
  {
    for(int j=0;j<3;j++)
    {
       newmat[i][j] = m[i][j] - v.m[i][j];
    }
  }
  return Matrix(newmat);
}

const Matrix starter::operator-        (const Matrix& m)
{
  return m*(-1);;
}

const Matrix Matrix::operator*        (const double v) const
{
  double newmat[3][3];   
  for(int i=0;i<3;i++)
  {
    for(int j=0;j<3;j++)
    {
       newmat[i][j] = m[i][j] * v;
    }
  } 
  return Matrix(newmat);
}

const Matrix starter::operator* (const double w, const Matrix& v)
{ return v * w; }

const Matrix Matrix::operator/        (const double v) const
{
  double newmat[3][3];   
  for(int i=0;i<3;i++)
  {
    for(int j=0;j<3;j++)
    {
       newmat[i][j] = m[i][j] / v;
    }
  } 
  return Matrix(newmat);
}

const Matrix Matrix::operator*        (const Matrix& v) const
{
  double newmat[3][3];   
  for(int i=0;i<3;i++)
  {
    for(int j=0;j<3;j++)
    {
       newmat[i][j] = 0;
       for(int k=0;k<3;k++)
       {
          newmat[i][j] += m[i][k] * v.m[k][j];
       }
    }
  } 
  return Matrix(newmat);
}

Matrix& Matrix::operator=      (const Matrix& v)
{
  for(int i=0;i<3;i++)
  {
    for(int j=0;j<3;j++)
    {
       m[i][j] = v.m[i][j];
    }
  }
  return *this;
}

Matrix& Matrix::operator+=      (const Matrix& v)
{
  for(int i=0;i<3;i++)
  {
    for(int j=0;j<3;j++)
    {
       m[i][j] += v.m[i][j];
    }
  } 
  return *this;
}

Matrix& Matrix::operator-=      (const Matrix& v)
{
  for(int i=0;i<3;i++)
  {
    for(int j=0;j<3;j++)
    {
       m[i][j] -= v.m[i][j];
    }
  } 
  return *this;
}

Matrix& Matrix::operator*=      (const double v)
{
  for(int i=0;i<3;i++)
  {
    for(int j=0;j<3;j++)
    {
       m[i][j] *= v;
    }
  } 
  return *this;
}

Matrix& Matrix::operator/=      (const double v)
{
  for(int i=0;i<3;i++)
  {
    for(int j=0;j<3;j++)
    {
       m[i][j] /= v;
    }
  } 
  return *this;
}

Matrix& Matrix::operator*=      (const Matrix& v)
{
  double newmat[3][3];
  for(int i=0;i<3;i++)
  {
    for(int j=0;j<3;j++)
    {
       newmat[i][j] = 0;
       for(int k=0;k<3;k++)
       {
          newmat[i][j] += m[i][k] * v.m[k][j];
       }
    }
  }
  for(int i=0;i<3;i++)
  {
    for(int j=0;j<3;j++)
    {
       m[i][j] = newmat[i][j];
    }
  }
  return *this;
}

const Matrix Matrix::operator&&      (const Matrix& m) const
{
  return ( (*this) * m + m * (*this) );
}

const Matrix Matrix::operator||      (const Matrix& m) const
{
  return ( (*this) * m - m * (*this) );
}

const Matrix Matrix::transpose() const
{
  double newmat[3][3];
  for(int i=0;i<3;i++)
  {
    for(int j=0;j<3;j++)
    {
       newmat[i][j] = m[j][i];
    }
  }
  return Matrix(newmat);
}

const double Matrix::det() const
{
   const double result = ( m[0][0] * ( m[1][1] * m[2][2] - m[1][2] * m[2][1] )
                         + m[0][1] * ( m[1][2] * m[2][0] - m[1][0] * m[2][2] )
                         + m[0][2] * ( m[1][0] * m[2][1] - m[1][1] * m[2][0] )  );
   return result;
}

const double Matrix::trace() const
{
  return ( m[0][0] + m[1][1] + m[2][2] );
}

const Matrix Matrix::exp() const
{
  double scaler = std::pow((double)2.0, (double)range);

  Matrix expm( 1,0,0,  0,1,0,  0,0,1 );
  Matrix mc(*this);
  Matrix mcs;
  mcs = mc/scaler;
  mc = mcs;

  const int terms = 30;
  for(int t=1; t<=terms; t++)
  {
    expm = expm + mc ;
    mc = mc * mcs / double(t+1);
  }
  for( int i=0;i<range;i++ )
  {
     expm = expm*expm;
  }
  return expm;
}

const Matrix Matrix::sinch() const
{
  Matrix expm( 1,0,0,  0,1,0,  0,0,1 );
  Matrix mc= -(*this);
  if( std::fabs(det()) > 1.0e-4 )
  {
     expm = -(mc.inverse()) * (expm -  mc.exp() );
     return expm;
  }
  Matrix accum = mc / 2.0;
  const int terms = 600;
  for(int t=2; t<=terms; t++)
  {
    expm = expm + accum;
    accum = accum * mc/double(t+1);
  }
  return expm;
}



const bool Matrix::operator==  (const Matrix& v) const
{
  for(int i=0;i<3;i++)
  {
    for(int j=0;j<3;j++)
    {
       if(m[j][i] != v.m[i][j]){ return false; }
    }
  }
  return true; 
}

const bool Matrix::operator!=  (const Matrix& v) const
{
  for(int i=0;i<3;i++)
  {
    for(int j=0;j<3;j++)
    {
       if(m[j][i] != v.m[i][j]){ return true; }
    }
  }
  return false;
}

// These tests are comparisons of the determinant
const bool Matrix::operator>          (const Matrix& v) const
{  return ( det() > v.det() ); }

const bool Matrix::operator>=         (const Matrix& v) const
{  return ( det() >= v.det() ); }

const bool Matrix::operator<          (const Matrix& v) const
{  return ( det() < v.det() ); }

const bool Matrix::operator<=         (const Matrix& v) const
{  return ( det() <= v.det() ); }

const Matrix Matrix::inverse() const
{
   double determinant = det();
   double newmat[3][3];
   for(int i=0;i<3;i++)
   {
      for(int j=0;j<3;j++)
      {
         newmat[i][j] = cofactor(i,j) / determinant;
      }
   }
   return Matrix( newmat );
}

const double Matrix::cofactor(int i, int j) const
{
  double small[2][2];
  int ip = 0, jp = 0;
  for(int ir=0;ir<3;ir++)
  {
    if(ir != i)
    {
       jp = 0;
       for(int jr=0;jr<3;jr++)
       {
          if(jr != j)
          {
             small[ip][jp] = m[ir][jr];
             jp++;
          }
       }
       ip++;
    }
  }
  return pow( -1.0, (i+j) ) * ( small[0][0] * small[1][1] - small[0][1] * small[1][0] ) ; 
}





