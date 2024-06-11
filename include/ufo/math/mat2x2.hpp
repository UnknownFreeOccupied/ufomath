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

#ifndef UFO_MATH_MAT2x2_HPP
#define UFO_MATH_MAT2x2_HPP

// UFO
#include <ufo/math/detail/mat.hpp>
#include <ufo/math/detail/mat_fun.hpp>
#include <ufo/math/vec2.hpp>

// STL
#include <array>
#include <cassert>
#include <cstddef>

namespace ufo
{
template <class T>
struct Mat<2, 2, T> {
	using value_type  = T;
	using size_type   = std::size_t;
	using column_type = Vec2<T>;
	using row_type    = Vec2<T>;

	/**************************************************************************************
	|                                                                                     |
	|                                    Constructors                                     |
	|                                                                                     |
	**************************************************************************************/

	constexpr Mat() noexcept : value_{column_type(1, 0), column_type(0, 1)} {}

	constexpr Mat(Mat const&) noexcept = default;

	constexpr explicit Mat(T value) noexcept
	    : value_{column_type(value), column_type(value)}
	{
	}

	constexpr Mat(T x1, T y1, T x2, T y2) noexcept
	    : value_{column_type(x1, y1), column_type(x2, y2)}
	{
	}

	constexpr Mat(column_type v1, column_type v2) noexcept : value_{v1, v2} {}

	template <class X1, class Y1, class X2, class Y2>
	constexpr Mat(X1 x1, Y1 y1, X2 x2, Y2 y2) noexcept
	    : value_{column_type(x1, y1), column_type(x2, y2)}
	{
	}

	template <class U, class V>
	constexpr Mat(Vec2<U> v1, Vec2<V> v2) noexcept
	    : value_{static_cast<column_type>(v1), static_cast<column_type>(v2)}
	{
	}

	template <class U>
	constexpr explicit Mat(Mat<2, 2, U> m) noexcept
	    : value_{static_cast<column_type>(m.value_[0]),
	             static_cast<column_type>(m.value_[1])}
	{
	}

	constexpr explicit Mat(Mat<3, 3, T> const& m)
	    : value_{column_type(m[0]), column_type(m[1])}
	{
	}

	constexpr explicit Mat(Mat<4, 4, T> const& m)
	    : value_{column_type(m[0]), column_type(m[1])}
	{
	}

	/**************************************************************************************
	|                                                                                     |
	|                                 Assignment operator                                 |
	|                                                                                     |
	**************************************************************************************/

	constexpr Mat& operator=(Mat const&) noexcept = default;

	template <class U>
	constexpr Mat& operator=(Mat<2, 2, U> const& m) noexcept
	{
		value_[0] = m[0];
		value_[1] = m[1];
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
		return {-value_[0], -value_[1]};
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
		return *this;
	}

	template <class U>
	constexpr Mat& operator+=(Mat<2, 2, U> const& m)
	{
		value_[0] += m[0];
		value_[1] += m[1];
		return *this;
	}

	template <class U>
	constexpr Mat& operator-=(U value)
	{
		value_[0] -= value;
		value_[1] -= value;
		return *this;
	}

	template <class U>
	constexpr Mat& operator-=(Mat<2, 2, U> const& m)
	{
		value_[0] -= m[0];
		value_[1] -= m[1];
		return *this;
	}

	template <class U>
	constexpr Mat& operator*=(U value)
	{
		value_[0] *= value;
		value_[1] *= value;
		return *this;
	}

	template <class U>
	constexpr Mat& operator*=(Mat<2, 2, U> const& m)
	{
		return *this = *this * m;
	}

	template <class U>
	constexpr Mat& operator/=(U value)
	{
		value_[0] /= value;
		value_[1] /= value;
		return *this;
	}

	template <class U>
	constexpr Mat& operator/=(Mat<2, 2, U> const& m)
	{
		return *this *= inverse(m);
	}

	/**************************************************************************************
	|                                                                                     |
	|                                      Capacity                                       |
	|                                                                                     |
	**************************************************************************************/

	[[nodiscard]] static constexpr size_type cols() noexcept { return 2; }

	[[nodiscard]] static constexpr size_type rows() noexcept { return 2; }

	[[nodiscard]] static constexpr size_type size() noexcept { return cols() * rows(); }

