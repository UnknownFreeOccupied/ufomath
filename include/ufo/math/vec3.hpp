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

#ifndef UFO_MATH_VEC3_HPP
#define UFO_MATH_VEC3_HPP

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
template <typename T>
struct Vec<3, T> {
	using value_type = T;
	using size_type  = std::size_t;

	T x{};
	T y{};
	T z{};

	/**************************************************************************************
	|                                                                                     |
	|                                    Constructors                                     |
	|                                                                                     |
	**************************************************************************************/

	constexpr Vec() noexcept            = default;
	constexpr Vec(Vec const &) noexcept = default;

	constexpr explicit Vec(T value) noexcept : x(value), y(value), z(value) {}

	constexpr Vec(T x, T y, T z) noexcept : x(x), y(y), z(z) {}

	template <class U>
	constexpr explicit Vec(Vec<1, U> v) noexcept
	    : x(static_cast<T>(v.x)), y(static_cast<T>(v.x)), z(static_cast<T>(v.x))
	{
	}

	template <class X, class Y, class Z>
	constexpr Vec(X x, Y y, Z z) noexcept
	    : x(static_cast<T>(x)), y(static_cast<T>(y)), z(static_cast<T>(z))
	{
	}

	template <class X, class Y, class Z>
	constexpr Vec(Vec<1, X> x, Y y, Z z) noexcept
	    : x(static_cast<T>(x.x)), y(static_cast<T>(y)), z(static_cast<T>(z))
	{
	}

	template <class X, class Y, class Z>
	constexpr Vec(X x, Vec<1, Y> y, Z z) noexcept
	    : x(static_cast<T>(x)), y(static_cast<T>(y.x)), z(static_cast<T>(z))
	{
	}

	template <class X, class Y, class Z>
	constexpr Vec(X x, Y y, Vec<1, Z> z) noexcept
	    : x(static_cast<T>(x)), y(static_cast<T>(y)), z(static_cast<T>(z.x))
	{
	}

	template <class X, class Y, class Z>
	constexpr Vec(Vec<1, X> x, Vec<1, Y> y, Z z) noexcept
	    : x(static_cast<T>(x.x)), y(static_cast<T>(y.x)), z(static_cast<T>(z))
	{
	}

	template <class X, class Y, class Z>
	constexpr Vec(Vec<1, X> x, Y y, Vec<1, Z> z) noexcept
	    : x(static_cast<T>(x.x)), y(static_cast<T>(y)), z(static_cast<T>(z.x))
	{
	}

	template <class X, class Y, class Z>
	constexpr Vec(X x, Vec<1, Y> y, Vec<1, Z> z) noexcept
	    : x(static_cast<T>(x)), y(static_cast<T>(y.x)), z(static_cast<T>(z.x))
	{
	}

	template <class X, class Y, class Z>
	constexpr Vec(Vec<1, X> x, Vec<1, Y> y, Vec<1, Z> z) noexcept
	    : x(static_cast<T>(x.x)), y(static_cast<T>(y.x)), z(static_cast<T>(z.x))
	{
	}

	template <class XY, class Z>
	constexpr Vec(Vec<2, XY> xy, Z z) noexcept
	    : x(static_cast<T>(xy.x)), y(static_cast<T>(xy.y)), z(static_cast<T>(z))
	{
	}

	template <class XY, class Z>
	constexpr Vec(Vec<2, XY> xy, Vec<1, Z> z) noexcept
	    : x(static_cast<T>(xy.x)), y(static_cast<T>(xy.y)), z(static_cast<T>(z.x))
	{
	}

	template <class X, class YZ>
	constexpr Vec(X x, Vec<2, YZ> yz) noexcept
	    : x(static_cast<T>(x)), y(static_cast<T>(yz.x)), z(static_cast<T>(yz.y))
	{
	}

	template <class X, class YZ>
	constexpr Vec(Vec<1, X> x, Vec<2, YZ> yz) noexcept
	    : x(static_cast<T>(x.x)), y(static_cast<T>(yz.x)), z(static_cast<T>(yz.y))
	{
	}

