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
#include <Eigen/Geometry>

namespace xc
{
namespace math
{


typedef Eigen::AngleAxis<Real>                         AngleAxis;
typedef Eigen::Translation<Real, 3>                    Translation3;
typedef Eigen::Transform<Real, 3, Eigen::Affine>       Affine3;
typedef Eigen::Quaternion<Real>                        Quaternion;

inline AngleAxis _ret rotx ( Real _in v )
{
  return AngleAxis ( v, colvec3::UnitX() );
}

inline AngleAxis _ret roty ( Real _in v )
{
  return AngleAxis ( v, colvec3::UnitY() );
}

inline AngleAxis _ret rotz ( Real _in v )
{
  return AngleAxis ( v, colvec3::UnitZ() );
}

inline Translation3 _ret translation ( Real _in v1, Real _in v2, Real _in v3 )
{
  Translation3::VectorType v;
  v << v1, v2, v3;
  return Translation3 ( v );
}

inline Translation3 _ret translation ( colvec3 _in v )
{
  return Translation3 ( v );
}

//eulerYPR----------------------------------------------------------------------
inline AngleAxis _ret eulerRPY ( Real _in r, Real _in p, Real _in y )
{
  AngleAxis ret;
  ret = AngleAxis ( r, colvec3::UnitX() )
        * AngleAxis ( p, colvec3::UnitY() )
        * AngleAxis ( y, colvec3::UnitZ() );
  return ret;
}

inline AngleAxis _ret eulerRPY ( colvec3 _in v )
{
  return eulerRPY ( v ( 0 ), v ( 1 ), v ( 2 ) );
}

//eulerYPR----------------------------------------------------------------------
inline AngleAxis _ret eulerYPR ( Real _in y, Real _in p, Real _in r )
{
  AngleAxis ret;
  ret = AngleAxis ( y, colvec3::UnitZ() )
        * AngleAxis ( p, colvec3::UnitY() )
        * AngleAxis ( r, colvec3::UnitX() );
  return ret;
}

inline AngleAxis _ret eulerYPR ( colvec3 _in v )
{
  return eulerYPR ( v ( 0 ), v ( 1 ), v ( 2 ) );
}

//rpy---------------------------------------------------------------------------
inline Affine3 _ret rpy ( Real _in r, Real _in p, Real _in y, bool _in ypr = true )
{
  Affine3 ret;
  if ( ypr )
    return ret = eulerYPR ( y, p, r );
  else
    return ret = eulerRPY ( r, p, y );
}

inline Affine3 _ret rpy ( colvec3 _in v , bool _in ypr = true )
{
  return rpy ( v ( 0 ), v ( 1 ), v ( 2 ), ypr );
}

inline Affine3 _ret rpy ( colvec3 _in p, colvec3 _in v , bool _in ypr = true )
{
  Affine3 ret;
  return ret = translation ( p ) * rpy ( v, ypr );
}

//itranslation------------------------------------------------------------------
inline colvec3 _ret itranslation ( Affine3 _in v )
{
  return  v.translation();
}

// ieulerRPY--------------------------------------------------------------------
// returns roll pitch yaw
inline colvec3 _ret ieulerRPY ( Affine3 _in v, unsigned int _in solution_number = 1 )
{
  colvec3  e;
  const Affine3::LinearMatrixType & rot = v.rotation();

  if ( is_zero ( rot ( 2, 2 ) ) && is_zero ( rot ( 1, 2 ) ) )
  {
    e ( 0 ) = 0;
    e ( 1 ) = std::atan2 ( rot ( 0, 2 ), rot ( 2, 2 ) );
    e ( 2 ) = std::atan2 ( rot ( 1, 0 ), rot ( 1, 1 ) );
  }
  else
  {
    e ( 0 ) = std::atan2 ( -rot ( 1, 2 ), rot ( 2, 2 ) );
    Real sr = std::sin ( e ( 0 ) );
    Real cr = std::cos ( e ( 0 ) );
    e ( 1 ) = std::atan2 ( rot ( 0, 2 ), cr * rot ( 2, 2 ) - sr * rot ( 1, 2 ) );
    e ( 2 ) = std::atan2 ( -rot ( 0, 1 ), rot ( 0, 0 ) );
  }
  return e;
}

// ieulerYPR--------------------------------------------------------------------
// returns yaw pitch roll
inline colvec3 _ret ieulerYPR ( Affine3 _in v , unsigned int _in solution_number = 1 )
{
  colvec3  e1;
  colvec3  e2;
  const Affine3::LinearMatrixType & rot = v.rotation();
  if ( std::fabs ( rot ( 2, 0 ) ) >= 1 )
  {
    e1 ( 0 ) = 0.0;
    e2 ( 0 ) = 0.0;

    Real delta = std::atan2 ( rot ( 2, 1 ), rot ( 2, 2 ) );
    if ( rot ( 2, 0 ) < 0 )
    {
		e1(1) = 1.57079632679489661923;
		e2(1) = 1.57079632679489661923;
      e1 ( 2 ) = delta;
      e2 ( 2 ) = delta;
    }
    else
    {
		e1(1) = -1.57079632679489661923;
		e2(1) = -1.57079632679489661923;
      e1 ( 2 ) = delta;
      e2 ( 2 ) = delta;
    }
  }
  else
  {
    e1 ( 1 ) = - std::asin ( rot ( 2, 0 ) );
    e2 ( 1 ) = M_PI - e1 ( 1 );

    e1 ( 2 ) = std::atan2 ( rot ( 2, 1 ) / std::cos ( e1 ( 1 ) ),
                            rot ( 2, 2 ) / std::cos ( e1 ( 1 ) ) );
    e2 ( 2 ) = std::atan2 ( rot ( 2, 1 ) / std::cos ( e2 ( 1 ) ),
                            rot ( 2, 2 ) / std::cos ( e2 ( 1 ) ) );

    e1 ( 0 ) = std::atan2 ( rot ( 1, 0 ) / std::cos ( e1 ( 1 ) ),
                            rot ( 0, 0 ) / std::cos ( e1 ( 1 ) ) );
    e2 ( 0 ) = std::atan2 ( rot ( 1, 0 ) / std::cos ( e2 ( 1 ) ),
                            rot ( 0, 0 ) / std::cos ( e2 ( 1 ) ) );
  }

  if ( 1 == solution_number )
    return e1;
  else
    return e2;
}

// returns roll pitch yaw
inline colvec3 _ret irpy ( Affine3 _in v , unsigned int _in solution_number = 1, bool _in ypr = true )
{
  if ( ypr )
  {
    colvec3 e = ieulerYPR ( v, solution_number );
    return colvec3 ( e ( 2 ), e ( 1 ), e ( 0 ) );
  }
  else
  {
    colvec3 e = ieulerRPY ( v, solution_number );
    return e;
  }
}

}

}

