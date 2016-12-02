/*
* License:The MIT License (MIT)
*
* Copyright (c) 2013 Yanyu Su
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
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/
#include <xc/core/core.h>
#include <string>
#include <iostream>
#include <xc/math/math.h>

typedef double Scalar;
Eigen::Matrix3d setEulerYPR ( Scalar eulerZ, Scalar eulerY, Scalar eulerX )
{
  Scalar ci ( cos ( eulerX ) );
  Scalar cj ( cos ( eulerY ) );
  Scalar ch ( cos ( eulerZ ) );
  Scalar si ( sin ( eulerX ) );
  Scalar sj ( sin ( eulerY ) );
  Scalar sh ( sin ( eulerZ ) );
  Scalar cc = ci * ch;
  Scalar cs = ci * sh;
  Scalar sc = si * ch;
  Scalar ss = si * sh;

  Eigen::Matrix3d ret;
  ret << cj * ch, sj * sc - cs, sj * cc + ss,
      cj * sh, sj * ss + cc, sj * cs - sc,
      -sj,      cj * si,      cj * ci ;
  return ret;
}

Eigen::Matrix3d setRPY ( Scalar roll, Scalar pitch, Scalar yaw )
{
  return setEulerYPR ( yaw, pitch, roll );
}

inline void test_ypr()
{
  Eigen::Matrix3d t0 = setRPY ( 30.0 / 180.0 * 3.1415926, -135.0 / 180.0 * 3.1415926, 120.0 / 180.0 * 3.1415926 );
  xc::math::Affine3 t1 = xc::math::rpy ( 30.0 / 180.0 * 3.1415926, -135.0 / 180.0 * 3.1415926, 120.0 / 180.0 * 3.1415926 );
  xc::math::colvec3 rpys1 = xc::math::irpy ( t1 , 1 ) / 3.1415926 * 180.0;
  xc::math::colvec3 rpys2 = xc::math::irpy ( t1 , 2 ) / 3.1415926 * 180.0;
  std::cout << t0.matrix() << std::endl;
  std::cout << t1.matrix() << std::endl;
  std::cout << "irpy(30 / 180 * 3.1415926, -135 / 180 * 3.1415926, 120 / 180 * 3.1415926) = " << rpys1.transpose() << std::endl;
  std::cout << "irpy(30 / 180 * 3.1415926, -135 / 180 * 3.1415926, 120 / 180 * 3.1415926) = " << rpys2.transpose() << std::endl;
}

inline void test_geometry()
{
  xc::math::Affine3 t0 = xc::math::rpy ( -150.0 / 180.0 * 3.1415926, -45.0 / 180.0 * 3.1415926, -60.0 / 180.0 * 3.1415926, false );
  xc::math::Affine3 t1 = xc::math::rpy ( 30.0 / 180.0 * 3.1415926, -135.0 / 180.0 * 3.1415926, 120.0 / 180.0 * 3.1415926, false );
  xc::math::colvec3 rpys1 = xc::math::irpy ( t1 , 1, false ) / 3.1415926 * 180.0;
  xc::math::colvec3 rpys2 = xc::math::irpy ( t1 , 2, false ) / 3.1415926 * 180.0;
  std::cout << t0.matrix() << std::endl;
  std::cout << t1.matrix() << std::endl;
  std::cout << "irpy(30 / 180 * 3.1415926, -135 / 180 * 3.1415926, 120 / 180 * 3.1415926) = " << rpys1.transpose() << std::endl;
  std::cout << "irpy(30 / 180 * 3.1415926, -135 / 180 * 3.1415926, 120 / 180 * 3.1415926) = " << rpys2.transpose() << std::endl;
}

inline void test_interpolate_linear_transform()
{
  xc::math::colvecX rs1 = xc::math::tpoly ( 0, 0, 0, 1.0, 0, 0, 16.0, 0.1 );
  xc::math::colvecX rs2 = xc::math::lspb ( 0, 1.0, 16.0, 0.1 );
  xc::math::Affine3 T1, T2;
  T1 = xc::math::translation ( 0.0, 0.0, 0.0 );
  T2 = xc::math::translation ( 100.0, 100.0, 0.0 ) * xc::math::rotx ( 90.0 / 180.0 * 3.1415926 ) * xc::math::rotz ( 90.0 / 180.0 * 3.1415926 );

  std::cout << "%test interpolate with tpoly" << std::endl;
  xc::math::VectorAffine3 rs3 = xc::math::interpolate_linear_transform ( T1, T2, rs1 );
  std::cout << "A=zeros(4,4," << rs3.size () << ");" << std::endl;
  for ( size_t i = 0; i < rs3.size (); ++i )
  {
    std::cout << "A(:,:," << i + 1 << ")=[" << rs3[i].matrix() << "];" << std::endl;
  }
  std::cout << "%-------------------------------------------------" << std::endl;
  std::cout << "%test interpolate with lspb" << std::endl;
  xc::math::VectorAffine3 rs4 = xc::math::interpolate_linear_transform ( T1, T2, rs2 );
  std::cout << "A=zeros(4,4," << rs4.size () << ");" << std::endl;
  for ( size_t i = 0; i < rs4.size (); ++i )
  {
    std::cout << "A(:,:," << i + 1 << ")=[" << rs4[i].matrix() << "];" << std::endl;
  }
}

inline void test_interpolate()
{
	xc::math::colvecX rs1 = xc::math::tpoly(0, 0, 0, 1.0, 0, 0, 15.0, 0.1);
	xc::math::colvecX rs2 = xc::math::lspb(0, 1.0, 15.0, 0.1);
	
	std::cout << "%test interpolate with tpoly" << std::endl;
	xc::math::matrix6X input;
	input.resize(6, 3);
	input << 0, 30, 0,
		0, 30, 0,
		0, 30, 0,
		0, 30, 0,
		0, 30, 0,
		0, 30, 0;
	xc::math::matrix6X output = xc::math::mcspline6(input, rs1);
	std::cout << "xs" << std::endl<< rs1 << std::endl;
	std::cout << "ys" << std::endl << output.transpose() << std::endl;
}

int main()
{
  //test_interpolate_linear_transform();
  //test_geometry();
	test_interpolate();
	system("pause");
;  return 1;
}
