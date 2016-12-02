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
		//lspb--------------------------------------------------------------------------
		inline colvecX _ret lspb(Real _in q0, Real _in q1,
			Real _in tf, Real _in step, Real _in v)
		{
			assert(v >= (q1 - q0) / tf);
			assert(v <= 2.0 * (q1 - q0) / tf);
			colvecX::Index size = static_cast<colvecX::Index>(std::floor(tf / step)) + 1;

			if (is_zero(q1 - q0))
			{
				colvecX ret;
				ret.resize(size);
				ret.fill(q0);
				return ret;
			}
			colvecX ret;
			ret.resize(size);
			double tb = (q0 - q1 + v * tf) / v;
			double a = v / tb;
			for (DenseIndex i = 0; i < ret.size(); ++i)
			{
				double tt = step * i;
				if (tt < tb)
				{
					ret(i) = q0 + a / 2.0 * tt * tt;
				}
				else if (tt <= tf - tb)
				{
					ret(i) = (q1 + q0 - v * tf) / 2.0 + v * tt;
				}
				else
				{
					ret(i) = q1 - a / 2.0 * tf * tf + a * tf * tt - a / 2.0 * tt * tt;
				}
			}
			return ret;
		}

		inline colvecX _ret lspb(Real _in q0, Real _in q1, Real _in tf, Real _in step)
		{
			double V = (q1 - q0) / tf * 1.5;
			return lspb(q0, q1, tf, step, V);
		}

		//tpoly-------------------------------------------------------------------------
		inline colvecX tpoly(Real _in q0, Real _in qd0, Real _in qdd0,
			Real _in qf, Real _in qdf, Real _in qddf,
			Real _in tf, Real _in step)
		{
			colvecX::Index size = static_cast<colvecX::Index>(std::floor(tf / step)) + 1;
			matrix66 x;
			x << 0, 0, 0, 0, 0, 1,
				std::pow(tf, 5), std::pow(tf, 4), std::pow(tf, 3), std::pow(tf, 2), tf, 1,
				0, 0, 0, 0, 1, 0,
				5 * std::pow(tf, 4), 4 * std::pow(tf, 3), 3 * std::pow(tf, 2), 2 * tf, 1, 0,
				0, 0, 0, 2, 0, 0,
				20 * std::pow(tf, 3), 12 * std::pow(tf, 2), 6 * tf, 2, 0, 0;
			colvec6 p;
			p << q0, qf, qd0, qdf, qdd0, qddf;
			rowvec6 coff = (x.inverse() * p).transpose();
			colvecX ret;
			ret.resize(size);
			colvec6 ts;
			for (DenseIndex i = 0; i < ret.size(); ++i)
			{
				double tt = step * i;
				ts << std::pow(tt, 5), std::pow(tt, 4), std::pow(tt, 3), std::pow(tt, 2), tt, 1;
				ret(i) = coff * ts;
			}
			return ret;
		}
	}
}
