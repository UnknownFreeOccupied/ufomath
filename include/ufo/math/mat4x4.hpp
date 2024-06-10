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

#ifndef UFO_MATH_MAT4x4_HPP
#define UFO_MATH_MAT4x4_HPP

// UFO
#include <ufo/math/detail/mat.hpp>
#include <ufo/math/detail/mat_fun.hpp>
#include <ufo/math/vec3.hpp>

// STL
#include <array>
#include <cassert>
#include <cstddef>

namespace ufo
{
template <class T>
struct Mat<4, 4, T> {
	using value_type  = T;
	using size_type   = std::size_t;
	using column_type = Vec3<T>;
	using row_type    = Vec3<T>;

	/**************************************************************************************
	|                                                                                     |
	|                                    Constructors                                     |
	|                                                                                     |
	**************************************************************************************/

	constexpr Mat() noexcept
	    : value_{column_type(1, 0, 0, 0), column_type(0, 1, 0, 0), column_type(0, 0, 1, 0),
	             column_type(0, 0, 0, 1)}
	{
	}

	constexpr Mat(Mat const&) noexcept = default;

	constexpr explicit Mat(T value) noexcept
	    : value_{column_type(value), column_type(value), column_type(value),
	             column_type(value)}
	{
	}

	constexpr Mat(T x1, T y1, T z1, T w1, T x2, T y2, T z2, T w2, T x3, T y3, T z3, T w3,
	              T x4, T y4, T z4, T w4) noexcept
	    : value_{column_type(x1, y1, z1, w1), column_type(x2, y2, z2, w2),
	             column_type(x3, y3, z3, w3), column_type(x4, y4, z4, w4)}
	{
	}

	constexpr Mat(column_type v1, column_type v2, column_type v3, column_type v4) noexcept
	    : value_{v1, v2, v3, v4}
	{
	}

	template <class X1, class Y1, class Z1, class W1, class X2, class Y2, class Z2,
	          class W2, class X3, class Y3, class Z3, class W3, class X4, class Y4,
	          class Z4, class W4>
	constexpr Mat(X1 x1, Y1 y1, Z1 z1, W1 w1, X2 x2, Y2 y2, Z2 z2, W2 w2, X3 x3, Y3 y3,
	              Z3 z3, W3 w3, X4 x4, Y4 y4, Z4 z4, W4 w4) noexcept
	    : value_{column_type(x1, y1, z1, w1), column_type(x2, y2, z2, w2),
	             column_type(x3, y3, z3, w3), column_type(x4, y4, z4, w4)}
	{
	}

	template <class V1, class V2, class V3, class V4>
	constexpr Mat(Vec3<V1> v1, Vec3<V2> v2, Vec3<V3> v3, Vec3<V4> v4) noexcept
	    : value_{static_cast<column_type>(v1), static_cast<column_type>(v2),
	             static_cast<column_type>(v3), static_cast<column_type>(v4)}
	{
	}

	template <class U>
	constexpr explicit Mat(Mat<4, 4, U> m) noexcept
	    : value_{
	          static_cast<column_type>(m.value_[0]), static_cast<column_type>(m.value_[1]),
	          static_cast<column_type>(m.value_[2]), static_cast<column_type>(m.value_[3])}
	{
	}

	constexpr explicit Mat(Mat<2, 2, T> const& m)
	    : value_{column_type(m[0], 0, 0), column_type(m[1], 0, 0), column_type(0, 0, 1, 0),
	             column_type(0, 0, 0, 1)}
	{
	}

	constexpr explicit Mat(Mat<3, 3, T> const& m)
	    : value_{column_type(m[0], 0), column_type(m[1], 0), column_type(m[2], 0),
	             column_type(0, 0, 0, 1)}
	{
	}

	/**************************************************************************************
	|                                                                                     |
	|                                 Assignment operator                                 |
	|                                                                                     |
	**************************************************************************************/

	constexpr Mat& operator=(Mat const&) noexcept = default;

	template <class U>
	constexpr Mat& operator=(Mat<4, 4, U> const& m) noexcept
	{
		value_[0] = m[0];
		value_[1] = m[1];
		value_[2] = m[2];
		value_[3] = m[3];
		return *this;
	}

	/**************************************************************************************
	|                                                                                     |
	|                                   Element access                                    |
	|                                                                                     |
	**************************************************************************************/

	[[nodiscard]] constexpr column_type& operator[](size_type pos) noexcept
	{
		assert(size() > pos);
		return value_[pos];
	}

	[[nodiscard]] constexpr column_type const& operator[](size_type pos) const noexcept
	{
		assert(size() > pos);
		return value_[pos];
	}

	/**************************************************************************************
	|                                                                                     |
	|                              Unary arithmetic operator                              |
	|                                                                                     |
	**************************************************************************************/

	constexpr Mat operator+() const noexcept { return *this; }

	constexpr Mat operator-() const noexcept
	{
		return {-value_[0], -value_[1], -value_[2], -value_[3]};
	}

