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
//#include <unsupported/Eigen/Splines>
#include <xc/math/xc_eigen/unsupported/Eigen/MonotoneCubicInterpolation>
#include <xc/math/xc_eigen/unsupported/Eigen/Splines>

namespace xc
{
	namespace math
	{

		using Eigen::Spline;
        using Eigen::MCI;

		template<int Cols>
		inline Matrix< Real, Cols, Eigen::Dynamic > _ret spline(Matrix < Real, Cols, Eigen::Dynamic > _in ps, colvecX _in rs, Eigen::DenseIndex degree = 2)
		{
			typedef Spline<Real, Cols> spline;

			// check rs equals to [rmin, rmax], rmax > rmin
			const Real rmin = rs(0);
			const Real rmax = rs(rs.size() - 1);
			const Real rl = rmax - rmin;
			assert(!is_zero(rl));
			for (size_t i = 1; i < rs.size(); ++i)
				assert(rs(i) > rs(i - 1));

            // check ps no less than 2
            assert ( ps.cols () >= 2 );

			// spline
			const spline spl = Eigen::SplineFitting<spline>::Interpolate(ps, degree);

			// interpolate
			Matrix< Real, Cols, Eigen::Dynamic > ret(Cols, rs.size());
			for (size_t i = 0; i < rs.size(); ++i)
			{
				ret.col(i) = spl((rs(i) - rmin) / rl);
			}
			return ret;
		}

		template<int Cols>
		inline Matrix< Real, Cols, Eigen::Dynamic > _ret mcspline(Matrix < Real, Cols, Eigen::Dynamic > _in ps, colvecX _in rs)
		{
            typedef MCI<Real, Cols> MCI;

			// check rs equals to [rmin, rmax], rmax > rmin
			const Real rmin = rs(0);
			const Real rmax = rs(rs.size() - 1);
			const Real rl = rmax - rmin;
			assert(!is_zero(rl));
			for (size_t i = 1; i < rs.size(); ++i)
				assert(rs(i) > rs(i - 1));

			// check ps less than 2
			assert(ps.cols() >= 2);

			// spline
            const MCI spl = Eigen::MCHI<MCI>::Interpolate(ps);

			// interpolate
			Matrix< Real, Cols, Eigen::Dynamic > ret(Cols, rs.size());
			for (size_t i = 0; i < rs.size(); ++i)
			{
				ret.col(i) = spl((rs(i) - rmin) / rl);
			}
			return ret;
		}

		inline Matrix< Real, 6, Eigen::Dynamic > _ret spline6(Matrix < Real, 6, Eigen::Dynamic > _in ps, colvecX _in rs)
		{
			typedef Spline<Real, 6> spline;

			// check rs equals to [rmin, rmax], rmax > rmin
			const Real rmin = rs(0);
			const Real rmax = rs(rs.size() - 1);
			const Real rl = rmax - rmin;
			assert(!is_zero(rl));
			for (colvecX::Index i = 1; i < rs.size(); ++i)
				assert(rs(i) > rs(i - 1));

			// check ps no less than 2
			assert(ps.cols() >= 2);

			// spline
			const spline spl = Eigen::SplineFitting<spline>::Interpolate(ps, 2);

			// interpolate
			Matrix< Real, 6, Eigen::Dynamic > ret(6, rs.size());
			for (colvecX::Index i = 0; i < rs.size(); ++i)
			{
				ret.col(i) = spl((rs(i) - rmin) / rl);
			}
			return ret;
		}

		inline Matrix< Real, 6, Eigen::Dynamic > _ret mcspline6(Matrix < Real, 6, Eigen::Dynamic > _in ps, colvecX _in rs)
		{
            typedef MCI<Real, 6> MCI6;

			// check rs equals to [rmin, rmax], rmax > rmin
			const Real rmin = rs(0);
			const Real rmax = rs(rs.size() - 1);
			const Real rl = rmax - rmin;
			assert(!is_zero(rl));
			for (colvecX::Index i = 1; i < rs.size(); ++i)
				assert(rs(i) > rs(i - 1));

			// check ps less than 2
			assert(ps.cols() >= 2);

			// spline
            const MCI6 spl = Eigen::MCHI<MCI6>::Interpolate(ps);

			// interpolate
			Matrix< Real, 6, Eigen::Dynamic > ret(6, rs.size());
			for (colvecX::Index i = 0; i < rs.size(); ++i)
			{
				ret.col(i) = spl((rs(i) - rmin) / rl);
			}
			return ret;
		}
	}
}

