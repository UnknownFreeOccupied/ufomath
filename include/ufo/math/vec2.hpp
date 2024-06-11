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

#ifndef UFO_MATH_VEC2_HPP
#define UFO_MATH_VEC2_HPP

// UFO
#include <ufo/math/detail/vec.hpp>
#include <ufo/math/detail/vec_fun.hpp>

// STL
#include <cassert>
#include <cmath>
#include <cstddef>
#include <utility>

namespace ufo
{
template <class T>
struct Vec<2, T> {
	using value_type = T;
	using size_type  = std::size_t;

	T x{};
	T y{};

	/**************************************************************************************
	|                                                                                     |
	|                                    Constructors                                     |
	|                                                                                     |
	**************************************************************************************/

	constexpr Vec() noexcept            = default;
	constexpr Vec(Vec const &) noexcept = default;

	constexpr explicit Vec(T value) noexcept : x(value), y(value) {}

	constexpr Vec(T x, T y) noexcept : x(x), y(y) {}

	template <class U>
	constexpr explicit Vec(Vec<1, U> v) noexcept
	    : x(static_cast<T>(v.x)), y(static_cast<T>(v.x))
	{
	}

	template <class X, class Y>
	constexpr Vec(X x, Y y) noexcept : x(static_cast<T>(x)), y(static_cast<T>(y))
	{
	}

	template <class X, class Y>
	constexpr Vec(Vec<1, X> x, Y y) noexcept : x(static_cast<T>(x.x)), y(static_cast<T>(y))
	{
	}

	template <class X, class Y>
	constexpr Vec(X x, Vec<1, Y> y) noexcept : x(static_cast<T>(x)), y(static_cast<T>(y.x))
	{
	}

	template <class X, class Y>
	constexpr Vec(Vec<1, X> x, Vec<1, Y> y) noexcept
	    : x(static_cast<T>(x.x)), y(static_cast<T>(y.x))
	{
	}

	template <class U>
	constexpr explicit Vec(Vec<2, U> v) noexcept
	    : x(static_cast<T>(v.x)), y(static_cast<T>(v.y))
	{
	}

	template <class U>
	constexpr explicit Vec(Vec<3, U> v) noexcept
	    : x(static_cast<T>(v.x)), y(static_cast<T>(v.y))
	{
	}

	template <class U>
	constexpr explicit Vec(Vec<4, U> v) noexcept
	    : x(static_cast<T>(v.x)), y(static_cast<T>(v.y))
	{
	}

	/**************************************************************************************
	|                                                                                     |
	|                                 Assignment operator                                 |
	|                                                                                     |
	**************************************************************************************/

	constexpr Vec &operator=(Vec const &) noexcept = default;

	template <class U>
	constexpr Vec &operator=(Vec<2, U> rhs) noexcept
	{
		x = static_cast<T>(rhs.x);
		y = static_cast<T>(rhs.y);
		return *this;
	}

	/**************************************************************************************
	|                                                                                     |
	|                                   Element access                                    |
	|                                                                                     |
	**************************************************************************************/

	[[nodiscard]] constexpr T &operator[](size_type pos) noexcept
	{
		assert(size() > pos);
		return (&x)[pos];
	}

	[[nodiscard]] constexpr T const &operator[](size_type pos) const noexcept
	{
		assert(size() > pos);
		return (&x)[pos];
	}

	/**************************************************************************************
	|                                                                                     |
	|                              Unary arithmetic operator                              |
	|                                                                                     |
	**************************************************************************************/

	constexpr Vec operator+() const noexcept { return *this; }

	constexpr Vec operator-() const noexcept { return {-x, -y}; }

	constexpr Vec operator~() const noexcept { return {~x, ~y}; }

	/**************************************************************************************
	|                                                                                     |
	|                            Compound assignment operator                             |
	|                                                                                     |
	**************************************************************************************/

	template <class U>
	constexpr Vec &operator+=(U value) noexcept
	{
		x += static_cast<T>(value);
		y += static_cast<T>(value);
		return *this;
	}

	template <class U>
	constexpr Vec &operator+=(Vec<1, U> v) noexcept
	{
		x += static_cast<T>(v.x);
		y += static_cast<T>(v.x);
		return *this;
	}

	template <class U>
	constexpr Vec &operator+=(Vec<2, U> v) noexcept
	{
		x += static_cast<T>(v.x);
		y += static_cast<T>(v.y);
		return *this;
	}

