/*!
 * UFOMap: An Efficient Probabilistic 3D Mapping Framework That Embraces the
 * Unknown
 *
 * @author Daniel Duberg (dduberg@kth.se)
 * @see https://github.com/UnknownFreeOccupied/ufomath
 * @version 2.0
 * @date 2024-06-14
 *
 * @copyright Copyright (c) 2024, Daniel Duberg
 *
 * BSD 3-Clause License
 *
 * Copyright (c) 2024, Daniel Duberg
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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

	out << std::setw(static_cast<int>(column_length[0])) << m[0][0];
	for (std::size_t col = 1; Cols > col; ++col) {
		out << ' ' << std::setw(static_cast<int>(column_length[col])) << m[col][0];
	}

	for (std::size_t row = 1; Rows > row; ++row) {
		out << '\n';
		out << std::setw(static_cast<int>(column_length[0])) << m[0][row];
		for (std::size_t col = 1; Cols > col; ++col) {
			out << ' ' << std::setw(static_cast<int>(column_length[col])) << m[col][row];
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
		T Coef00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
		T Coef02 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
		T Coef03 = m[1][2] * m[2][3] - m[2][2] * m[1][3];

		T Coef04 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
		T Coef06 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
		T Coef07 = m[1][1] * m[2][3] - m[2][1] * m[1][3];

		T Coef08 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
		T Coef10 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
		T Coef11 = m[1][1] * m[2][2] - m[2][1] * m[1][2];

		T Coef12 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
		T Coef14 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
		T Coef15 = m[1][0] * m[2][3] - m[2][0] * m[1][3];

		T Coef16 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
		T Coef18 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
		T Coef19 = m[1][0] * m[2][2] - m[2][0] * m[1][2];

		T Coef20 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
		T Coef22 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
		T Coef23 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

		Vec<4, T> Fac0(Coef00, Coef00, Coef02, Coef03);
		Vec<4, T> Fac1(Coef04, Coef04, Coef06, Coef07);
		Vec<4, T> Fac2(Coef08, Coef08, Coef10, Coef11);
		Vec<4, T> Fac3(Coef12, Coef12, Coef14, Coef15);
		Vec<4, T> Fac4(Coef16, Coef16, Coef18, Coef19);
		Vec<4, T> Fac5(Coef20, Coef20, Coef22, Coef23);

		Vec<4, T> Vec0(m[1][0], m[0][0], m[0][0], m[0][0]);
		Vec<4, T> Vec1(m[1][1], m[0][1], m[0][1], m[0][1]);
		Vec<4, T> Vec2(m[1][2], m[0][2], m[0][2], m[0][2]);
		Vec<4, T> Vec3(m[1][3], m[0][3], m[0][3], m[0][3]);

		Vec<4, T> Inv0(Vec1 * Fac0 - Vec2 * Fac1 + Vec3 * Fac2);
		Vec<4, T> Inv1(Vec0 * Fac0 - Vec2 * Fac3 + Vec3 * Fac4);
		Vec<4, T> Inv2(Vec0 * Fac1 - Vec1 * Fac3 + Vec3 * Fac5);
		Vec<4, T> Inv3(Vec0 * Fac2 - Vec1 * Fac4 + Vec2 * Fac5);

		Vec<4, T>    SignA(+1, -1, +1, -1);
		Vec<4, T>    SignB(-1, +1, -1, +1);
		Mat<4, 4, T> Inverse(Inv0 * SignA, Inv1 * SignB, Inv2 * SignA, Inv3 * SignB);

		Vec<4, T> Row0(Inverse[0][0], Inverse[1][0], Inverse[2][0], Inverse[3][0]);

		Vec<4, T> Dot0(m[0] * Row0);
		T         Dot1 = (Dot0.x + Dot0.y) + (Dot0.z + Dot0.w);

		T OneOverDeterminant = static_cast<T>(1) / Dot1;

		return Inverse * OneOverDeterminant;
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

template <class T>
[[nodiscard]] Mat<4, 4, T> orthogonal(T left, T right, T bottom, T top)
{
	Mat<4, 4, T> m(T(1));
	m[0][0] = T(2) / (right - left);
	m[1][1] = T(2) / (top - bottom);
	m[2][2] = -T(1);
	m[3][0] = -(right + left) / (right - left);
	m[3][1] = -(top + bottom) / (top - bottom);
	return m;
}

template <class T, bool RightHanded = true, bool ZeroToOne = true>
[[nodiscard]] Mat<4, 4, T> orthogonal(T left, T right, T bottom, T top, T zNear, T zFar)
{
	Mat<4, 4, T> m(1);

	if constexpr (RightHanded && ZeroToOne) {
		m[0][0] = T(2) / (right - left);
		m[1][1] = T(2) / (top - bottom);
		m[2][2] = -T(1) / (zFar - zNear);
		m[3][0] = -(right + left) / (right - left);
		m[3][1] = -(top + bottom) / (top - bottom);
		m[3][2] = -zNear / (zFar - zNear);
	} else if constexpr (RightHanded && !ZeroToOne) {
		m[0][0] = T(2) / (right - left);
		m[1][1] = T(2) / (top - bottom);
		m[2][2] = -T(2) / (zFar - zNear);
		m[3][0] = -(right + left) / (right - left);
		m[3][1] = -(top + bottom) / (top - bottom);
		m[3][2] = -(zFar + zNear) / (zFar - zNear);
	} else if constexpr (!RightHanded && ZeroToOne) {
		m[0][0] = T(2) / (right - left);
		m[1][1] = T(2) / (top - bottom);
		m[2][2] = T(1) / (zFar - zNear);
		m[3][0] = -(right + left) / (right - left);
		m[3][1] = -(top + bottom) / (top - bottom);
		m[3][2] = -zNear / (zFar - zNear);
	} else if constexpr (!RightHanded && !ZeroToOne) {
		m[0][0] = T(2) / (right - left);
		m[1][1] = T(2) / (top - bottom);
		m[2][2] = T(2) / (zFar - zNear);
		m[3][0] = -(right + left) / (right - left);
		m[3][1] = -(top + bottom) / (top - bottom);
		m[3][2] = -(zFar + zNear) / (zFar - zNear);
	}

	return m;
}

template <class T, bool RightHanded = true, bool ZeroToOne = true>
[[nodiscard]] Mat<4, 4, T> perspective(T fovy, T aspect, T near, T far)
{
	Mat<4, 4, T> m(T(0));

	T const tan_half_fovy = std::tan(fovy / T(2));

	if constexpr (RightHanded && ZeroToOne) {
		m[0][0] = T(1) / (aspect * tan_half_fovy);
		m[1][1] = T(1) / (tan_half_fovy);
		m[2][2] = far / (near - far);
		m[2][3] = -T(1);
		m[3][2] = -(far * near) / (far - near);
	} else if constexpr (RightHanded && !ZeroToOne) {
		m[0][0] = T(1) / (aspect * tan_half_fovy);
		m[1][1] = T(1) / (tan_half_fovy);
		m[2][2] = -(far + near) / (far - near);
		m[2][3] = -T(1);
		m[3][2] = -(T(2) * far * near) / (far - near);
	} else if constexpr (!RightHanded && ZeroToOne) {
		m[0][0] = T(1) / (aspect * tan_half_fovy);
		m[1][1] = T(1) / (tan_half_fovy);
		m[2][2] = far / (far - near);
		m[2][3] = T(1);
		m[3][2] = -(far * near) / (far - near);
	} else if constexpr (!RightHanded && !ZeroToOne) {
		m[0][0] = T(1) / (aspect * tan_half_fovy);
		m[1][1] = T(1) / (tan_half_fovy);
		m[2][2] = (far + near) / (far - near);
		m[2][3] = T(1);
		m[3][2] = -(T(2) * far * near) / (far - near);
	}

	return m;
}

template <class T, bool RightHanded = true, bool ZeroToOne = true>
[[nodiscard]] Mat<4, 4, T> infinitePerspective(T fovy, T aspect, T near)
{
	Mat<4, 4, T> m(T(0));

	T const range  = std::tan(fovy / T(2)) * near;
	T const left   = -range * aspect;
	T const right  = range * aspect;
	T const bottom = -range;
	T const top    = range;

	if constexpr (RightHanded && ZeroToOne) {
		m[0][0] = (T(2) * near) / (right - left);
		m[1][1] = (T(2) * near) / (top - bottom);
		m[2][2] = -T(1);
		m[2][3] = -T(1);
		m[3][2] = -near;
	} else if constexpr (RightHanded && !ZeroToOne) {
		m[0][0] = (T(2) * near) / (right - left);
		m[1][1] = (T(2) * near) / (top - bottom);
		m[2][2] = -T(1);
		m[2][3] = -T(1);
		m[3][2] = -T(2) * near;
	} else if constexpr (!RightHanded && ZeroToOne) {
		m[0][0] = (T(2) * near) / (right - left);
		m[1][1] = (T(2) * near) / (top - bottom);
		m[2][2] = T(1);
		m[2][3] = T(1);
		m[3][2] = -near;
	} else if constexpr (!RightHanded && !ZeroToOne) {
		m[0][0] = (T(2) * near) / (right - left);
		m[1][1] = (T(2) * near) / (top - bottom);
		m[2][2] = T(1);
		m[2][3] = T(1);
		m[3][2] = -T(2) * near;
	}

	return m;
}

template <class T, bool RightHanded = true>
[[nodiscard]] Mat<4, 4, T> lookAt(Vec<3, T> const& eye, Vec<3, T> const& target,
                                  Vec<3, T> const& up)
{
	Mat<4, 4, T> m(1);

	if constexpr (RightHanded) {
		Vec<3, T> const f(normalize(target - eye));
		Vec<3, T> const s(normalize(cross(f, up)));
		Vec<3, T> const u(cross(s, f));

		m[0][0] = s.x;
		m[1][0] = s.y;
		m[2][0] = s.z;
		m[0][1] = u.x;
		m[1][1] = u.y;
		m[2][1] = u.z;
		m[0][2] = -f.x;
		m[1][2] = -f.y;
		m[2][2] = -f.z;
		m[3][0] = -dot(s, eye);
		m[3][1] = -dot(u, eye);
		m[3][2] = dot(f, eye);
	} else {
		Vec<3, T> const f(normalize(target - eye));
		Vec<3, T> const s(normalize(cross(up, f)));
		Vec<3, T> const u(cross(f, s));

		m[0][0] = s.x;
		m[1][0] = s.y;
		m[2][0] = s.z;
		m[0][1] = u.x;
		m[1][1] = u.y;
		m[2][1] = u.z;
		m[0][2] = f.x;
		m[1][2] = f.y;
		m[2][2] = f.z;
		m[3][0] = -dot(s, eye);
		m[3][1] = -dot(u, eye);
		m[3][2] = -dot(f, eye);
	}

	return m;
}

template <class T>
[[nodiscard]] Mat<4, 4, T> rotate(Mat<4, 4, T> const& m, T angle, Vec<3, T> const& v)
{
	T const a = angle;
	T const c = std::cos(a);
	T const s = std::sin(a);

	Vec<3, T> axis(normalize(v));
	Vec<3, T> temp((T(1) - c) * axis);

	Mat<3, 3, T> rotate;
	rotate[0][0] = c + temp[0] * axis[0];
	rotate[0][1] = temp[0] * axis[1] + s * axis[2];
	rotate[0][2] = temp[0] * axis[2] - s * axis[1];

	rotate[1][0] = temp[1] * axis[0] - s * axis[2];
	rotate[1][1] = c + temp[1] * axis[1];
	rotate[1][2] = temp[1] * axis[2] + s * axis[0];

	rotate[2][0] = temp[2] * axis[0] + s * axis[1];
	rotate[2][1] = temp[2] * axis[1] - s * axis[0];
	rotate[2][2] = c + temp[2] * axis[2];

	Mat<4, 4, T> result;
	result[0] = m[0] * rotate[0][0] + m[1] * rotate[0][1] + m[2] * rotate[0][2];
	result[1] = m[0] * rotate[1][0] + m[1] * rotate[1][1] + m[2] * rotate[1][2];
	result[2] = m[0] * rotate[2][0] + m[1] * rotate[2][1] + m[2] * rotate[2][2];
	result[3] = m[3];
	return result;
}
}  // namespace ufo

#endif  // UFO_MATH_DETAIL_MAT_FUN_HPP