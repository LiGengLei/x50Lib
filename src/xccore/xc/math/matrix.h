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
#include <iostream>

namespace xc
{
namespace math
{

template<typename Derived>
inline Eigen::MatrixBase<Derived> _ret pinv ( Eigen::MatrixBase<Derived> _out inv, Eigen::MatrixBase<Derived> _in mat )
{
  double  pinvtoler = 1.e-6;

  Eigen::JacobiSVD<Derived> svd;
  svd.compute ( mat, Eigen::ComputeFullU | Eigen::ComputeFullV );

  const typename Eigen::JacobiSVD<typename Derived::PlainObject>::std::singularValuesType &
  sigma = svd.singularValues();
  typename Eigen::JacobiSVD<typename Derived::PlainObject>::std::singularValuesType
  sigma_inv = sigma;

  for ( typename Derived::Index i = 0; i < mat.cols(); ++i )
  {
    if ( sigma ( i ) > pinvtoler )
    {
      sigma_inv ( i ) = 1.0 / sigma ( i );
    }
    else
    {
      sigma_inv ( i ) = 0;
    }
  }

  inv = ( svd.matrixV() * sigma_inv.asDiagonal() * svd.matrixU().transpose() );
  return inv;
}

template<typename Derived>
inline std::istream &operator>> ( std::istream _out stm, Eigen::MatrixBase<Derived> _out mat )
{
  for ( typename Eigen::MatrixBase<Derived>::Index i = 0; i < mat.rows(); ++i )
  {
    for ( typename Eigen::MatrixBase<Derived>::Index j = 0; j < mat.cols(); ++j )
    {
      stm >> mat ( i, j );
    }
  }
  return stm;
}

}
}
