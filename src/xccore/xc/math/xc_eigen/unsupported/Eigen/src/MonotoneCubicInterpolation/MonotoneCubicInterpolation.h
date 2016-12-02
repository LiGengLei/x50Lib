// This file is part of Eigen, a lightweight C++ template library
// for linear algebra.
//
// Copyright (c) 2013,2014 Yanyu Su (suyanyucn@gmail.com)
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef EIGEN_MONOTONE_CUBIC_INTERPOLATION_H
#define EIGEN_MONOTONE_CUBIC_INTERPOLATION_H

#include "MonotoneCubicInterpolationFwd.h"

namespace Eigen
{
  /**
   * \ingroup Monotone_Cubic_Interpolation_Module
   * \class MC
   * \brief A class representing multi-dimensional cubic curves.
   *
   * \tparam _Scalar The underlying data type (typically float or double)
   * \tparam _Dim The curve dimension (e.g. 2 or 3)
   **/
  template <typename _Scalar, int _Dim>
  class MCI
  {
  public:
    typedef _Scalar Scalar; /*!< The cubic curve's scalar type. */
    enum { Dimension = _Dim /*!< The cubic curve's dimension. */ };

    /** \brief The point type the cubic is representing. */
    typedef typename MCITraits<MCI>::XType XType;

    /** \brief The point type the cubic is representing. */
    typedef typename MCITraits<MCI>::YType YType;

    /** \brief The data type used to store x vectors, i.e. x. */
    typedef typename MCITraits<MCI>::XVectorType XVectorType;

    /** \brief The data type representing the y points, i.e. y. */
    typedef typename MCITraits<MCI>::YVectorType YVectorType;

    /** \brief The data type representing the coefficients, i.e. m. */
    typedef typename MCITraits<MCI>::CoefficientVectorType CoefficientVectorType;

    /**
    * \brief Creates a (constant) zero cubic.
    **/
    MCI()
      : m_xs(XVectorType::Zero(1, 1))
      , m_ys(YVectorType::Zero(Dimension, 1))
      , m_c1s(CoefficientVectorType::Zero(Dimension, 1))
      , m_c2s(CoefficientVectorType::Zero(Dimension, 1))
      , m_c3s(CoefficientVectorType::Zero(Dimension, 1)){}

    /**
    * \brief Creates a cubic from a x vector, y points and coefficients
    * \param xs The cubic x vector.
    * \param ys The cubic y vector.
    * \param c1s The cubic coefficient vector.
    * \param c2s The cubic coefficient vector.
    * \param c3s The cubic coefficients vector.
    **/
    template <typename OtherVectorType, typename OtherArrayType1, typename OtherArrayType2>
    MCI(const OtherVectorType& xs, const OtherArrayType1& ys, const OtherArrayType2& c1s,
      const OtherArrayType2& c2s, const OtherArrayType2& c3s)
      : m_xs(xs), m_ys(ys), m_c1s(c1s), m_c2s(c2s), m_c3s(c3s) {}

    /**
    * \brief Copy constructor for cubic.
    * \param cubic The input cubic.
    **/
    MCI(const MCI<Scalar, Dimension>& cubic)
      : m_xs(cubic.m_xs), m_ys(cubic.m_ys), m_c1s(cubic.m_c1s),
      m_c2s(cubic.m_c2s), m_c3s(cubic.m_c3s) {}

    /**
     * \brief Returns the spline value at a given site u.
     * \param u Parameter u at which the cubic is evaluated.
     * \return The cubic value at the given location u.
     **/
    YType const operator() (const Scalar u) const;

    /**
     * \brief Returns the span within the x vector in which u is falling.
     * \param u The site for which the span is determined.
     **/
    DenseIndex const span(const Scalar  u) const;

    /**
     * \brief Computes the span within the provided x vector in which u is falling.
     **/
    static DenseIndex Span(const typename MCITraits<MCI>::Scalar u,
      const typename MCITraits<MCI>::XVectorType& xs);