	template <class U>
	constexpr explicit Vec(Vec<3, U> v) noexcept
	    : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)), z(static_cast<T>(v.z))
	{
	}

	template <class U>
	constexpr explicit Vec(Vec<4, U> v) noexcept
	    : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)), z(static_cast<T>(v.z))
	{
	}

	/**************************************************************************************
	|                                                                                     |
	|                                 Assignment operator                                 |
	|                                                                                     |
	**************************************************************************************/

	constexpr Vec &operator=(Vec const &) noexcept = default;

	template <class U>
	constexpr Vec &operator=(Vec<3, U> rhs) noexcept
	{
		x = static_cast<T>(rhs.x);
		y = static_cast<T>(rhs.y);
		z = static_cast<T>(rhs.z);
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

	constexpr Vec operator-() const noexcept { return {-x, -y, -z}; }

	constexpr Vec operator~() const noexcept { return {~x, ~y, ~z}; }

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
		z += static_cast<T>(value);
		return *this;
	}

	template <class U>
	constexpr Vec &operator+=(Vec<1, U> v) noexcept
	{
		x += static_cast<T>(v.x);
		y += static_cast<T>(v.x);
		z += static_cast<T>(v.x);
		return *this;
	}

	template <class U>
	constexpr Vec &operator+=(Vec<3, U> v) noexcept
	{
		x += static_cast<T>(v.x);
		y += static_cast<T>(v.y);
		z += static_cast<T>(v.z);
		return *this;
	}

	template <class U>
	constexpr Vec &operator-=(U value) noexcept
	{
		x -= static_cast<T>(value);
		y -= static_cast<T>(value);
		z -= static_cast<T>(value);
		return *this;
	}

	template <class U>
	constexpr Vec &operator-=(Vec<1, U> v) noexcept
	{
		x -= static_cast<T>(v.x);
		y -= static_cast<T>(v.x);
		z -= static_cast<T>(v.x);
		return *this;
	}

	template <class U>
	constexpr Vec &operator-=(Vec<3, U> v) noexcept
	{
		x -= static_cast<T>(v.x);
		y -= static_cast<T>(v.y);
		z -= static_cast<T>(v.z);
		return *this;
	}

	template <class U>
	constexpr Vec &operator*=(U value) noexcept
	{
		x *= static_cast<T>(value);
		y *= static_cast<T>(value);
		z *= static_cast<T>(value);
		return *this;
	}

	template <class U>
	constexpr Vec &operator*=(Vec<1, U> v) noexcept
	{
		x *= static_cast<T>(v.x);
		y *= static_cast<T>(v.x);
		z *= static_cast<T>(v.x);
		return *this;
	}

	template <class U>
	constexpr Vec &operator*=(Vec<3, U> v) noexcept
	{
		x *= static_cast<T>(v.x);
		y *= static_cast<T>(v.y);
		z *= static_cast<T>(v.z);
		return *this;
	}

	template <class U>
	constexpr Vec &operator/=(U value) noexcept
	{
		x /= static_cast<T>(value);
		y /= static_cast<T>(value);
		z /= static_cast<T>(value);
		return *this;
	}

	template <class U>
	constexpr Vec &operator/=(Vec<1, U> v) noexcept
	{
		x /= static_cast<T>(v.x);
		y /= static_cast<T>(v.x);
		z /= static_cast<T>(v.x);
		return *this;
	}

	template <class U>
	constexpr Vec &operator/=(Vec<3, U> v) noexcept
	{
		x /= static_cast<T>(v.x);
		y /= static_cast<T>(v.y);
		z /= static_cast<T>(v.z);
		return *this;
	}

	template <class U>
	constexpr Vec &operator%=(U value) noexcept
	{
		x %= static_cast<T>(value);
		y %= static_cast<T>(value);
		z %= static_cast<T>(value);
		return *this;
	}

	template <class U>
	constexpr Vec &operator%=(Vec<1, U> v) noexcept
	{
		x %= static_cast<T>(v.x);
		y %= static_cast<T>(v.x);
		z %= static_cast<T>(v.x);
		return *this;
	}

	template <class U>
	constexpr Vec &operator%=(Vec<3, U> v) noexcept
	{
		x %= static_cast<T>(v.x);
		y %= static_cast<T>(v.y);
		z %= static_cast<T>(v.z);
		return *this;
	}

	template <class U>
	constexpr Vec &operator&=(U value) noexcept
	{
		x &= static_cast<T>(value);
		y &= static_cast<T>(value);
		z &= static_cast<T>(value);
		return *this;
	}

	template <class U>
	constexpr Vec &operator&=(Vec<1, U> v) noexcept
	{
		x &= static_cast<T>(v.x);
		y &= static_cast<T>(v.x);
		z &= static_cast<T>(v.x);
		return *this;
	}

	template <class U>
	constexpr Vec &operator&=(Vec<3, U> v) noexcept
	{
		x &= static_cast<T>(v.x);
		y &= static_cast<T>(v.y);
		z &= static_cast<T>(v.z);
		return *this;
	}

	template <class U>
	constexpr Vec &operator|=(U value) noexcept
	{
		x |= static_cast<T>(value);
		y |= static_cast<T>(value);
		z |= static_cast<T>(value);
		return *this;
	}

	template <class U>
	constexpr Vec &operator|=(Vec<1, U> v) noexcept
	{
		x |= static_cast<T>(v.x);
		y |= static_cast<T>(v.x);
		z |= static_cast<T>(v.x);
		return *this;
	}

	template <class U>
	constexpr Vec &operator|=(Vec<3, U> v) noexcept
	{
		x |= static_cast<T>(v.x);
		y |= static_cast<T>(v.y);
		z |= static_cast<T>(v.z);
		return *this;
	}

	template <class U>
	constexpr Vec &operator^=(U value) noexcept
	{
		x ^= static_cast<T>(value);
		y ^= static_cast<T>(value);
		z ^= static_cast<T>(value);
		return *this;
	}

	template <class U>
	constexpr Vec &operator^=(Vec<1, U> v) noexcept
	{
		x ^= static_cast<T>(v.x);
		y ^= static_cast<T>(v.x);
		z ^= static_cast<T>(v.x);
		return *this;
	}

	template <class U>
	constexpr Vec &operator^=(Vec<3, U> v) noexcept
	{
		x ^= static_cast<T>(v.x);
		y ^= static_cast<T>(v.y);
		z ^= static_cast<T>(v.z);
		return *this;
	}

	template <class U>
	constexpr Vec &operator<<=(U value) noexcept
	{
		x <<= static_cast<T>(value);
		y <<= static_cast<T>(value);
		z <<= static_cast<T>(value);
		return *this;
	}

	template <class U>
	constexpr Vec &operator<<=(Vec<1, U> v) noexcept
	{
		x <<= static_cast<T>(v.x);
		y <<= static_cast<T>(v.x);
		z <<= static_cast<T>(v.x);
		return *this;
	}

	template <class U>
	constexpr Vec &operator<<=(Vec<3, U> v) noexcept
	{
		x <<= static_cast<T>(v.x);
		y <<= static_cast<T>(v.y);
		z <<= static_cast<T>(v.z);
		return *this;
	}

	template <class U>
	constexpr Vec &operator>>=(U value) noexcept
	{
		x >>= static_cast<T>(value);
		y >>= static_cast<T>(value);
		z >>= static_cast<T>(value);
		return *this;
	}

	template <class U>
	constexpr Vec &operator>>=(Vec<1, U> v) noexcept
	{
		x >>= static_cast<T>(v.x);
		y >>= static_cast<T>(v.x);
		z >>= static_cast<T>(v.x);
		return *this;
	}

	template <class U>
	constexpr Vec &operator>>=(Vec<3, U> v) noexcept
	{
		x >>= static_cast<T>(v.x);
		y >>= static_cast<T>(v.y);
		z >>= static_cast<T>(v.z);
		return *this;
	}

	/**************************************************************************************
	|                                                                                     |
	|                                      Capacity                                       |
	|                                                                                     |
	**************************************************************************************/

	[[nodiscard]] static constexpr size_type size() noexcept { return 3; }

	/**************************************************************************************
	|                                                                                     |
	|                                     Operations                                      |
	|                                                                                     |
	**************************************************************************************/

	void swap(Vec &other) noexcept
	{
		std::swap(x, other.x);
		std::swap(y, other.y);
		std::swap(z, other.z);
	}
};

