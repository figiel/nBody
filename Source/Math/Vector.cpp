//--------------------------------------------------------------------------
//
// nBody -v1.0
//
// Copyright (c) 2012, Mariusz Moczala and Tomasz Stachowiak
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// - Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
// - Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the distribution.
// - Neither the name of the copyright holders nor the names of its
//   contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT
// HOLDERS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
// OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//--------------------------------------------------------------------------


//--------------------------------------------------------------------------
#include <math.h>
#include "Vector.h"
//--------------------------------------------------------------------------
CVector::CVector()
{
  // Assign default vector
  x = 0;
  y = 0;
  z = 0;
}
//--------------------------------------------------------------------------
CVector::CVector(const CVector &Vector)
{
  // Assign specified vector
  x = Vector.x;
  y = Vector.y;
  z = Vector.z;
}
//--------------------------------------------------------------------------
CVector::CVector(double _x, double _y, double _z)
{             
  // Assign specified vector
  x = _x;
  y = _y;
  z = _z;
}
//--------------------------------------------------------------------------
CVector & CVector::operator = (const CVector &Vector)
{              
  // Assign specified vector
  x = Vector.x;
  y = Vector.y;
  z = Vector.z;

  // Return reference to this object
  return *this;
}
//--------------------------------------------------------------------------
CVector & CVector::operator += (const CVector &Vector)
{                      
  // Vector addition
  x += Vector.x;
  y += Vector.y;
  z += Vector.z;
                
  // Return reference to this object
  return *this;
}
//--------------------------------------------------------------------------
CVector & CVector::operator -= (const CVector &Vector)
{               
  // Vector subtraction
  x -= Vector.x;
  y -= Vector.y;
  z -= Vector.z;
                     
  // Return reference to this object
  return *this;
}
//--------------------------------------------------------------------------
CVector & CVector::operator ^= (const CVector &Vector)
{
  // Cross product
  *this = CVector(
    y * Vector.z - z * Vector.y,
    z * Vector.x - x * Vector.z,
    x * Vector.y - y * Vector.x);
                    
  // Return reference to this object
  return *this;
}
//--------------------------------------------------------------------------
CVector & CVector::operator *= (const double Scalar)
{
  // Scalar multiplication
  x *= Scalar;
  y *= Scalar;
  z *= Scalar;

  // Return reference to this object
  return *this;
}
//--------------------------------------------------------------------------
CVector CVector::operator + (const CVector &Vector) const
{
  // Vector addition
  return CVector(x + Vector.x, y + Vector.y, z + Vector.z);
}
//--------------------------------------------------------------------------
CVector CVector::operator - (const CVector &Vector) const
{
  // Vector subtraction
  return CVector(x - Vector.x, y - Vector.y, z - Vector.z);
}
//--------------------------------------------------------------------------
CVector CVector::operator ^ (const CVector &Vector) const
{
  // Cross product
  return CVector(
    y * Vector.z - z * Vector.y,
    z * Vector.x - x * Vector.z,
    x * Vector.y - y * Vector.x);
}
//--------------------------------------------------------------------------
double CVector::operator & (const CVector &Vector) const
{
  // Dot product
  return x * Vector.x + y * Vector.y + z * Vector.z;
}
//--------------------------------------------------------------------------
CVector CVector::operator * (const double Scalar) const
{
  // Scalar multiplication
  return CVector(x * Scalar, y * Scalar, z * Scalar);
}
//--------------------------------------------------------------------------
double CVector::Length() const
{
  // Vector length
  return sqrt(x * x + y * y + z * z);
}
//--------------------------------------------------------------------------
CVector & CVector::Normalize()
{
  // Calculate vector length
  double Len = Length();

  // When length is not zero, divide all components by length to
  // normalize vector
  if(Len != 0)
  {
    x /= Len;
    y /= Len;
    z /= Len;
  }
                
  // Return reference to this object
  return *this;
}
//--------------------------------------------------------------------------
void CVector::CartesianToSphericalCoord(double &Radius,
  double &Inclination, double &Azimuth) const
{
  // Radious is equal to vector length
  Radius = Length();

  // Angles can be calculated only, when vector have non zero length
  if(Radius != 0)
  {
    // Calculate inclination
    Inclination = asin(z / Radius);

    // Calculate azimuth
    if(x != 0)
      Azimuth = atan(y / x);
    else
      Azimuth = M_PI / 2;
  }

  // Assign default values for zero length vector
  else
  {
    Inclination = 0;
    Azimuth = 0;
  }
}
//--------------------------------------------------------------------------
CVector & CVector::SphericalToCartesianCoord(
  double Radius, double Inclination, double Azimuth)
{
  // Calculate components from sperical coordinates
  x = Radius * sin(Inclination) * cos(Azimuth);
  y = Radius * sin(Inclination) * sin(Azimuth);
  z = Radius * cos(Inclination);

  // Return reference to this object
  return *this;
}
//--------------------------------------------------------------------------