	template <class U>
	constexpr Vec &operator-=(U value) noexcept
	{
		x -= static_cast<T>(value);
		y -= static_cast<T>(value);
		return *this;
	}

	template <class U>
	constexpr Vec &operator-=(Vec<1, U> v) noexcept
	{
		x -= static_cast<T>(v.x);
		y -= static_cast<T>(v.x);
		return *this;
	}

	template <class U>
	constexpr Vec &operator-=(Vec<2, U> v) noexcept
	{
		x -= static_cast<T>(v.x);
		y -= static_cast<T>(v.y);
		return *this;
	}

	template <class U>
	constexpr Vec &operator*=(U value) noexcept
	{
		x *= static_cast<T>(value);
		y *= static_cast<T>(value);
		return *this;
	}

	template <class U>
	constexpr Vec &operator*=(Vec<1, U> v) noexcept
	{
		x *= static_cast<T>(v.x);
		y *= static_cast<T>(v.x);
		return *this;
	}

	template <class U>
	constexpr Vec &operator*=(Vec<2, U> v) noexcept
	{
		x *= static_cast<T>(v.x);
		y *= static_cast<T>(v.y);
		return *this;
	}

	template <class U>
	constexpr Vec &operator/=(U value) noexcept
	{
		x /= static_cast<T>(value);
		y /= static_cast<T>(value);
		return *this;
	}

	template <class U>
	constexpr Vec &operator/=(Vec<1, U> v) noexcept
	{
		x /= static_cast<T>(v.x);
		y /= static_cast<T>(v.x);
		return *this;
	}

	template <class U>
	constexpr Vec &operator/=(Vec<2, U> v) noexcept
	{
		x /= static_cast<T>(v.x);
		y /= static_cast<T>(v.y);
		return *this;
	}

	template <class U>
	constexpr Vec &operator%=(U value) noexcept
	{
		x %= static_cast<T>(value);
		y %= static_cast<T>(value);
		return *this;
	}

	template <class U>
	constexpr Vec &operator%=(Vec<1, U> v) noexcept
	{
		x %= static_cast<T>(v.x);
		y %= static_cast<T>(v.x);
		return *this;
	}

	template <class U>
	constexpr Vec &operator%=(Vec<2, U> v) noexcept
	{
		x %= static_cast<T>(v.x);
		y %= static_cast<T>(v.y);
		return *this;
	}

	template <class U>
	constexpr Vec &operator&=(U value) noexcept
	{
		x &= static_cast<T>(value);
		y &= static_cast<T>(value);
		return *this;
	}

	template <class U>
	constexpr Vec &operator&=(Vec<1, U> v) noexcept
	{
		x &= static_cast<T>(v.x);
		y &= static_cast<T>(v.x);
		return *this;
	}

	template <class U>
	constexpr Vec &operator&=(Vec<2, U> v) noexcept
	{
		x &= static_cast<T>(v.x);
		y &= static_cast<T>(v.y);
		return *this;
	}

	template <class U>
	constexpr Vec &operator|=(U value) noexcept
	{
		x |= static_cast<T>(value);
		y |= static_cast<T>(value);
		return *this;
	}

	template <class U>
	constexpr Vec &operator|=(Vec<1, U> v) noexcept
	{
		x |= static_cast<T>(v.x);
		y |= static_cast<T>(v.x);
		return *this;
	}

	template <class U>
	constexpr Vec &operator|=(Vec<2, U> v) noexcept
	{
		x |= static_cast<T>(v.x);
		y |= static_cast<T>(v.y);
		return *this;
	}

	template <class U>
	constexpr Vec &operator^=(U value) noexcept
	{
		x ^= static_cast<T>(value);
		y ^= static_cast<T>(value);
		return *this;
	}

	template <class U>
	constexpr Vec &operator^=(Vec<1, U> v) noexcept
	{
		x ^= static_cast<T>(v.x);
		y ^= static_cast<T>(v.x);
		return *this;
	}

	template <class U>
	constexpr Vec &operator^=(Vec<2, U> v) noexcept
	{
		x ^= static_cast<T>(v.x);
		y ^= static_cast<T>(v.y);
		return *this;
	}

	template <class U>
	constexpr Vec &operator<<=(U value) noexcept
	{
		x <<= static_cast<T>(value);
		y <<= static_cast<T>(value);
		return *this;
	}

	template <class U>
	constexpr Vec &operator<<=(Vec<1, U> v) noexcept
	{
		x <<= static_cast<T>(v.x);
		y <<= static_cast<T>(v.x);
		return *this;
	}