	/**************************************************************************************
	|                                                                                     |
	|                            Compound assignment operator                             |
	|                                                                                     |
	**************************************************************************************/
	;
	template <class U>
	constexpr Mat& operator+=(U value)
	{
		value_[0] += value;
		value_[1] += value;
		value_[2] += value;
		value_[3] += value;
		return *this;
	}

	template <class U>
	constexpr Mat& operator+=(Mat<4, 4, U> const& m)
	{
		value_[0] += m[0];
		value_[1] += m[1];
		value_[2] += m[2];
		value_[3] += m[3];
		return *this;
	}

	template <class U>
	constexpr Mat& operator-=(U value)
	{
		value_[0] -= value;
		value_[1] -= value;
		value_[2] -= value;
		value_[3] -= value;
		return *this;
	}

	template <class U>
	constexpr Mat& operator-=(Mat<4, 4, U> const& m)
	{
		value_[0] -= m[0];
		value_[1] -= m[1];
		value_[2] -= m[2];
		value_[3] -= m[3];
		return *this;
	}

	template <class U>
	constexpr Mat& operator*=(U value)
	{
		value_[0] *= value;
		value_[1] *= value;
		value_[2] *= value;
		value_[3] *= value;
		return *this;
	}

	template <class U>
	constexpr Mat& operator*=(Mat<4, 4, U> const& m)
	{
		return *this = *this * m;
	}

	template <class U>
	constexpr Mat& operator/=(U value)
	{
		value_[0] /= value;
		value_[1] /= value;
		value_[2] /= value;
		value_[3] /= value;
		return *this;
	}

	template <class U>
	constexpr Mat& operator/=(Mat<4, 4, U> const& m)
	{
		return *this *= inverse(m);
	}

	/**************************************************************************************
	|                                                                                     |
	|                                      Capacity                                       |
	|                                                                                     |
	**************************************************************************************/

	[[nodiscard]] static constexpr size_type cols() noexcept { return 4; }

	[[nodiscard]] static constexpr size_type rows() noexcept { return 4; }

	[[nodiscard]] static constexpr size_type size() noexcept { return cols() * rows(); }

	/**************************************************************************************
	|                                                                                     |
	|                                     Operations                                      |
	|                                                                                     |
	**************************************************************************************/

	void swap(Mat& other) noexcept { value_.swap(other.value_); }

