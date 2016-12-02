// This file is part of Eigen, a lightweight C++ template library
// for linear algebra.
//
// Copyright (c) 2013,2014 Yanyu Su (suyanyucn@gmail.com)
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef EIGEN_MONOTONE_CUBIC_HERMITE_INTERPOLATION_H
#define EIGEN_MONOTONE_CUBIC_HERMITE_INTERPOLATION_H

#include "MonotoneCubicInterpolationFwd.h"

namespace Eigen
{

  /**
   * \ingroup Monotone_Cubic_Interpolation_Module
   * \brief Monotone Cubic Hermite Interpolation Method
   **/
  template <typename MCIType>
  struct MCHI
  {
    typedef typename MCIType::Scalar                Scalar;
    typedef typename MCIType::XType                 XType;
    typedef typename MCIType::YType                 YType;
    typedef typename MCIType::XVectorType           XVectorType;
    typedef typename MCIType::YVectorType           YVectorType;
    typedef typename MCIType::CoefficientVectorType CoefficientVectorType;

    /**
     * \brief Fits an cubic to the given data points.
     *
     * \param ys The y points for which an monotone cubic Hermite interpolation will be computed.
     *
     * \returns A cubic monotone hermite interpolation of the initially provided points.
     **/
    template <typename PointArrayType>
    static MCIType Interpolate(const PointArrayType& ys);

    /**
    * \brief Fits an cubic to the given data points.
    *
    * \param ys The y points for which an monotone cubic Hermite interpolation will be computed.
    * \param xs The x points for which an monotone cubic Hermite interpolation will be computed.
    *
    * \returns A cubic monotone Hermite interpolation of the initially provided points.
    **/
    template <typename PointArrayType>
    static MCIType Interpolate(const PointArrayType& ys, const XVectorType& xs);
  };


  template <typename MCIType>
  template <typename PointArrayType>
  MCIType MCHI<MCIType>::Interpolate(const PointArrayType& ys, const XVectorType& xs)
  {
    // check inputs
    assert(ys.cols() == xs.size());

    // init constants
    const DenseIndex length = ys.cols();
    const DenseIndex dim = ys.rows();

    // init variables
    CoefficientVectorType c1s, c2s, c3s;
    XVectorType dxs;
    YVectorType dys;
    YVectorType ms;
    c1s.resize(dim, length);
    c2s.resize(dim, length - 1);
    c3s.resize(dim, length - 1);
    dxs.resize(1, length - 1);
    dys.resize(dim, length - 1);
    ms.resize(dim, length - 1);

    // get consecutive differences and slopes
    for (DenseIndex k = 0; k < length - 1; ++k)
    {
      dxs(k) = xs(k + 1) - xs(k);
      dys.col(k) = ys.col(k + 1) - ys.col(k);
      for (DenseIndex i = 0; i < dim; ++i)
        ms(i, k) = dys(i, k) / dxs(k);
    }

    // get degree-1 coefficients
    c1s.col(0) = ms.col(0);
    for (DenseIndex k = 0; k < length - 1 - 1; ++k)
    {
      Scalar dx = dxs(k);
      Scalar dxNext = dxs(k + 1);
      Scalar common = dx + dxNext;
      for (DenseIndex i = 0; i < dim; ++i)
      {
        Scalar m = ms(i, k);
        Scalar mNext = ms(i, k + 1);
        if (m*mNext <= 0)
          c1s(i, k + 1) = 0;
        else
          c1s(i, k + 1) = 3.0 * common / ((common + dxNext) / m + (common + dx) / mNext);
      }
    }
    c1s.col(length - 1) = ms.col(length - 1 - 1);

    // get degree-2 and degree-3 coefficients
    for (DenseIndex k = 0; k < length - 1; ++k)
    {
      for (DenseIndex i = 0; i < dim; ++i)
      {
        Scalar c1 = c1s(i, k);
        Scalar c1Next = c1s(i, k + 1);
        Scalar m = ms(i, k);
        Scalar invDx = 1.0 / dxs(k);
        Scalar common = c1 + c1Next - m - m;
        c2s(i, k) = (m - c1 - common)*invDx;
        c3s(i, k) = common*invDx*invDx;
      }
    }

    return MCIType(xs, ys, c1s, c2s, c3s);
  }

  template <typename MCIType>
  template <typename PointArrayType>
  MCIType MCHI<MCIType>::Interpolate(const PointArrayType& pts)
  {
    typedef typename XVectorType::Scalar Scalar;
    XVectorType chord_lengths(pts.cols());
    for (DenseIndex i = 0; i < chord_lengths.size(); ++i)
      chord_lengths(i) = static_cast<Scalar> (i) / (chord_lengths.size() - 1);
    return Interpolate(pts, chord_lengths);
  }
}

#endif // EIGEN_MONOTONE_CUBIC_HERMITE_INTERPOLATION_H