	template <class U>
	constexpr Vec &operator<<=(Vec<2, U> v) noexcept
	{
		x <<= static_cast<T>(v.x);
		y <<= static_cast<T>(v.y);
		return *this;
	}

	template <class U>
	constexpr Vec &operator>>=(U value) noexcept
	{
		x >>= static_cast<T>(value);
		y >>= static_cast<T>(value);
		return *this;
	}

	template <class U>
	constexpr Vec &operator>>=(Vec<1, U> v) noexcept
	{
		x >>= static_cast<T>(v.x);
		y >>= static_cast<T>(v.x);
		return *this;
	}

	template <class U>
	constexpr Vec &operator>>=(Vec<2, U> v) noexcept
	{
		x >>= static_cast<T>(v.x);
		y >>= static_cast<T>(v.y);
		return *this;
	}

	/**************************************************************************************
	|                                                                                     |
	|                                      Capacity                                       |
	|                                                                                     |
	**************************************************************************************/

	[[nodiscard]] static constexpr size_type size() noexcept { return 2; }

	/**************************************************************************************
	|                                                                                     |
	|                                     Operations                                      |
	|                                                                                     |
	**************************************************************************************/

	void swap(Vec &other) noexcept
	{
		std::swap(x, other.x);
		std::swap(y, other.y);
	}
};

/**************************************************************************************
|                                                                                     |
|                                  Binary operators                                   |
|                                                                                     |
**************************************************************************************/

template <class T>
[[nodiscard]] constexpr Vec<2, T> operator+(Vec<2, T> v, T value) noexcept
{
	return {v.x + value, v.y + value};
}

template <class T>
[[nodiscard]] constexpr Vec<2, T> operator+(Vec<2, T> v1, Vec<1, T> v2) noexcept
{
	return {v1.x + v2.x, v1.y + v2.x};
}

template <class T>
[[nodiscard]] constexpr Vec<2, T> operator+(T value, Vec<2, T> v) noexcept
{
	return {value + v.x, value + v.y};
}

template <class T>
[[nodiscard]] constexpr Vec<2, T> operator+(Vec<1, T> v1, Vec<2, T> v2) noexcept
{
	return {v1.x + v2.x, v1.x + v2.y};
}

template <class T>
[[nodiscard]] constexpr Vec<2, T> operator+(Vec<2, T> v1, Vec<2, T> v2) noexcept
{
	return {v1.x + v2.x, v1.y + v2.y};
}

template <class T>
[[nodiscard]] constexpr Vec<2, T> operator-(Vec<2, T> v, T value) noexcept
{
	return {v.x - value, v.y - value};
}

template <class T>
[[nodiscard]] constexpr Vec<2, T> operator-(Vec<2, T> v1, Vec<1, T> v2) noexcept
{
	return {v1.x - v2.x, v1.y - v2.x};
}

template <class T>
[[nodiscard]] constexpr Vec<2, T> operator-(T value, Vec<2, T> v) noexcept
{
	return {value - v.x, value - v.y};
}

template <class T>
[[nodiscard]] constexpr Vec<2, T> operator-(Vec<1, T> v1, Vec<2, T> v2) noexcept
{
	return {v1.x - v2.x, v1.x - v2.y};
}

template <class T>
[[nodiscard]] constexpr Vec<2, T> operator-(Vec<2, T> v1, Vec<2, T> v2) noexcept
{
	return {v1.x - v2.x, v1.y - v2.y};
}

template <class T>
[[nodiscard]] constexpr Vec<2, T> operator*(Vec<2, T> v, T value) noexcept
{
	return {v.x * value, v.y * value};
}

template <class T>
[[nodiscard]] constexpr Vec<2, T> operator*(Vec<2, T> v1, Vec<1, T> v2) noexcept
{
	return {v1.x * v2.x, v1.y * v2.x};
}

template <class T>
[[nodiscard]] constexpr Vec<2, T> operator*(T value, Vec<2, T> v) noexcept
{
	return {value * v.x, value * v.y};
}

template <class T>
[[nodiscard]] constexpr Vec<2, T> operator*(Vec<1, T> v1, Vec<2, T> v2) noexcept
{
	return {v1.x * v2.x, v1.x * v2.y};
}

template <class T>
[[nodiscard]] constexpr Vec<2, T> operator*(Vec<2, T> v1, Vec<2, T> v2) noexcept
{
	return {v1.x * v2.x, v1.y * v2.y};
}

template <class T>
[[nodiscard]] constexpr Vec<2, T> operator/(Vec<2, T> v, T value) noexcept
{
	return {v.x / value, v.y / value};
}

template <class T>
[[nodiscard]] constexpr Vec<2, T> operator/(Vec<2, T> v1, Vec<1, T> v2) noexcept
{
	return {v1.x / v2.x, v1.y / v2.x};
}

template <class T>
[[nodiscard]] constexpr Vec<2, T> operator/(T value, Vec<2, T> v) noexcept
{
	return {value / v.x, value / v.y};
}

template <class T>
[[nodiscard]] constexpr Vec<2, T> operator/(Vec<1, T> v1, Vec<2, T> v2) noexcept
{
	return {v1.x / v2.x, v1.x / v2.y};
}

template <class T>
[[nodiscard]] constexpr Vec<2, T> operator/(Vec<2, T> v1, Vec<2, T> v2) noexcept
{
	return {v1.x / v2.x, v1.y / v2.y};
}

template <class T>
[[nodiscard]] constexpr Vec<2, T> operator%(Vec<2, T> v, T value) noexcept
{
	return {v.x % value, v.y % value};
}

template <class T>
[[nodiscard]] constexpr Vec<2, T> operator%(Vec<2, T> v1, Vec<1, T> v2) noexcept
{
	return {v1.x % v2.x, v1.y % v2.x};
}

template <class T>
[[nodiscard]] constexpr Vec<2, T> operator%(T value, Vec<2, T> v) noexcept
{
	return {value % v.x, value % v.y};
}

template <class T>
[[nodiscard]] constexpr Vec<2, T> operator%(Vec<1, T> v1, Vec<2, T> v2) noexcept
{
	return {v1.x % v2.x, v1.x % v2.y};
}

template <class T>
[[nodiscard]] constexpr Vec<2, T> operator%(Vec<2, T> v1, Vec<2, T> v2) noexcept
{
	return {v1.x % v2.x, v1.y % v2.y};
}

template <class T>
[[nodiscard]] constexpr Vec<2, T> operator&(Vec<2, T> v, T value) noexcept
{
	return {v.x & value, v.y & value};
}

template <class T>
[[nodiscard]] constexpr Vec<2, T> operator&(Vec<2, T> v1, Vec<1, T> v2) noexcept
{
	return {v1.x & v2.x, v1.y & v2.x};
}

template <class T>
[[nodiscard]] constexpr Vec<2, T> operator&(T value, Vec<2, T> v) noexcept
{
	return {value & v.x, value & v.y};
}

template <class T>
[[nodiscard]] constexpr Vec<2, T> operator&(Vec<1, T> v1, Vec<2, T> v2) noexcept
{
	return {v1.x & v2.x, v1.x & v2.y};
}

template <class T>
[[nodiscard]] constexpr Vec<2, T> operator&(Vec<2, T> v1, Vec<2, T> v2) noexcept
{
	return {v1.x & v2.x, v1.y & v2.y};
}

template <class T>
[[nodiscard]] constexpr Vec<2, T> operator|(Vec<2, T> v, T value) noexcept
{
	return {v.x | value, v.y | value};
}

template <class T>
[[nodiscard]] constexpr Vec<2, T> operator|(Vec<2, T> v1, Vec<1, T> v2) noexcept
{
	return {v1.x | v2.x, v1.y | v2.x};
}

template <class T>
[[nodiscard]] constexpr Vec<2, T> operator|(T value, Vec<2, T> v) noexcept
{
	return {value | v.x, value | v.y};
}

template <class T>
[[nodiscard]] constexpr Vec<2, T> operator|(Vec<1, T> v1, Vec<2, T> v2) noexcept
{
	return {v1.x | v2.x, v1.x | v2.y};
}

template <class T>
[[nodiscard]] constexpr Vec<2, T> operator|(Vec<2, T> v1, Vec<2, T> v2) noexcept
{
	return {v1.x | v2.x, v1.y | v2.y};
}

template <class T>
[[nodiscard]] constexpr Vec<2, T> operator^(Vec<2, T> v, T value) noexcept
{
	return {v.x ^ value, v.y ^ value};
}

template <class T>
[[nodiscard]] constexpr Vec<2, T> operator^(Vec<2, T> v1, Vec<1, T> v2) noexcept
{
	return {v1.x ^ v2.x, v1.y ^ v2.x};
}

template <class T>
[[nodiscard]] constexpr Vec<2, T> operator^(T value, Vec<2, T> v) noexcept
{
	return {value ^ v.x, value ^ v.y};
}

template <class T>
[[nodiscard]] constexpr Vec<2, T> operator^(Vec<1, T> v1, Vec<2, T> v2) noexcept
{
	return {v1.x ^ v2.x, v1.x ^ v2.y};
}

template <class T>
[[nodiscard]] constexpr Vec<2, T> operator^(Vec<2, T> v1, Vec<2, T> v2) noexcept
{
	return {v1.x ^ v2.x, v1.y ^ v2.y};
}

template <class T>
[[nodiscard]] constexpr Vec<2, T> operator<<(Vec<2, T> v, T value) noexcept
{
	return {v.x << value, v.y << value};
}

template <class T>
[[nodiscard]] constexpr Vec<2, T> operator<<(Vec<2, T> v1, Vec<1, T> v2) noexcept
{
	return {v1.x << v2.x, v1.y << v2.x};
}

template <class T>
[[nodiscard]] constexpr Vec<2, T> operator<<(T value, Vec<2, T> v) noexcept
{
	return {value << v.x, value << v.y};
}

template <class T>
[[nodiscard]] constexpr Vec<2, T> operator<<(Vec<1, T> v1, Vec<2, T> v2) noexcept
{
	return {v1.x << v2.x, v1.x << v2.y};
}

template <class T>
[[nodiscard]] constexpr Vec<2, T> operator<<(Vec<2, T> v1, Vec<2, T> v2) noexcept
{
	return {v1.x << v2.x, v1.y << v2.y};
}

template <class T>
[[nodiscard]] constexpr Vec<2, T> operator>>(Vec<2, T> v, T value) noexcept
{
	return {v.x >> value, v.y >> value};
}

template <class T>
[[nodiscard]] constexpr Vec<2, T> operator>>(Vec<2, T> v1, Vec<1, T> v2) noexcept
{
	return {v1.x >> v2.x, v1.y >> v2.x};
}

template <class T>
[[nodiscard]] constexpr Vec<2, T> operator>>(T value, Vec<2, T> v) noexcept
{
	return {value >> v.x, value >> v.y};
}

template <class T>
[[nodiscard]] constexpr Vec<2, T> operator>>(Vec<1, T> v1, Vec<2, T> v2) noexcept
{
	return {v1.x >> v2.x, v1.x >> v2.y};
}

template <class T>
[[nodiscard]] constexpr Vec<2, T> operator>>(Vec<2, T> v1, Vec<2, T> v2) noexcept
{
	return {v1.x >> v2.x, v1.y >> v2.y};
}

[[nodiscard]] constexpr Vec<2, bool> operator&&(Vec<2, bool> v1, Vec<2, bool> v2)
{
	return {v1.x && v2.x, v1.y && v2.y};
}

[[nodiscard]] constexpr Vec<2, bool> operator||(Vec<2, bool> v1, Vec<2, bool> v2)
{
	return {v1.x || v2.x, v1.y || v2.y};
}

/**************************************************************************************
|                                                                                     |
|                                       Compare                                       |
|                                                                                     |
**************************************************************************************/

template <class T>
[[nodiscard]] constexpr Vec<2, bool> operator==(Vec<2, T> lhs, Vec<2, T> rhs) noexcept
{
	return {lhs.x == rhs.x, lhs.y == rhs.y};
}

template <class T>
[[nodiscard]] constexpr Vec<2, bool> operator!=(Vec<2, T> lhs, Vec<2, T> rhs) noexcept
{
	return {lhs.x != rhs.x, lhs.y != rhs.y};
}

template <class T>
[[nodiscard]] constexpr Vec<2, bool> operator<(Vec<2, T> lhs, Vec<2, T> rhs) noexcept
{
	return {lhs.x < rhs.x, lhs.y < rhs.y};
}

template <class T>
[[nodiscard]] constexpr Vec<2, bool> operator<=(Vec<2, T> lhs, Vec<2, T> rhs) noexcept
{
	return {lhs.x <= rhs.x, lhs.y <= rhs.y};
}

template <class T>
[[nodiscard]] constexpr Vec<2, bool> operator>(Vec<2, T> lhs, Vec<2, T> rhs) noexcept
{
	return {lhs.x > rhs.x, lhs.y > rhs.y};
}

template <class T>
[[nodiscard]] constexpr Vec<2, bool> operator>=(Vec<2, T> lhs, Vec<2, T> rhs) noexcept
{
	return {lhs.x >= rhs.x, lhs.y >= rhs.y};
}
}  // namespace ufo

#endif  // UFO_MATH_VEC2_HPP