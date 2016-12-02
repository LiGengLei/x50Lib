// This file is part of Eigen, a lightweight C++ template library
// for linear algebra.
//
// Copyright (c) 2013,2014 Yanyu Su (suyanyucn@gmail.com)
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef EIGEN_MONOTONE_CUBIC_INTERPOLATION_FWD_H
#define EIGEN_MONOTONE_CUBIC_INTERPOLATION_FWD_H

#include <Eigen/Core>

namespace Eigen
{
template <typename Scalar, int Dim> class MCI;

template <typename MCIType> struct MCITraits {};

/**
 * \ingroup Monotone_Cubic_Interpolation_Module
 * \brief Compile-time attributes of the monotone cubic interpolation.
 **/
template <typename _Scalar, int _Dim>
struct MCITraits< MCI<_Scalar, _Dim> >
{
  typedef _Scalar Scalar;  /*!< The curve's scalar type. */

  enum { Dimension = _Dim  /*!< The curve's dimension. */ };

  /** \brief The note type the spline is representing, i.e. x. */
  typedef Scalar                            XType;

  /** \brief The point type the spline is representing, i.e. y=f(x). */
  typedef Array<Scalar, Dimension, 1>       YType;

  /** \brief The data type used to store knot vectors, i.e. X={x_1,x_2,...}. */
  typedef Array<Scalar, 1, Dynamic >        XVectorType;

  /** \brief The data type representing the spline's control points, i.e. Y={y_1,y_2,...}. */
  typedef Array<Scalar, Dimension, Dynamic> YVectorType;

  /** \brief The data type representing the spline's control points, i.e. M={m_1,m_2,...}. */
  typedef Array<Scalar, Dimension, Dynamic> CoefficientVectorType;

  };

}

#endif // EIGEN_MONOTONE_CUBIC_INTERPOLATION_FWD_H