    /**
     * \brief Computes a cubic value given x, y and coefficients.
     **/
    static typename MCI::Scalar InterpolateFunc(const typename MCITraits<MCI>::Scalar x,
      const typename MCITraits<MCI>::Scalar xl,
      const typename MCITraits<MCI>::Scalar yl,
      const typename MCITraits<MCI>::Scalar c1s,
      const typename MCITraits<MCI>::Scalar c2s,
      const typename MCITraits<MCI>::Scalar c3s);

  private:
    XVectorType                 m_xs; /*!< x vector. */
    YVectorType                 m_ys; /*!< y points. */
    CoefficientVectorType       m_c1s; /*!< coefficients. */
    CoefficientVectorType       m_c2s; /*!< coefficients. */
    CoefficientVectorType       m_c3s; /*!< coefficients. */
  };

  template <typename _Scalar, int _Dim>
  DenseIndex MCI<_Scalar, _Dim>::Span(
    const typename MCITraits<MCI<_Scalar, _Dim> >::Scalar u,
    const typename MCITraits< MCI<_Scalar, _Dim> >::XVectorType& xs)
  {
    if (u <= xs(0)) return 0;
    if (u >= xs(xs.size() - 1)) return xs.size() - 1;
    const Scalar* pos = std::upper_bound(xs.data(), xs.data() + xs.size(), u);
    return static_cast<DenseIndex> (std::distance(xs.data(), pos) - 1);
  }

  template <typename _Scalar, int _Dim>
  typename MCI<_Scalar, _Dim>::Scalar MCI<_Scalar, _Dim>::InterpolateFunc(
    const typename MCITraits<MCI<_Scalar, _Dim> >::Scalar x,
    const typename MCITraits<MCI<_Scalar, _Dim> >::Scalar xl,
    const typename MCITraits<MCI<_Scalar, _Dim> >::Scalar yl,
    const typename MCITraits<MCI<_Scalar, _Dim> >::Scalar c1s,
    const typename MCITraits<MCI<_Scalar, _Dim> >::Scalar c2s,
    const typename MCITraits<MCI<_Scalar, _Dim> >::Scalar c3s)
  {
    const typename MCITraits<MCI<_Scalar, _Dim> >::Scalar diff = x - xl;
    const typename MCITraits<MCI<_Scalar, _Dim> >::Scalar diffSq = diff*diff;
    return yl + c1s*diff + c2s*diffSq + c3s*diff*diffSq;
  }

  template <typename _Scalar, int _Dim>
  DenseIndex const MCI<_Scalar, _Dim>::span(const typename MCI<_Scalar, _Dim>::Scalar u) const
  {
    DenseIndex size = MCI::Span(u, m_xs);
    return size;
  }

  template <typename _Scalar, int _Dim>
  typename MCI<_Scalar, _Dim>::YType const MCI<_Scalar, _Dim>::operator() (const typename MCI<_Scalar, _Dim>::Scalar u) const
  {
    const DenseIndex klower = span(u);

    if (klower >= m_ys.cols() - 1)
      return MCI::m_ys.col(m_ys.cols() - 1);

    const MCI::Scalar                      xl = m_xs(klower);
    const MCI::YType                      _yl = m_ys.col(klower);
    const MCI::CoefficientVectorType      _c1 = m_c1s.col(klower);
    const MCI::CoefficientVectorType      _c2 = m_c2s.col(klower);
    const MCI::CoefficientVectorType      _c3 = m_c3s.col(klower);
    MCI::YType ret;
    for (size_t i = 0; i < _Dim; ++i)
    {
      MCI::Scalar  yl = _yl(i);
      MCI::Scalar  c1 = _c1(i);
      MCI::Scalar  c2 = _c2(i);
      MCI::Scalar  c3 = _c3(i);
      ret(i) = MCI::InterpolateFunc(u, xl, yl, c1, c2, c3);
    }

    return ret;
  }

}

#endif // EIGEN_MONOTONE_CUBIC_INTERPOLATION_H