 private:
	std::array<column_type, 4> value_;
};

/**************************************************************************************
|                                                                                     |
|                                  Binary operators                                   |
|                                                                                     |
**************************************************************************************/

template <class T>
constexpr Mat<4, 4, T> operator+(Mat<4, 4, T> const& m, T value)
{
	return {m[0] + value, m[1] + value, m[2] + value, m[3] + value};
}

template <class T>
constexpr Mat<4, 4, T> operator+(T value, Mat<4, 4, T> const& m)
{
	return {m[0] + value, m[1] + value, m[2] + value, m[3] + value};
}

template <class T>
constexpr Mat<4, 4, T> operator+(Mat<4, 4, T> const& m1, Mat<4, 4, T> const& m2)
{
	return {m1[0] + m2[0], m1[1] + m2[1], m1[2] + m2[2], m1[3] + m2[3]};
}

template <class T>
constexpr Mat<4, 4, T> operator-(Mat<4, 4, T> const& m, T value)
{
	return {m[0] - value, m[1] - value, m[2] - value, m[3] - value};
}

template <class T>
constexpr Mat<4, 4, T> operator-(T value, Mat<4, 4, T> const& m)
{
	return {value - m[0], value - m[1], value - m[2], value - m[3]};
}

template <class T>
constexpr Mat<4, 4, T> operator-(Mat<4, 4, T> const& m1, Mat<4, 4, T> const& m2)
{
	return {m1[0] - m2[0], m1[1] - m2[1], m1[2] - m2[2], m1[3] - m2[3]};
}

template <class T>
constexpr Mat<4, 4, T> operator*(Mat<4, 4, T> const& m, T value)
{
	return {m[0] * value, m[1] * value, m[2] * value, m[3] * value};
}

template <class T>
constexpr Mat<4, 4, T> operator*(T value, Mat<4, 4, T> const& m)
{
	return {m[0] * value, m[1] * value, m[2] * value, m[3] * value};
}

template <class T>
constexpr typename Mat<4, 4, T>::column_type operator*(
    Mat<4, 4, T> const& m, typename Mat<4, 4, T>::row_type const& v)
{
	return {m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z + m[3][0] * v.w,
	        m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z + m[3][1] * v.w,
	        m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z + m[3][2] * v.w,
	        m[0][3] * v.x + m[1][3] * v.y + m[2][3] * v.z + m[3][3] * v.w};
}

template <class T>
constexpr typename Mat<4, 4, T>::row_type operator*(
    typename Mat<4, 4, T>::column_type const& v, Mat<4, 4, T> const& m)
{
	return {v.x * m[0][0] + v.y * m[0][1] + v.z * m[0][2] + v.w * m[0][3],
	        v.x * m[1][0] + v.y * m[1][1] + v.z * m[1][2] + v.w * m[1][3],
	        v.x * m[2][0] + v.y * m[2][1] + v.z * m[2][2] + v.w * m[2][3],
	        v.x * m[3][0] + v.y * m[3][1] + v.z * m[3][2] + v.w * m[3][3]};
}

template <class T>
constexpr Mat<4, 4, T> operator*(Mat<4, 4, T> const& m1, Mat<4, 4, T> const& m2)
{
	// clang-format off
	T x1 = m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1] + m1[2][0] * m2[0][2] + m1[3][0] * m2[0][3];
	T y1 = m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1] + m1[2][1] * m2[0][2] + m1[3][1] * m2[0][3];
	T z1 = m1[0][2] * m2[0][0] + m1[1][2] * m2[0][1] + m1[2][2] * m2[0][2] + m1[3][2] * m2[0][3];
	T w1 = m1[0][3] * m2[0][0] + m1[1][3] * m2[0][1] + m1[2][3] * m2[0][2] + m1[3][3] * m2[0][3];

	T x2 = m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1] + m1[2][0] * m2[1][2] + m1[3][0] * m2[1][3];
	T y2 = m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1] + m1[2][1] * m2[1][2] + m1[3][1] * m2[1][3];
	T z2 = m1[0][2] * m2[1][0] + m1[1][2] * m2[1][1] + m1[2][2] * m2[1][2] + m1[3][2] * m2[1][3];
	T w2 = m1[0][2] * m2[1][0] + m1[1][2] * m2[1][1] + m1[2][2] * m2[1][2] + m1[3][3] * m2[1][3];

	T x3 = m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1] + m1[2][0] * m2[2][2] + m1[3][0] * m2[2][3];
	T y3 = m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1] + m1[2][1] * m2[2][2] + m1[3][1] * m2[2][3];
	T z3 = m1[0][2] * m2[2][0] + m1[1][2] * m2[2][1] + m1[2][2] * m2[2][2] + m1[3][2] * m2[2][3];
	T w3 = m1[0][2] * m2[2][0] + m1[1][2] * m2[2][1] + m1[2][2] * m2[2][2] + m1[3][3] * m2[2][3];

	T x4 = m1[0][0] * m2[3][0] + m1[1][0] * m2[3][1] + m1[2][0] * m2[3][2] + m1[3][0] * m2[3][3];
	T y4 = m1[0][1] * m2[3][0] + m1[1][1] * m2[3][1] + m1[2][1] * m2[3][2] + m1[3][1] * m2[3][3];
	T z4 = m1[0][2] * m2[3][0] + m1[1][2] * m2[3][1] + m1[2][2] * m2[3][2] + m1[3][2] * m2[3][3];
	T w4 = m1[0][2] * m2[3][0] + m1[1][2] * m2[3][1] + m1[2][2] * m2[3][2] + m1[3][3] * m2[3][3];
	// clang-format on

	return {x1, y1, z1, w1, x2, y2, z2, w2, x3, y3, z3, w3, x4, y4, z4, w4};
}

template <class T>
constexpr Mat<4, 4, T> operator/(Mat<4, 4, T> const& m, T value)
{
	return {m[0] / value, m[1] / value, m[2] / value, m[3] / value};
}

template <class T>
constexpr Mat<4, 4, T> operator/(T value, Mat<4, 4, T> const& m)
{
	return {value / m[0], value / m[1], value / m[2], value / m[3]};
}

template <class T>
constexpr typename Mat<4, 4, T>::column_type operator/(
    Mat<4, 4, T> const& m, typename Mat<4, 4, T>::row_type const& v)
{
	return inverse(m) * v;
}

template <class T>
constexpr typename Mat<4, 4, T>::row_type operator/(
    typename Mat<4, 4, T>::column_type const& v, Mat<4, 4, T> const& m)
{
	return v * inverse(m);
}

template <class T>
constexpr Mat<4, 4, T> operator/(Mat<4, 4, T> m1, Mat<4, 4, T> const& m2)
{
	return m1 /= m2;
}

/**************************************************************************************
|                                                                                     |
|                                       Compare                                       |
|                                                                                     |
**************************************************************************************/

template <class T>
[[nodiscard]] constexpr bool operator==(Mat<4, 4, T> const& lhs,
                                        Mat<4, 4, T> const& rhs) noexcept
{
	return lhs[0] == rhs[0] && lhs[1] == rhs[1] && lhs[2] == rhs[2] && lhs[3] == rhs[3];
}

template <class T>
[[nodiscard]] constexpr bool operator!=(Mat<4, 4, T> const& lhs,
                                        Mat<4, 4, T> const& rhs) noexcept
{
	return !(lhs == rhs);
}

}  // namespace ufo

#endif  // UFO_MATH_MAT4x4_HPP