	/**************************************************************************************
	|                                                                                     |
	|                                     Operations                                      |
	|                                                                                     |
	**************************************************************************************/

	void swap(Mat& other) noexcept { value_.swap(other.value_); }

 private:
	std::array<column_type, 2> value_;
};

/**************************************************************************************
|                                                                                     |
|                                  Binary operators                                   |
|                                                                                     |
**************************************************************************************/

template <class T>
constexpr Mat<2, 2, T> operator+(Mat<2, 2, T> const& m, T value)
{
	return {m[0] + value, m[1] + value};
}

template <class T>
constexpr Mat<2, 2, T> operator+(T value, Mat<2, 2, T> const& m)
{
	return {m[0] + value, m[1] + value};
}

template <class T>
constexpr Mat<2, 2, T> operator+(Mat<2, 2, T> const& m1, Mat<2, 2, T> const& m2)
{
	return {m1[0] + m2[0], m1[1] + m2[1]};
}

template <class T>
constexpr Mat<2, 2, T> operator-(Mat<2, 2, T> const& m, T value)
{
	return {m[0] - value, m[1] - value};
}

template <class T>
constexpr Mat<2, 2, T> operator-(T value, Mat<2, 2, T> const& m)
{
	return {value - m[0], value - m[1]};
}

template <class T>
constexpr Mat<2, 2, T> operator-(Mat<2, 2, T> const& m1, Mat<2, 2, T> const& m2)
{
	return {m1[0] - m2[0], m1[1] - m2[1]};
}

template <class T>
constexpr Mat<2, 2, T> operator*(Mat<2, 2, T> const& m, T value)
{
	return {m[0] * value, m[1] * value};
}

template <class T>
constexpr Mat<2, 2, T> operator*(T value, Mat<2, 2, T> const& m)
{
	return {m[0] * value, m[1] * value};
}

template <class T>
constexpr typename Mat<2, 2, T>::column_type operator*(
    Mat<2, 2, T> const& m, typename Mat<2, 2, T>::row_type const& v)
{
	return {m[0][0] * v.x + m[1][0] * v.y, m[0][1] * v.x + m[1][1] * v.y};
}

template <class T>
constexpr typename Mat<2, 2, T>::row_type operator*(
    typename Mat<2, 2, T>::column_type const& v, Mat<2, 2, T> const& m)
{
	return {v.x * m[0][0] + v.y * m[0][1], v.x * m[1][0] + v.y * m[1][1]};
}

template <class T>
constexpr Mat<2, 2, T> operator*(Mat<2, 2, T> const& m1, Mat<2, 2, T> const& m2)
{
	return {m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1],
	        m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1],
	        m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1],
	        m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1]};
}

template <class T>
constexpr Mat<2, 2, T> operator/(Mat<2, 2, T> const& m, T value)
{
	return {m[0] / value, m[1] / value};
}

template <class T>
constexpr Mat<2, 2, T> operator/(T value, Mat<2, 2, T> const& m)
{
	return {value / m[0], value / m[1]};
}

template <class T>
constexpr typename Mat<2, 2, T>::column_type operator/(
    Mat<2, 2, T> const& m, typename Mat<2, 2, T>::row_type const& v)
{
	return inverse(m) * v;
}

template <class T>
constexpr typename Mat<2, 2, T>::row_type operator/(
    typename Mat<2, 2, T>::column_type const& v, Mat<2, 2, T> const& m)
{
	return v * inverse(m);
}

template <class T>
constexpr Mat<2, 2, T> operator/(Mat<2, 2, T> m1, Mat<2, 2, T> const& m2)
{
	return m1 /= m2;
}

/**************************************************************************************
|                                                                                     |
|                                       Compare                                       |
|                                                                                     |
**************************************************************************************/

template <class T>
[[nodiscard]] constexpr bool operator==(Mat<2, 2, T> const& lhs,
                                        Mat<2, 2, T> const& rhs) noexcept
{
	return lhs[0] == rhs[0] && lhs[1] == rhs[1];
}

template <class T>
[[nodiscard]] constexpr bool operator!=(Mat<2, 2, T> const& lhs,
                                        Mat<2, 2, T> const& rhs) noexcept
{
	return !(lhs == rhs);
}

}  // namespace ufo

#endif  // UFO_MATH_MAT2x2_HPP