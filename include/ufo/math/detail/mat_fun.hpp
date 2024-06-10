/*!
 * UFOMap: An Efficient Probabilistic 3D Mapping Framework That Embraces the
 * Unknown
 *
 * @author Daniel Duberg (dduberg@kth.se)
 * @see https://github.com/UnknownFreeOccupied/ufomap
 * @version 1.0
 * @date 2022-05-13
 *
 * @copyright Copyright (c) 2022, Daniel Duberg, KTH Royal Institute of
 * Technology
 *
 * BSD 3-Clause License
 *
 * Copyright (c) 2022, Daniel Duberg, KTH Royal Institute of Technology
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *     and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *     contributors may be used to endorse or promote products derived from
 *     this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef UFO_MATH_DETAIL_MAT_FUN_HPP
#define UFO_MATH_DETAIL_MAT_FUN_HPP

// UFO
#include <ufo/math/detail/mat.hpp>
#include <ufo/math/detail/vec.hpp>

// STL
#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iomanip>
#include <ostream>
#include <sstream>

namespace ufo
{
template <std::size_t Cols, std::size_t Rows, class T>
std::ostream& operator<<(std::ostream& out, Mat<Cols, Rows, T> m)
{
	auto length = [&out](T value) {
		std::ostringstream ss;
		ss.copyfmt(out);
		ss << value;
		return ss.str().size();
	};

	std::array<std::size_t, Cols> column_length{};
	for (std::size_t col{}; Cols > col; ++col) {
		for (std::size_t row{}; Rows > row; ++row) {
			column_length[col] = std::max(column_length[col], length(m[col][row]));
		}
	}

	out << std::setw(column_length[0]) << m[0][0];
	for (std::size_t col = 1; Cols > col; ++col) {
		out << ' ' << std::setw(column_length[col]) << m[col][0];
	}

	for (std::size_t row = 1; Rows > row; ++row) {
		out << '\n';
		out << std::setw(column_length[0]) << m[0][row];
		for (std::size_t col = 1; Cols > col; ++col) {
			out << ' ' << std::setw(column_length[col]) << m[col][row];
		}
	}

	return out;
}

template <std::size_t Cols, std::size_t Rows, class T>
[[nodiscard]] Mat<Rows, Cols, T> transpose(Mat<Cols, Rows, T> const& m)
{
	Mat<Rows, Cols, T> t;
	for (std::size_t row{}; Rows > row; ++row) {
		for (std::size_t col{}; Cols > col; ++col) {
			t[col][row] = m[row][col];
		}
	}
	return t;
}

template <std::size_t Cols, std::size_t Rows, class T>
[[nodiscard]] Mat<Cols, Rows, T> inverse(Mat<Cols, Rows, T> const& m)
{
	if constexpr (2 == Cols && 2 == Rows) {
		T d = static_cast<T>(1) / determinant(m);
		return {m[1][1] * d, -m[0][1] * d, -m[1][0] * d, m[0][0] * d};
	} else if constexpr (3 == Cols && 3 == Rows) {
		T d = static_cast<T>(1) / determinant(m);

		Mat<3, 3, T> res;
		res[0][0] = (m[1][1] * m[2][2] - m[2][1] * m[1][2]);
		res[1][0] = -(m[1][0] * m[2][2] - m[2][0] * m[1][2]);
		res[2][0] = (m[1][0] * m[2][1] - m[2][0] * m[1][1]);
		res[0][1] = -(m[0][1] * m[2][2] - m[2][1] * m[0][2]);
		res[1][1] = (m[0][0] * m[2][2] - m[2][0] * m[0][2]);
		res[2][1] = -(m[0][0] * m[2][1] - m[2][0] * m[0][1]);
		res[0][2] = (m[0][1] * m[1][2] - m[1][1] * m[0][2]);
		res[1][2] = -(m[0][0] * m[1][2] - m[1][0] * m[0][2]);
		res[2][2] = (m[0][0] * m[1][1] - m[1][0] * m[0][1]);

		res *= d;
		return res;
	} else if constexpr (4 == Cols && 4 == Rows) {
		T coef00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
		T coef02 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
		T coef03 = m[1][2] * m[2][3] - m[2][2] * m[1][3];

		T coef04 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
		T coef06 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
		T coef07 = m[1][1] * m[2][3] - m[2][1] * m[1][3];

		T coef08 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
		T coef10 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
		T coef11 = m[1][1] * m[2][2] - m[2][1] * m[1][2];

		T coef12 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
		T coef14 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
		T coef15 = m[1][0] * m[2][3] - m[2][0] * m[1][3];

		T coef16 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
		T coef18 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
		T coef19 = m[1][0] * m[2][2] - m[2][0] * m[1][2];

		T coef20 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
		T coef22 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
		T coef23 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

		Vec<4, T> fac0(coef00, coef00, coef02, coef03);
		Vec<4, T> fac1(coef04, coef04, coef06, coef07);
		Vec<4, T> fac2(coef08, coef08, coef10, coef11);
		Vec<4, T> fac3(coef12, coef12, coef14, coef15);
		Vec<4, T> fac4(coef16, coef16, coef18, coef19);
		Vec<4, T> fac5(coef20, coef20, coef22, coef23);

		Vec<4, T> vec0(m[1][0], m[0][0], m[0][0], m[0][0]);
		Vec<4, T> vec1(m[1][1], m[0][1], m[0][1], m[0][1]);
		Vec<4, T> vec2(m[1][2], m[0][2], m[0][2], m[0][2]);
		Vec<4, T> vec3(m[1][3], m[0][3], m[0][3], m[0][3]);

		Vec<4, T> Inv0(vec1 * fac0 - vec2 * fac1 + vec3 * fac2);
		Vec<4, T> Inv1(vec0 * fac0 - vec2 * fac3 + vec3 * fac4);
		Vec<4, T> Inv2(vec0 * fac1 - vec1 * fac3 + vec3 * fac5);
		Vec<4, T> Inv3(vec0 * fac2 - vec1 * fac4 + vec2 * fac5);

		Vec<4, T>    signA(+1, -1, +1, -1);
		Vec<4, T>    signB(-1, +1, -1, +1);
		Mat<4, 4, T> res(Inv0 * signA, Inv1 * signB, Inv2 * signA, Inv3 * signB);

		Vec<4, T> row0(res[0][0], res[1][0], res[2][0], res[3][0]);

		Vec<4, T> dot0(m[0] * row0);
		T         dot1 = (dot0.x + dot0.y) + (dot0.z + dot0.w);

		T d = static_cast<T>(1) / dot1;

		return res * d;
	} else {
		// Error
	}
}

template <std::size_t Cols, std::size_t Rows, class T>
[[nodiscard]] T determinant(Mat<Cols, Rows, T> const& m)
{
	if constexpr (2 == Cols && 2 == Rows) {
		return m[0][0] * m[1][1] - m[1][0] * m[0][1];
	} else if constexpr (3 == Cols && 3 == Rows) {
		return m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2]) -
		       m[1][0] * (m[0][1] * m[2][2] - m[2][1] * m[0][2]) +
		       m[2][0] * (m[0][1] * m[1][2] - m[1][1] * m[0][2]);
	} else if constexpr (4 == Cols && 4 == Rows) {
		return m[3][0] * m[2][1] * m[1][2] * m[0][3] - m[2][0] * m[3][1] * m[1][2] * m[0][3] -
		       m[3][0] * m[1][1] * m[2][2] * m[0][3] + m[1][0] * m[3][1] * m[2][2] * m[0][3] +
		       m[2][0] * m[1][1] * m[3][2] * m[0][3] - m[1][0] * m[2][1] * m[3][2] * m[0][3] -
		       m[3][0] * m[2][1] * m[0][2] * m[1][3] + m[2][0] * m[3][1] * m[0][2] * m[1][3] +
		       m[3][0] * m[0][1] * m[2][2] * m[1][3] - m[0][0] * m[3][1] * m[2][2] * m[1][3] -
		       m[2][0] * m[0][1] * m[3][2] * m[1][3] + m[0][0] * m[2][1] * m[3][2] * m[1][3] +
		       m[3][0] * m[1][1] * m[0][2] * m[2][3] - m[1][0] * m[3][1] * m[0][2] * m[2][3] -
		       m[3][0] * m[0][1] * m[1][2] * m[2][3] + m[0][0] * m[3][1] * m[1][2] * m[2][3] +
		       m[1][0] * m[0][1] * m[3][2] * m[2][3] - m[0][0] * m[1][1] * m[3][2] * m[2][3] -
		       m[2][0] * m[1][1] * m[0][2] * m[3][3] + m[1][0] * m[2][1] * m[0][2] * m[3][3] +
		       m[2][0] * m[0][1] * m[1][2] * m[3][3] - m[0][0] * m[2][1] * m[1][2] * m[3][3] -
		       m[1][0] * m[0][1] * m[2][2] * m[3][3] + m[0][0] * m[1][1] * m[2][2] * m[3][3];
	} else {
		static_assert(
		    Cols != Rows,
		    "Cols has to be equal to Rows (only implemented for 2x2, 3x3, and 4x4)");
	}
}
}  // namespace ufo

#endif  // UFO_MATH_DETAIL_MAT_FUN_HPP