/**************************************************************************************
|                                                                                     |
|                                  Binary operators                                   |
|                                                                                     |
**************************************************************************************/

template <class T>
[[nodiscard]] constexpr Vec<3, T> operator+(Vec<3, T> v, T value) noexcept
{
	return {v.x + value, v.y + value, v.z + value};
}

template <class T>
[[nodiscard]] constexpr Vec<3, T> operator+(Vec<3, T> v1, Vec<1, T> v2) noexcept
{
	return {v1.x + v2.x, v1.y + v2.x, v1.z + v2.x};
}

template <class T>
[[nodiscard]] constexpr Vec<3, T> operator+(T value, Vec<3, T> v) noexcept
{
	return {value + v.x, value + v.y, value + v.z};
}

template <class T>
[[nodiscard]] constexpr Vec<3, T> operator+(Vec<1, T> v1, Vec<3, T> v2) noexcept
{
	return {v1.x + v2.x, v1.x + v2.y, v1.x + v2.z};
}

template <class T>
[[nodiscard]] constexpr Vec<3, T> operator+(Vec<3, T> v1, Vec<3, T> v2) noexcept
{
	return {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
}

template <class T>
[[nodiscard]] constexpr Vec<3, T> operator-(Vec<3, T> v, T value) noexcept
{
	return {v.x - value, v.y - value, v.z - value};
}

template <class T>
[[nodiscard]] constexpr Vec<3, T> operator-(Vec<3, T> v1, Vec<1, T> v2) noexcept
{
	return {v1.x - v2.x, v1.y - v2.x, v1.z - v2.x};
}

template <class T>
[[nodiscard]] constexpr Vec<3, T> operator-(T value, Vec<3, T> v) noexcept
{
	return {value - v.x, value - v.y, value - v.z};
}

template <class T>
[[nodiscard]] constexpr Vec<3, T> operator-(Vec<1, T> v1, Vec<3, T> v2) noexcept
{
	return {v1.x - v2.x, v1.x - v2.y, v1.x - v2.z};
}

template <class T>
[[nodiscard]] constexpr Vec<3, T> operator-(Vec<3, T> v1, Vec<3, T> v2) noexcept
{
	return {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
}

template <class T>
[[nodiscard]] constexpr Vec<3, T> operator*(Vec<3, T> v, T value) noexcept
{
	return {v.x * value, v.y * value, v.z * value};
}

template <class T>
[[nodiscard]] constexpr Vec<3, T> operator*(Vec<3, T> v1, Vec<1, T> v2) noexcept
{
	return {v1.x * v2.x, v1.y * v2.x, v1.z * v2.x};
}

template <class T>
[[nodiscard]] constexpr Vec<3, T> operator*(T value, Vec<3, T> v) noexcept
{
	return {value * v.x, value * v.y, value * v.z};
}

template <class T>
[[nodiscard]] constexpr Vec<3, T> operator*(Vec<1, T> v1, Vec<3, T> v2) noexcept
{
	return {v1.x * v2.x, v1.x * v2.y, v1.x * v2.z};
}

template <class T>
[[nodiscard]] constexpr Vec<3, T> operator*(Vec<3, T> v1, Vec<3, T> v2) noexcept
{
	return {v1.x * v2.x, v1.y * v2.y, v1.z * v2.z};
}

template <class T>
[[nodiscard]] constexpr Vec<3, T> operator/(Vec<3, T> v, T value) noexcept
{
	return {v.x / value, v.y / value, v.z / value};
}

template <class T>
[[nodiscard]] constexpr Vec<3, T> operator/(Vec<3, T> v1, Vec<1, T> v2) noexcept
{
	return {v1.x / v2.x, v1.y / v2.x, v1.z / v2.x};
}

template <class T>
[[nodiscard]] constexpr Vec<3, T> operator/(T value, Vec<3, T> v) noexcept
{
	return {value / v.x, value / v.y, value / v.z};
}

template <class T>
[[nodiscard]] constexpr Vec<3, T> operator/(Vec<1, T> v1, Vec<3, T> v2) noexcept
{
	return {v1.x / v2.x, v1.x / v2.y, v1.x / v2.z};
}

template <class T>
[[nodiscard]] constexpr Vec<3, T> operator/(Vec<3, T> v1, Vec<3, T> v2) noexcept
{
	return {v1.x / v2.x, v1.y / v2.y, v1.z / v2.z};
}

template <class T>
[[nodiscard]] constexpr Vec<3, T> operator%(Vec<3, T> v, T value) noexcept
{
	return {v.x % value, v.y % value, v.z % value};
}

template <class T>
[[nodiscard]] constexpr Vec<3, T> operator%(Vec<3, T> v1, Vec<1, T> v2) noexcept
{
	return {v1.x % v2.x, v1.y % v2.x, v1.z % v2.x};
}

template <class T>
[[nodiscard]] constexpr Vec<3, T> operator%(T value, Vec<3, T> v) noexcept
{
	return {value % v.x, value % v.y, value % v.z};
}

template <class T>
[[nodiscard]] constexpr Vec<3, T> operator%(Vec<1, T> v1, Vec<3, T> v2) noexcept
{
	return {v1.x % v2.x, v1.x % v2.y, v1.x % v2.z};
}

template <class T>
[[nodiscard]] constexpr Vec<3, T> operator%(Vec<3, T> v1, Vec<3, T> v2) noexcept
{
	return {v1.x % v2.x, v1.y % v2.y, v1.z % v2.z};
}

template <class T>
[[nodiscard]] constexpr Vec<3, T> operator&(Vec<3, T> v, T value) noexcept
{
	return {v.x & value, v.y & value, v.z & value};
}

template <class T>
[[nodiscard]] constexpr Vec<3, T> operator&(Vec<3, T> v1, Vec<1, T> v2) noexcept
{
	return {v1.x & v2.x, v1.y & v2.x, v1.z & v2.x};
}

template <class T>
[[nodiscard]] constexpr Vec<3, T> operator&(T value, Vec<3, T> v) noexcept
{
	return {value & v.x, value & v.y, value & v.z};
}

template <class T>
[[nodiscard]] constexpr Vec<3, T> operator&(Vec<1, T> v1, Vec<3, T> v2) noexcept
{
	return {v1.x & v2.x, v1.x & v2.y, v1.x & v2.z};
}

template <class T>
[[nodiscard]] constexpr Vec<3, T> operator&(Vec<3, T> v1, Vec<3, T> v2) noexcept
{
	return {v1.x & v2.x, v1.y & v2.y, v1.z & v2.z};
}

template <class T>
[[nodiscard]] constexpr Vec<3, T> operator|(Vec<3, T> v, T value) noexcept
{
	return {v.x | value, v.y | value, v.z | value};
}

template <class T>
[[nodiscard]] constexpr Vec<3, T> operator|(Vec<3, T> v1, Vec<1, T> v2) noexcept
{
	return {v1.x | v2.x, v1.y | v2.x, v1.z | v2.x};
}

template <class T>
[[nodiscard]] constexpr Vec<3, T> operator|(T value, Vec<3, T> v) noexcept
{
	return {value | v.x, value | v.y, value | v.z};
}

template <class T>
[[nodiscard]] constexpr Vec<3, T> operator|(Vec<1, T> v1, Vec<3, T> v2) noexcept
{
	return {v1.x | v2.x, v1.x | v2.y, v1.x | v2.z};
}

template <class T>
[[nodiscard]] constexpr Vec<3, T> operator|(Vec<3, T> v1, Vec<3, T> v2) noexcept
{
	return {v1.x | v2.x, v1.y | v2.y, v1.z | v2.z};
}

template <class T>
[[nodiscard]] constexpr Vec<3, T> operator^(Vec<3, T> v, T value) noexcept
{
	return {v.x ^ value, v.y ^ value, v.z ^ value};
}

template <class T>
[[nodiscard]] constexpr Vec<3, T> operator^(Vec<3, T> v1, Vec<1, T> v2) noexcept
{
	return {v1.x ^ v2.x, v1.y ^ v2.x, v1.z ^ v2.x};
}

template <class T>
[[nodiscard]] constexpr Vec<3, T> operator^(T value, Vec<3, T> v) noexcept
{
	return {value ^ v.x, value ^ v.y, value ^ v.z};
}

template <class T>
[[nodiscard]] constexpr Vec<3, T> operator^(Vec<1, T> v1, Vec<3, T> v2) noexcept
{
	return {v1.x ^ v2.x, v1.x ^ v2.y, v1.x ^ v2.z};
}

template <class T>
[[nodiscard]] constexpr Vec<3, T> operator^(Vec<3, T> v1, Vec<3, T> v2) noexcept
{
	return {v1.x ^ v2.x, v1.y ^ v2.y, v1.z ^ v2.z};
}

template <class T>
[[nodiscard]] constexpr Vec<3, T> operator<<(Vec<3, T> v, T value) noexcept
{
	return {v.x << value, v.y << value, v.z << value};
}

template <class T>
[[nodiscard]] constexpr Vec<3, T> operator<<(Vec<3, T> v1, Vec<1, T> v2) noexcept
{
	return {v1.x << v2.x, v1.y << v2.x, v1.z << v2.x};
}

template <class T>
[[nodiscard]] constexpr Vec<3, T> operator<<(T value, Vec<3, T> v) noexcept
{
	return {value << v.x, value << v.y, value << v.z};
}

template <class T>
[[nodiscard]] constexpr Vec<3, T> operator<<(Vec<1, T> v1, Vec<3, T> v2) noexcept
{
	return {v1.x << v2.x, v1.x << v2.y, v1.x << v2.z};
}

template <class T>
[[nodiscard]] constexpr Vec<3, T> operator<<(Vec<3, T> v1, Vec<3, T> v2) noexcept
{
	return {v1.x << v2.x, v1.y << v2.y, v1.z << v2.z};
}

template <class T>
[[nodiscard]] constexpr Vec<3, T> operator>>(Vec<3, T> v, T value) noexcept
{
	return {v.x >> value, v.y >> value, v.z >> value};
}

template <class T>
[[nodiscard]] constexpr Vec<3, T> operator>>(Vec<3, T> v1, Vec<1, T> v2) noexcept
{
	return {v1.x >> v2.x, v1.y >> v2.x, v1.z >> v2.x};
}

template <class T>
[[nodiscard]] constexpr Vec<3, T> operator>>(T value, Vec<3, T> v) noexcept
{
	return {value >> v.x, value >> v.y, value >> v.z};
}

template <class T>
[[nodiscard]] constexpr Vec<3, T> operator>>(Vec<1, T> v1, Vec<3, T> v2) noexcept
{
	return {v1.x >> v2.x, v1.x >> v2.y, v1.x >> v2.z};
}

template <class T>
[[nodiscard]] constexpr Vec<3, T> operator>>(Vec<3, T> v1, Vec<3, T> v2) noexcept
{
	return {v1.x >> v2.x, v1.y >> v2.y, v1.z >> v2.z};
}

[[nodiscard]] constexpr Vec<3, bool> operator&&(Vec<3, bool> v1, Vec<3, bool> v2)
{
	return {v1.x && v2.x, v1.y && v2.y, v1.z && v2.z};
}

[[nodiscard]] constexpr Vec<3, bool> operator||(Vec<3, bool> v1, Vec<3, bool> v2)
{
	return {v1.x || v2.x, v1.y || v2.y, v1.z || v2.z};
}

/**************************************************************************************
|                                                                                     |
|                                       Compare                                       |
|                                                                                     |
**************************************************************************************/

template <class T>
[[nodiscard]] constexpr bool operator==(Vec<3, T> lhs, Vec<3, T> rhs) noexcept
{
	return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

template <class T>
[[nodiscard]] constexpr bool operator!=(Vec<3, T> lhs, Vec<3, T> rhs) noexcept
{
	return !(lhs == rhs);
}
}  // namespace ufo

#endif  // UFO_MATH_VEC3_HPP