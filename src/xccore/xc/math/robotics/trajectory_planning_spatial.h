/*
* License:The MIT License (MIT)
*
* Copyright (c) 2013,2014 Yanyu Su
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARIstd::sinG FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/
#pragma once
#include <xc/math/math_fwd.h>
#include <xc/math/geometry.h>
#include <xc/math/interpolation.h>

namespace xc
{
namespace math
{
typedef std::vector<Affine3, Eigen::aligned_allocator<Affine3> > VectorAffine3;

VectorAffine3 _ret rpys ( matrix6X _in ts )
{
  VectorAffine3 ret;
  ret.resize ( ts.cols () );
  for ( DenseIndex i = 0; i < ts.cols (); ++i )
  {
    ret[i] = rpy ( ts.block<3, 1> ( 0, i ), ts.block<3, 1> ( 3, i ) );
  }
  return ret;
}

matrix6X _ret irpys ( VectorAffine3 _in ts )
{
  matrix6X ret;
  ret.resize ( 6, ts.size () );
  for ( VectorAffine3::size_type i = 0; i < ts.size (); ++i )
  {
    ret.block<3, 1> ( 0, i ) = ts[i].translation();
    ret.block<3, 1> ( 3, i ) = irpy ( ts[i] );
  }
  return ret;
}

/*
* Function
*  TODO:
*
* Output
*  ret   \in R^4
*
* Input
*  t1    \in R^{4 \times 4}
*  t2    \in R^{4 \times 4}
*  r     \in [0,1.0]
*/
inline Affine3 _ret interpolate_linear_transform ( Affine3 _in t1, Affine3 _in t2, Real _in r )
{
  Real x = r;
  if ( x > 1 ) x = 1.0;
  if ( x < 0 ) x = 0.0;

  const Quaternion q1 ( t1.rotation() );
  const Quaternion q2 ( t2.rotation() );
  Quaternion q = q1.slerp ( r, q2 );
  colvec3 p = r * t2.translation() + ( 1.0 - x ) * t1.translation();
  return Translation3 ( p ) * q;
}

/*
* Function
*  TODO:
*
* Output
*  ret   \in R^4
*
* Input
*  t1    \in R^{4 \times 4}
*  t2    \in R^{4 \times 4}
*  rs    \in R^x, rs is required to be strictly monotone increasing [0.0, 1.0]
*/
inline VectorAffine3 _ret interpolate_linear_transform ( Affine3 _in t1, Affine3 _in t2, colvecX _in rs )
{
  assert ( rs ( 0 ) >= 0.0 );
  assert ( rs ( rs.size() - 1 ) <= 1.0 );
  for ( DenseIndex i = 1; i < rs.size() ; ++i )
  {
    assert ( rs ( i ) > rs ( i - 1 ) );
  }

  VectorAffine3 ret ( rs.size() );
  for ( DenseIndex i = 0; i < rs.size(); ++i )
  {
    xreal r = rs ( i ) ;
    ret[i] =  interpolate_linear_transform ( t1, t2, r );
  }
  return ret;
}

/*
* Function
*  TODO:
*
* Output
*  ret   \in a series of R^{4 \times 4}, is the interpolated trajectory
*
* Input
*  ts    \in a series of R^{4 \times 4}, is the key points on the trajectory
*  rs    \in R^x, is the time index, required to be strictly monotone increasing [0.0, 1.0]
*/
inline VectorAffine3 _ret interpolate_spline_transforms ( VectorAffine3 _in ts, colvecX _in rs )
{
  assert ( rs ( 0 ) >= 0.0 );
  assert ( rs ( rs.size() - 1 ) <= 1.0 );
  for ( DenseIndex i = 1; i < rs.size() ; ++i )
  {
    assert ( rs ( i ) > rs ( i - 1 ) );
  }

  matrix6X rpy_in = irpys ( ts );
  //XC_DISPLAY ( rpy_in );
  matrix6X rpy_out = spline6(rpy_in, rs);
  //matrix6X rpy_out = spline<6> ( rpy_in, rs, 2 );
  //XC_DISPLAY ( rpy_out );
  return rpys ( rpy_out );
}

/*
* Function
*  TODO:
*
* Output
*  ret   \in a series of R^{4 \times 4}, is the interpolated trajectory
*
* Input
*  ts    \in a series of R^{4 \times 4}, is the key points on the trajectory
*  rs    \in R^x, is the time index, required to be strictly monotone increasing [0.0, 1.0]
*/
inline VectorAffine3 _ret interpolate_mcspline_transforms ( VectorAffine3 _in ts, colvecX _in rs )
{
  assert ( rs ( 0 ) >= 0.0 );
  assert ( rs ( rs.size() - 1 ) <= 1.0 );
  for ( DenseIndex i = 1; i < rs.size() ; ++i )
  {
    assert ( rs ( i ) > rs ( i - 1 ) );
  }

  matrix6X rpy_in = irpys ( ts );
  XC_DISPLAY ( rpy_in );
  matrix6X rpy_out = mcspline6 ( rpy_in, rs );
  XC_DISPLAY ( rpy_out );
  return rpys ( rpy_out );
}

}
}
