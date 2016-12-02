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
#include <xc/core/core.h>
#include <cmath>
#include <limits>
#include <Eigen/Eigen>
#include <Eigen/StdVector>

#define XC_DISPLAY(X) std::cout << #X << " =  [" << std::endl << X << std::endl << "];"  << std::endl;

namespace xc
{
namespace math
{
typedef double Real;
using   Eigen::Matrix;
using   Eigen::DenseIndex;

typedef Matrix< Real, 6, 6 >                           matrix66;
typedef Matrix< Real, 3, Eigen::Dynamic >              matrix3X;
typedef Matrix< Real, 4, Eigen::Dynamic >              matrix4X;
typedef Matrix< Real, 6, Eigen::Dynamic >              matrix6X;
typedef Matrix< Real, 7, Eigen::Dynamic >              matrix7X;
typedef Matrix< Real, Eigen::Dynamic, Eigen::Dynamic > matrixXX;
typedef Matrix< Real, 3, 1 >                           colvec3;
typedef Matrix< Real, 4, 1 >                           colvec4;
typedef Matrix< Real, 6, 1 >                           colvec6;
typedef Matrix< Real, 7, 1 >                           colvec7;
typedef Matrix< Real, Eigen::Dynamic, 1 >              colvecX;
typedef Matrix< Real, 1, 3 >                           rowvec3;
typedef Matrix< Real, 1, 4 >                           rowvec4;
typedef Matrix< Real, 1, 6 >                           rowvec6;
typedef Matrix< Real, 1, Eigen::Dynamic >              rowvecX;

// old types
typedef Real xreal;


class math_data
{
public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};

inline Real _ret eps ()
{
  return std::numeric_limits<Real>::epsilon();
}

inline bool _ret is_zero ( Real _in x )
{
  return std::fabs ( x ) < std::numeric_limits<Real>::epsilon();
}

}
}