/*

inline colvec3 _ret ieuler ( Affine3 _in v )
{
  colvec3 e;
  const Affine3::LinearMatrixType & rot = v.rotation();
  Scale sp = 0.0;
  Scale cp = 0.0;
  if ( is_zero ( rot ( 0, 2 ) ) && is_zero ( rot ( 1, 2 ) ) )
  {
    e ( 0 ) = 0.0;
    sp = 0.0;
    cp = 1.0;
  }
  else
  {
    e ( 0 ) = std::atan2 ( rot ( 1, 2 ), rot ( 0, 2 ) );
    sp = std::sin ( e ( 0 ) );
    cp = std::cos ( e ( 0 ) );
  }
  e ( 1 ) = std::atan2 ( cp * rot ( 0, 2 ) + sp * rot ( 1, 2 ), rot ( 2, 2 ) );
  e ( 2 ) = std::atan2 ( -sp * rot ( 0, 0 ) + cp * rot ( 1, 0 ), -sp * rot ( 0, 1 ) + cp * rot ( 1, 1 ) );
  return e;
}



inline colvec3 _ret iypr1 ( Affine3 _in v )
{
  colvec3  e;
  const Affine3::LinearMatrixType & rot = v.rotation();

  if ( is_zero ( rot ( 0, 0 ) ) && is_zero ( rot ( 2, 1 ) ) )
  {
    e ( 0 ) = 0;
    e ( 1 ) = std::atan2 ( -rot ( 2, 0 ), rot ( 0, 0 ) );
    e ( 2 ) = std::atan2 ( -rot ( 1, 2 ), rot ( 1, 1 ) );
  }
  else
  {
    e ( 0 ) = std::atan2 ( -rot ( 1, 0 ), rot ( 0, 0 ) );
    Scale sr = std::sin ( e ( 0 ) );
    Scale cr = std::cos ( e ( 0 ) );
    e ( 1 ) = std::atan2 ( -rot ( 2, 0 ), cr * rot ( 0, 0 ) + sr * rot ( 1, 0 ) );
    e ( 2 ) = std::atan2 ( sr * rot ( 0, 2 ) - cr * rot ( 1, 2 ), cr * rot ( 1, 1 ) - sr * rot ( 0, 1 ) );
  }
  return e;
}

inline Affine3 _ret eulerZYZ ( Scale _in v1, Scale _in v2, Scale _in v3 )
{
  Affine3 ret;
  ret = AngleAxis ( v1, colvec3::UnitZ() )
        * AngleAxis ( v2, colvec3::UnitY() )
        * AngleAxis ( v3, colvec3::UnitZ() );
  return ret;
}

inline Affine3 _ret eulerZYZ ( colvec3 _in e )
{
  return eulerXYZ ( e ( 0 ), e ( 1 ), e ( 2 ) );
}

inline Affine3 _ret eulerZYZ ( colvec3 _in p, colvec3 _in v )
{
  Affine3 t;
  t = Translation3 ( p )
      * AngleAxis ( v ( 0 ), colvec3::UnitZ() )
      * AngleAxis ( v ( 1 ), colvec3::UnitY() )
      * AngleAxis ( v ( 2 ), colvec3::UnitZ() );
  return t;
}

*/
