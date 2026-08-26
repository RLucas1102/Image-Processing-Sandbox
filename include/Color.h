//*******************************************************************
//
//   Color.h
//
// 4D color class in the namespace starter
//
//  Copyright (c) 2017 Jerry Tessendorf
//
//
//*******************************************************************

#ifndef STARTER_COLOR_H
#define STARTER_COLOR_H


namespace starter
{

//! a class to hold 4-component float color values.
class Color
{
  public:

   Color(){ xyzw[0] = xyzw[1] = xyzw[2] = xyzw[3] = 0; }

   Color(const Color& v)
   { 
      xyzw[0] = v.xyzw[0];
      xyzw[1] = v.xyzw[1];
      xyzw[2] = v.xyzw[2]; 
      xyzw[3] = v.xyzw[3]; 
   }
   
   Color(const float a, const float b, const float c, const float d)
   {
      xyzw[0] = a;
      xyzw[1] = b;
      xyzw[2] = c; 
      xyzw[3] = d; 
   }

   ~Color(){}

   //!  Set all four components
   void set( const float vx, const float vy, const float vz, const float vw )
   {
      xyzw[0] = vx;
      xyzw[1] = vy;
      xyzw[2] = vz;
      xyzw[3] = vw;
   }

   //! Add two colors together
   const Color operator+        (const Color& v) const 
   { 
      return Color(xyzw[0]+v.xyzw[0], xyzw[1]+v.xyzw[1], xyzw[2]+v.xyzw[2], xyzw[3]+v.xyzw[3]); 
   }
  
   //! Subtract one color from another
   const Color operator-        (const Color& v) const
   { 
      return Color(xyzw[0]-v.xyzw[0], xyzw[1]-v.xyzw[1], xyzw[2]-v.xyzw[2], xyzw[3]-v.xyzw[3]); 
   }

   //! Unary minus
   friend const Color operator- (const Color& v)
   { return Color(-v.xyzw[0],-v.xyzw[1],-v.xyzw[2], -v.xyzw[3]); }

   //! Multiplication of a constant with a Color 
   friend const Color operator* (const float w, const Color& v)
   { return v*w; }
	  
   //! Multiplication of a Color with a constant
   const Color operator*        (const float v) const
   { return Color(xyzw[0]*v, xyzw[1]*v, xyzw[2]*v, xyzw[3]*v); }

   const Color operator/        (const float v) const
   { return Color(xyzw[0]/v, xyzw[1]/v, xyzw[2]/v, xyzw[3]/v); }

   //! component-by-component product
   const Color operator*        (const Color& v) const  
   { return Color(xyzw[0]*v.xyzw[0] , xyzw[1]*v.xyzw[1] , xyzw[2]*v.xyzw[2] , xyzw[3]*v.xyzw[3]); }
  
   Color& operator=       (const Color& v)
   { xyzw[0] = v.xyzw[0]; xyzw[1] = v.xyzw[1]; xyzw[2] = v.xyzw[2]; xyzw[3]=v.xyzw[3]; return *this; }
  
   Color& operator+=      (const Color& v)
   { xyzw[0] += v.xyzw[0]; xyzw[1] += v.xyzw[1]; xyzw[2] += v.xyzw[2]; xyzw[3] += v.xyzw[3]; return *this; }
  
   Color& operator-=      (const Color& v)
   { xyzw[0] -= v.xyzw[0]; xyzw[1] -= v.xyzw[1]; xyzw[2] -= v.xyzw[2]; xyzw[3] -= v.xyzw[3]; return *this; }
  
   Color& operator*=      (const float v)
   { xyzw[0] *= v; xyzw[1] *= v; xyzw[2] *= v; xyzw[3] *= v; return *this; }
  
   Color& operator*=      (const Color& v)
   { xyzw[0] *= v.xyzw[0]; xyzw[1] *= v.xyzw[1]; xyzw[2] *= v.xyzw[2]; xyzw[3] *= v.xyzw[3]; return *this; }
  
   Color& operator/=      (const float v)
   { xyzw[0] /= v; xyzw[1] /= v; xyzw[2] /= v; xyzw[3] /= v; return *this; }
  
   Color& operator/=      (const Color& v)
   { xyzw[0] /= v.xyzw[0]; xyzw[1] /= v.xyzw[1]; xyzw[2] /= v.xyzw[2]; xyzw[3] /= v.xyzw[3]; return *this; }
 
   const float& operator[] (const int v) const { return xyzw[v]; }
         float& operator[] (const int v)       { return xyzw[v]; }
   const float& operator() (const int v) const { return xyzw[v]; }

   const float X() const { return xyzw[0]; }
   const float Y() const { return xyzw[1]; }
   const float Z() const { return xyzw[2]; }
   const float W() const { return xyzw[3]; }

   const float red() const { return xyzw[0]; }
   const float green() const { return xyzw[1]; }
   const float blue() const { return xyzw[2]; }
   const float alpha() const { return xyzw[3]; }

   const float* expose() const { return xyzw; }

//  Comparisons

   //! test for equality component-by-component
   const bool operator==         (const Color& v) const
       { return ( xyzw[0]==v.xyzw[0] && xyzw[1]==v.xyzw[1] && xyzw[2]==v.xyzw[2] && xyzw[3] == v.xyzw[3] ); }

   //! test for not equality component-by-component
   const bool operator!=         (const Color& v) const
       { return ( xyzw[0]!=v.xyzw[0] || xyzw[1]!=v.xyzw[1] || xyzw[2]!=v.xyzw[2] || xyzw[3] != v.xyzw[3] ); }

   //! This is useful for python bindings. 
   char *__str__() {
       static char tmp[1024];
       std::sprintf(tmp,"Color(%g,%g,%g,%g)", xyzw[0],xyzw[1],xyzw[2],xyzw[3]);
       return tmp;
   }


  private:
  float xyzw[4];
};

}



#endif
