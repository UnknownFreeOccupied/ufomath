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
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TOROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef UFO_MATH_VEC4_HPP
#define UFO_MATH_VEC4_HPP
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
struct Vec<4, T> {
	using value_type = T;
	using size_type  = std::size_t;

	T x{};
	T y{};
	T z{};
	T w{};

	/**************************************************************************************
	|                                                                                     |
	|                                    Constructors                                     |
	|                                                                                     |
	**************************************************************************************/

	constexpr Vec() noexcept            = default;
	constexpr Vec(Vec const &) noexcept = default;

	constexpr explicit Vec(T value) noexcept : x(value), y(value), z(value), w(value) {}

	constexpr Vec(T x, T y, T z, T w) noexcept : x(x), y(y), z(z), w(w) {}

	template <class U>
	constexpr explicit Vec(Vec<1, U> v) noexcept
	    : x(static_cast<T>(v.x))
	    , y(static_cast<T>(v.x))
	    , z(static_cast<T>(v.x))
	    , w(static_cast<T>(v.x))
	{
	}

	template <class X, class Y, class Z, class W>
	constexpr Vec(X x, Y y, Z z, W w) noexcept
	    : x(static_cast<T>(x))
	    , y(static_cast<T>(y))
	    , z(static_cast<T>(z))
	    , w(static_cast<T>(w))
	{
	}

	template <class X, class Y, class Z, class W>
	constexpr Vec(Vec<1, X> x, Y y, Z z, W w) noexcept
	    : x(static_cast<T>(x.x))
	    , y(static_cast<T>(y))
	    , z(static_cast<T>(z))
	    , w(static_cast<T>(w))
	{
	}

	template <class X, class Y, class Z, class W>
	constexpr Vec(X x, Vec<1, Y> y, Z z, W w) noexcept
	    : x(static_cast<T>(x))
	    , y(static_cast<T>(y.x))
	    , z(static_cast<T>(z))
	    , w(static_cast<T>(w))
	{
	}

	template <class X, class Y, class Z, class W>
	constexpr Vec(Vec<1, X> x, Vec<1, Y> y, Z z, W w) noexcept
	    : x(static_cast<T>(x.x))
	    , y(static_cast<T>(y.x))
	    , z(static_cast<T>(z))
	    , w(static_cast<T>(w))
	{
	}

	template <class X, class Y, class Z, class W>
	constexpr Vec(X x, Y y, Vec<1, Z> z, W w) noexcept
	    : x(static_cast<T>(x))
	    , y(static_cast<T>(y))
	    , z(static_cast<T>(z.x))
	    , w(static_cast<T>(w))
	{
	}

	template <class X, class Y, class Z, class W>
	constexpr Vec(Vec<1, X> x, Y y, Vec<1, Z> z, W w) noexcept
	    : x(static_cast<T>(x.x))
	    , y(static_cast<T>(y))
	    , z(static_cast<T>(z.x))
	    , w(static_cast<T>(w))
	{
	}

	template <class X, class Y, class Z, class W>
	constexpr Vec(X x, Vec<1, Y> y, Vec<1, Z> z, W w) noexcept
	    : x(static_cast<T>(x))
	    , y(static_cast<T>(y.x))
	    , z(static_cast<T>(z.x))
	    , w(static_cast<T>(w))
	{
	}

	template <class X, class Y, class Z, class W>
	constexpr Vec(Vec<1, X> x, Vec<1, Y> y, Vec<1, Z> z, W w) noexcept
	    : x(static_cast<T>(x.x))
	    , y(static_cast<T>(y.x))
	    , z(static_cast<T>(z.x))
	    , w(static_cast<T>(w))
	{
	}

	template <class X, class Y, class Z, class W>
	constexpr Vec(Vec<1, X> x, Y y, Z z, Vec<1, W> w) noexcept
	    : x(static_cast<T>(x.x))
	    , y(static_cast<T>(y))
	    , z(static_cast<T>(z))
	    , w(static_cast<T>(w.x))
	{
	}

	template <class X, class Y, class Z, class W>
	constexpr Vec(X x, Vec<1, Y> y, Z z, Vec<1, W> w) noexcept
	    : x(static_cast<T>(x))
	    , y(static_cast<T>(y.x))
	    , z(static_cast<T>(z))
	    , w(static_cast<T>(w.x))
	{
	}

	template <class X, class Y, class Z, class W>
	constexpr Vec(Vec<1, X> x, Vec<1, Y> y, Z z, Vec<1, W> w) noexcept
	    : x(static_cast<T>(x.x))
	    , y(static_cast<T>(y.x))
	    , z(static_cast<T>(z))
	    , w(static_cast<T>(w.x))
	{
	}

	template <class X, class Y, class Z, class W>
	constexpr Vec(X x, Y y, Vec<1, Z> z, Vec<1, W> w) noexcept
	    : x(static_cast<T>(x))
	    , y(static_cast<T>(y))
	    , z(static_cast<T>(z.x))
	    , w(static_cast<T>(w.x))
	{
	}

	template <class X, class Y, class Z, class W>
	constexpr Vec(Vec<1, X> x, Y y, Vec<1, Z> z, Vec<1, W> w) noexcept
	    : x(static_cast<T>(x.x))
	    , y(static_cast<T>(y))
	    , z(static_cast<T>(z.x))
	    , w(static_cast<T>(w.x))
	{
	}

	template <class X, class Y, class Z, class W>
	constexpr Vec(X x, Vec<1, Y> y, Vec<1, Z> z, Vec<1, W> w) noexcept
	    : x(static_cast<T>(x))
	    , y(static_cast<T>(y.x))
	    , z(static_cast<T>(z.x))
	    , w(static_cast<T>(w.x))
	{
	}

	template <class X, class Y, class Z, class W>
	constexpr Vec(Vec<1, X> x, Vec<1, Y> y, Vec<1, Z> z, Vec<1, W> w) noexcept
	    : x(static_cast<T>(x.x))
	    , y(static_cast<T>(y.x))
	    , z(static_cast<T>(z.x))
	    , w(static_cast<T>(w.x))
	{
	}

	template <class XY, class Z, class W>
	constexpr Vec(Vec<2, XY> xy, Z z, W w) noexcept
	    : x(static_cast<T>(xy.x))
	    , y(static_cast<T>(xy.y))
	    , z(static_cast<T>(z))
	    , w(static_cast<T>(w))
	{
	}

	template <class XY, class Z, class W>
	constexpr Vec(Vec<2, XY> xy, Vec<1, Z> z, W w) noexcept
	    : x(static_cast<T>(xy.x))
	    , y(static_cast<T>(xy.y))
	    , z(static_cast<T>(z.x))
	    , w(static_cast<T>(w))
	{
	}

	template <class XY, class Z, class W>
	constexpr Vec(Vec<2, XY> xy, Z z, Vec<1, W> w) noexcept
	    : x(static_cast<T>(xy.x))
	    , y(static_cast<T>(xy.y))
	    , z(static_cast<T>(z))
	    , w(static_cast<T>(w.x))
	{
	}

	template <class XY, class Z, class W>
	constexpr Vec(Vec<2, XY> xy, Vec<1, Z> z, Vec<1, W> w) noexcept
	    : x(static_cast<T>(xy.x))
	    , y(static_cast<T>(xy.y))
	    , z(static_cast<T>(z.x))
	    , w(static_cast<T>(w.x))
	{
	}

	template <class X, class YZ, class W>
	constexpr Vec(X x, Vec<2, YZ> yz, W w) noexcept
	    : x(static_cast<T>(x))
	    , y(static_cast<T>(yz.x))
	    , z(static_cast<T>(yz.y))
	    , w(static_cast<T>(w))
	{
	}

	template <class X, class YZ, class W>
	constexpr Vec(Vec<1, X> x, Vec<2, YZ> yz, W w) noexcept
	    : x(static_cast<T>(x.x))
	    , y(static_cast<T>(yz.x))
	    , z(static_cast<T>(yz.y))
	    , w(static_cast<T>(w))
	{
	}

	template <class X, class YZ, class W>
	constexpr Vec(X x, Vec<2, YZ> yz, Vec<1, W> w) noexcept
	    : x(static_cast<T>(x))
	    , y(static_cast<T>(yz.x))
	    , z(static_cast<T>(yz.y))
	    , w(static_cast<T>(w.x))
	{
	}

	template <class X, class YZ, class W>
	constexpr Vec(Vec<1, X> x, Vec<2, YZ> yz, Vec<1, W> w) noexcept
	    : x(static_cast<T>(x.x))
	    , y(static_cast<T>(yz.x))
	    , z(static_cast<T>(yz.y))
	    , w(static_cast<T>(w.x))
	{
	}

	template <class X, class Y, class ZW>
	constexpr Vec(X x, Y y, Vec<2, ZW> zw) noexcept
	    : x(static_cast<T>(x))
	    , y(static_cast<T>(y))
	    , z(static_cast<T>(zw.x))
	    , w(static_cast<T>(zw.y))
	{
	}

	template <class X, class Y, class ZW>
	constexpr Vec(Vec<1, X> x, Y y, Vec<2, ZW> zw) noexcept
	    : x(static_cast<T>(x.x))
	    , y(static_cast<T>(y))
	    , z(static_cast<T>(zw.x))
	    , w(static_cast<T>(zw.y))
	{
	}

	template <class X, class Y, class ZW>
	constexpr Vec(X x, Vec<1, Y> y, Vec<2, ZW> zw) noexcept
	    : x(static_cast<T>(x))
	    , y(static_cast<T>(y.x))
	    , z(static_cast<T>(zw.x))
	    , w(static_cast<T>(zw.y))
	{
	}

	template <class X, class Y, class ZW>
	constexpr Vec(Vec<1, X> x, Vec<1, Y> y, Vec<2, ZW> zw) noexcept
	    : x(static_cast<T>(x.x))
	    , y(static_cast<T>(y.x))
	    , z(static_cast<T>(zw.x))
	    , w(static_cast<T>(zw.y))
	{
	}

	template <class XY, class ZW>
	constexpr explicit Vec(Vec<2, XY> xy, Vec<2, ZW> zw) noexcept
	    : x(static_cast<T>(xy.x))
	    , y(static_cast<T>(xy.y))
	    , z(static_cast<T>(zw.x))
	    , w(static_cast<T>(zw.y))
	{
	}

	template <class XYZ, class W>
	constexpr explicit Vec(Vec<3, XYZ> xyz, W w) noexcept
	    : x(static_cast<T>(xyz.x))
	    , y(static_cast<T>(xyz.y))
	    , z(static_cast<T>(xyz.z))
	    , w(static_cast<T>(w))
	{
	}

	template <class XYZ, class W>
	constexpr explicit Vec(Vec<3, XYZ> xyz, Vec<1, W> w) noexcept
	    : x(static_cast<T>(xyz.x))
	    , y(static_cast<T>(xyz.y))
	    , z(static_cast<T>(xyz.z))
	    , w(static_cast<T>(w.x))
	{
	}

	template <class X, class YZW>
	constexpr explicit Vec(X x, Vec<3, YZW> yzw) noexcept
	    : x(static_cast<T>(x))
	    , y(static_cast<T>(yzw.x))
	    , z(static_cast<T>(yzw.y))
	    , w(static_cast<T>(yzw.z))
	{
	}

	template <class X, class YZW>
	constexpr explicit Vec(Vec<1, X> x, Vec<3, YZW> yzw) noexcept
	    : x(static_cast<T>(x.x))
	    , y(static_cast<T>(yzw.x))
	    , z(static_cast<T>(yzw.y))
	    , w(static_cast<T>(yzw.z))
	{
	}

	template <class U>
	constexpr explicit Vec(Vec<4, U> v) noexcept
	    : x(static_cast<T>(v.x))
	    , y(static_cast<T>(v.y))
	    , z(static_cast<T>(v.z))
	    , w(static_cast<T>(v.w))
	{
	}

	/**************************************************************************************
	|                                                                                     |
	|                                 Assignment operator                                 |
	|                                                                                     |
	**************************************************************************************/

	constexpr Vec &operator=(Vec const &) noexcept = default;

	template <class U>
	constexpr Vec &operator=(Vec<4, U> rhs) noexcept
	{
		x = static_cast<T>(rhs.x);
		y = static_cast<T>(rhs.y);
		z = static_cast<T>(rhs.z);
		w = static_cast<T>(rhs.w);
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

	[[nodiscard]] constexpr T operator[](size_type pos) const noexcept
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

	constexpr Vec operator-() const noexcept { return {-x, -y, -z, -w}; }

	constexpr Vec operator~() const noexcept { return {~x, ~y, ~z, ~w}; }

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
		w += static_cast<T>(value);
		return *this;
	}

	template <class U>
	constexpr Vec &operator+=(Vec<1, U> v) noexcept
	{
		x += static_cast<T>(v.x);
		y += static_cast<T>(v.x);
		z += static_cast<T>(v.x);
		w += static_cast<T>(v.x);
		return *this;
	}

	template <class U>
	constexpr Vec &operator+=(Vec<4, U> v) noexcept
	{
		x += static_cast<T>(v.x);
		y += static_cast<T>(v.y);
		z += static_cast<T>(v.z);
		w += static_cast<T>(v.w);
		return *this;
	}

	template <class U>
	constexpr Vec &operator-=(U value) noexcept
	{
		x -= static_cast<T>(value);
		y -= static_cast<T>(value);
		z -= static_cast<T>(value);
		w -= static_cast<T>(value);
		return *this;
	}

	template <class U>
	constexpr Vec &operator-=(Vec<1, U> v) noexcept
	{
		x -= static_cast<T>(v.x);
		y -= static_cast<T>(v.x);
		z -= static_cast<T>(v.x);
		w -= static_cast<T>(v.x);
		return *this;
	}

	template <class U>
	constexpr Vec &operator-=(Vec<4, U> v) noexcept
	{
		x -= static_cast<T>(v.x);
		y -= static_cast<T>(v.y);
		z -= static_cast<T>(v.z);
		w -= static_cast<T>(v.w);
		return *this;
	}

	template <class U>
	constexpr Vec &operator*=(U value) noexcept
	{
		x *= static_cast<T>(value);
		y *= static_cast<T>(value);
		z *= static_cast<T>(value);
		w *= static_cast<T>(value);
		return *this;
	}

	template <class U>
	constexpr Vec &operator*=(Vec<1, U> v) noexcept
	{
		x *= static_cast<T>(v.x);
		y *= static_cast<T>(v.x);
		z *= static_cast<T>(v.x);
		w *= static_cast<T>(v.x);
		return *this;
	}

	template <class U>
	constexpr Vec &operator*=(Vec<4, U> v) noexcept
	{
		x *= static_cast<T>(v.x);
		y *= static_cast<T>(v.y);
		z *= static_cast<T>(v.z);
		w *= static_cast<T>(v.w);
		return *this;
	}

	template <class U>
	constexpr Vec &operator/=(U value) noexcept
	{
		x /= static_cast<T>(value);
		y /= static_cast<T>(value);
		z /= static_cast<T>(value);
		w /= static_cast<T>(value);
		return *this;
	}

	template <class U>
	constexpr Vec &operator/=(Vec<1, U> v) noexcept
	{
		x /= static_cast<T>(v.x);
		y /= static_cast<T>(v.x);
		z /= static_cast<T>(v.x);
		w /= static_cast<T>(v.x);
		return *this;
	}

	template <class U>
	constexpr Vec &operator/=(Vec<4, U> v) noexcept
	{
		x /= static_cast<T>(v.x);
		y /= static_cast<T>(v.y);
		z /= static_cast<T>(v.z);
		w /= static_cast<T>(v.w);
		return *this;
	}

	template <class U>
	constexpr Vec &operator%=(U value) noexcept
	{
		x %= static_cast<T>(value);
		y %= static_cast<T>(value);
		z %= static_cast<T>(value);
		w %= static_cast<T>(value);
		return *this;
	}

	template <class U>
	constexpr Vec &operator%=(Vec<1, U> v) noexcept
	{
		x %= static_cast<T>(v.x);
		y %= static_cast<T>(v.x);
		z %= static_cast<T>(v.x);
		w %= static_cast<T>(v.x);
		return *this;
	}

	template <class U>
	constexpr Vec &operator%=(Vec<4, U> v) noexcept
	{
		x %= static_cast<T>(v.x);
		y %= static_cast<T>(v.y);
		z %= static_cast<T>(v.z);
		w %= static_cast<T>(v.w);
		return *this;
	}

	template <class U>
	constexpr Vec &operator&=(U value) noexcept
	{
		x &= static_cast<T>(value);
		y &= static_cast<T>(value);
		z &= static_cast<T>(value);
		w &= static_cast<T>(value);
		return *this;
	}

	template <class U>
	constexpr Vec &operator&=(Vec<1, U> v) noexcept
	{
		x &= static_cast<T>(v.x);
		y &= static_cast<T>(v.x);
		z &= static_cast<T>(v.x);
		w &= static_cast<T>(v.x);
		return *this;
	}

	template <class U>
	constexpr Vec &operator&=(Vec<4, U> v) noexcept
	{
		x &= static_cast<T>(v.x);
		y &= static_cast<T>(v.y);
		z &= static_cast<T>(v.z);
		w &= static_cast<T>(v.w);
		return *this;
	}

	template <class U>
	constexpr Vec &operator|=(U value) noexcept
	{
		x |= static_cast<T>(value);
		y |= static_cast<T>(value);
		z |= static_cast<T>(value);
		w |= static_cast<T>(value);
		return *this;
	}

	template <class U>
	constexpr Vec &operator|=(Vec<1, U> v) noexcept
	{
		x |= static_cast<T>(v.x);
		y |= static_cast<T>(v.x);
		z |= static_cast<T>(v.x);
		w |= static_cast<T>(v.x);
		return *this;
	}

	template <class U>
	constexpr Vec &operator|=(Vec<4, U> v) noexcept
	{
		x |= static_cast<T>(v.x);
		y |= static_cast<T>(v.y);
		z |= static_cast<T>(v.z);
		w |= static_cast<T>(v.w);
		return *this;
	}

	template <class U>
	constexpr Vec &operator^=(U value) noexcept
	{
		x ^= static_cast<T>(value);
		y ^= static_cast<T>(value);
		z ^= static_cast<T>(value);
		w ^= static_cast<T>(value);
		return *this;
	}

	template <class U>
	constexpr Vec &operator^=(Vec<1, U> v) noexcept
	{
		x ^= static_cast<T>(v.x);
		y ^= static_cast<T>(v.x);
		z ^= static_cast<T>(v.x);
		w ^= static_cast<T>(v.x);
		return *this;
	}

	template <class U>
	constexpr Vec &operator^=(Vec<4, U> v) noexcept
	{
		x ^= static_cast<T>(v.x);
		y ^= static_cast<T>(v.y);
		z ^= static_cast<T>(v.z);
		w ^= static_cast<T>(v.w);
		return *this;
	}

	template <class U>
	constexpr Vec &operator<<=(U value) noexcept
	{
		x <<= static_cast<T>(value);
		y <<= static_cast<T>(value);
		z <<= static_cast<T>(value);
		w <<= static_cast<T>(value);
		return *this;
	}

	template <class U>
	constexpr Vec &operator<<=(Vec<1, U> v) noexcept
	{
		x <<= static_cast<T>(v.x);
		y <<= static_cast<T>(v.x);
		z <<= static_cast<T>(v.x);
		w <<= static_cast<T>(v.x);
		return *this;
	}

	template <class U>
	constexpr Vec &operator<<=(Vec<4, U> v) noexcept
	{
		x <<= static_cast<T>(v.x);
		y <<= static_cast<T>(v.y);
		z <<= static_cast<T>(v.z);
		w <<= static_cast<T>(v.w);
		return *this;
	}

	template <class U>
	constexpr Vec &operator>>=(U value) noexcept
	{
		x >>= static_cast<T>(value);
		y >>= static_cast<T>(value);
		z >>= static_cast<T>(value);
		w >>= static_cast<T>(value);
		return *this;
	}

	template <class U>
	constexpr Vec &operator>>=(Vec<1, U> v) noexcept
	{
		x >>= static_cast<T>(v.x);
		y >>= static_cast<T>(v.x);
		z >>= static_cast<T>(v.x);
		w >>= static_cast<T>(v.x);
		return *this;
	}

	template <class U>
	constexpr Vec &operator>>=(Vec<4, U> v) noexcept
	{
		x >>= static_cast<T>(v.x);
		y >>= static_cast<T>(v.y);
		z >>= static_cast<T>(v.z);
		w >>= static_cast<T>(v.w);
		return *this;
	}

	/**************************************************************************************
	|                                                                                     |
	|                                      Capacity                                       |
	|                                                                                     |
	**************************************************************************************/

	[[nodiscard]] static constexpr size_type size() noexcept { return 4; }

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
		std::swap(w, other.w);
	}
};

/**************************************************************************************
|                                                                                     |
|                                  Binary operators                                   |
|                                                                                     |
**************************************************************************************/

template <class T>
[[nodiscard]] constexpr Vec<4, T> operator+(Vec<4, T> v, T value) noexcept
{
	return {v.x + value, v.y + value, v.z + value, v.w + value};
}

template <class T>
[[nodiscard]] constexpr Vec<4, T> operator+(Vec<4, T> v1, Vec<1, T> v2) noexcept
{
	return {v1.x + v2.x, v1.y + v2.x, v1.z + v2.x, v1.w + v2.x};
}

template <class T>
[[nodiscard]] constexpr Vec<4, T> operator+(T value, Vec<4, T> v) noexcept
{
	return {value + v.x, value + v.y, value + v.z, value + v.w};
}

template <class T>
[[nodiscard]] constexpr Vec<4, T> operator+(Vec<1, T> v1, Vec<4, T> v2) noexcept
{
	return {v1.x + v2.x, v1.x + v2.y, v1.x + v2.z, v1.x + v2.w};
}

template <class T>
[[nodiscard]] constexpr Vec<4, T> operator+(Vec<4, T> v1, Vec<4, T> v2) noexcept
{
	return {v1.x + v2.x, v1.y + v2.y, v1.x + v2.z, v1.w + v2.w};
}

template <class T>
[[nodiscard]] constexpr Vec<4, T> operator-(Vec<4, T> v, T value) noexcept
{
	return {v.x - value, v.y - value, v.z - value, v.w - value};
}

template <class T>
[[nodiscard]] constexpr Vec<4, T> operator-(Vec<4, T> v1, Vec<1, T> v2) noexcept
{
	return {v1.x - v2.x, v1.y - v2.x, v1.z - v2.x, v1.w - v2.x};
}

template <class T>
[[nodiscard]] constexpr Vec<4, T> operator-(T value, Vec<4, T> v) noexcept
{
	return {value - v.x, value - v.y, value - v.z, value - v.w};
}

template <class T>
[[nodiscard]] constexpr Vec<4, T> operator-(Vec<1, T> v1, Vec<4, T> v2) noexcept
{
	return {v1.x - v2.x, v1.x - v2.y, v1.x - v2.z, v1.x - v2.w};
}

template <class T>
[[nodiscard]] constexpr Vec<4, T> operator-(Vec<4, T> v1, Vec<4, T> v2) noexcept
{
	return {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w};
}

template <class T>
[[nodiscard]] constexpr Vec<4, T> operator*(Vec<4, T> v, T value) noexcept
{
	return {v.x * value, v.y * value, v.z * value, v.w * value};
}

template <class T>
[[nodiscard]] constexpr Vec<4, T> operator*(Vec<4, T> v1, Vec<1, T> v2) noexcept
{
	return {v1.x * v2.x, v1.y * v2.x, v1.z * v2.x, v1.w * v2.x};
}

template <class T>
[[nodiscard]] constexpr Vec<4, T> operator*(T value, Vec<4, T> v) noexcept
{
	return {value * v.x, value * v.y, value * v.z, value * v.w};
}

template <class T>
[[nodiscard]] constexpr Vec<4, T> operator*(Vec<1, T> v1, Vec<4, T> v2) noexcept
{
	return {v1.x * v2.x, v1.x * v2.y, v1.x * v2.z, v1.x * v2.w};
}

template <class T>
[[nodiscard]] constexpr Vec<4, T> operator*(Vec<4, T> v1, Vec<4, T> v2) noexcept
{
	return {v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w};
}

template <class T>
[[nodiscard]] constexpr Vec<4, T> operator/(Vec<4, T> v, T value) noexcept
{
	return {v.x / value, v.y / value, v.z / value, v.w / value};
}

template <class T>
[[nodiscard]] constexpr Vec<4, T> operator/(Vec<4, T> v1, Vec<1, T> v2) noexcept
{
	return {v1.x / v2.x, v1.y / v2.x, v1.z / v2.x, v1.w / v2.x};
}

template <class T>
[[nodiscard]] constexpr Vec<4, T> operator/(T value, Vec<4, T> v) noexcept
{
	return {value / v.x, value / v.y, value / v.z, value / v.w};
}

template <class T>
[[nodiscard]] constexpr Vec<4, T> operator/(Vec<1, T> v1, Vec<4, T> v2) noexcept
{
	return {v1.x / v2.x, v1.x / v2.y, v1.x / v2.z, v1.x / v2.w};
}

template <class T>
[[nodiscard]] constexpr Vec<4, T> operator/(Vec<4, T> v1, Vec<4, T> v2) noexcept
{
	return {v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w};
}

template <class T>
[[nodiscard]] constexpr Vec<4, T> operator%(Vec<4, T> v, T value) noexcept
{
	return {v.x % value, v.y % value, v.z % value, v.w % value};
}

template <class T>
[[nodiscard]] constexpr Vec<4, T> operator%(Vec<4, T> v1, Vec<1, T> v2) noexcept
{
	return {v1.x % v2.x, v1.y % v2.x, v1.z % v2.x, v1.w % v2.x};
}

template <class T>
[[nodiscard]] constexpr Vec<4, T> operator%(T value, Vec<4, T> v) noexcept
{
	return {value % v.x, value % v.y, value % v.z, value % v.w};
}

template <class T>
[[nodiscard]] constexpr Vec<4, T> operator%(Vec<1, T> v1, Vec<4, T> v2) noexcept
{
	return {v1.x % v2.x, v1.x % v2.y, v1.x % v2.z, v1.x % v2.w};
}

template <class T>
[[nodiscard]] constexpr Vec<4, T> operator%(Vec<4, T> v1, Vec<4, T> v2) noexcept
{
	return {v1.x % v2.x, v1.y % v2.y, v1.z % v2.z, v1.w % v2.w};
}

template <class T>
[[nodiscard]] constexpr Vec<4, T> operator&(Vec<4, T> v, T value) noexcept
{
	return {v.x & value, v.y & value, v.z & value, v.w & value};
}

template <class T>
[[nodiscard]] constexpr Vec<4, T> operator&(Vec<4, T> v1, Vec<1, T> v2) noexcept
{
	return {v1.x & v2.x, v1.y & v2.x, v1.z & v2.x, v1.w & v2.x};
}

template <class T>
[[nodiscard]] constexpr Vec<4, T> operator&(T value, Vec<4, T> v) noexcept
{
	return {value & v.x, value & v.y, value & v.z, value & v.w};
}

template <class T>
[[nodiscard]] constexpr Vec<4, T> operator&(Vec<1, T> v1, Vec<4, T> v2) noexcept
{
	return {v1.x & v2.x, v1.x & v2.y, v1.x & v2.z, v1.x & v2.w};
}

template <class T>
[[nodiscard]] constexpr Vec<4, T> operator&(Vec<4, T> v1, Vec<4, T> v2) noexcept
{
	return {v1.x & v2.x, v1.y & v2.y, v1.z & v2.z, v1.w & v2.w};
}

template <class T>
[[nodiscard]] constexpr Vec<4, T> operator|(Vec<4, T> v, T value) noexcept
{
	return {v.x | value, v.y | value, v.z | value, v.w | value};
}

template <class T>
[[nodiscard]] constexpr Vec<4, T> operator|(Vec<4, T> v1, Vec<1, T> v2) noexcept
{
	return {v1.x | v2.x, v1.y | v2.x, v1.z | v2.x, v1.w | v2.x};
}

template <class T>
[[nodiscard]] constexpr Vec<4, T> operator|(T value, Vec<4, T> v) noexcept
{
	return {value | v.x, value | v.y, value | v.z, value | v.w};
}

template <class T>
[[nodiscard]] constexpr Vec<4, T> operator|(Vec<1, T> v1, Vec<4, T> v2) noexcept
{
	return {v1.x | v2.x, v1.x | v2.y, v1.x | v2.z, v1.x | v2.w};
}

template <class T>
[[nodiscard]] constexpr Vec<4, T> operator|(Vec<4, T> v1, Vec<4, T> v2) noexcept
{
	return {v1.x | v2.x, v1.y | v2.y, v1.z | v2.z, v1.w | v2.w};
}

template <class T>
[[nodiscard]] constexpr Vec<4, T> operator^(Vec<4, T> v, T value) noexcept
{
	return {v.x ^ value, v.y ^ value, v.z ^ value, v.w ^ value};
}

template <class T>
[[nodiscard]] constexpr Vec<4, T> operator^(Vec<4, T> v1, Vec<1, T> v2) noexcept
{
	return {v1.x ^ v2.x, v1.y ^ v2.x, v1.z ^ v2.x, v1.w ^ v2.x};
}

template <class T>
[[nodiscard]] constexpr Vec<4, T> operator^(T value, Vec<4, T> v) noexcept
{
	return {value ^ v.x, value ^ v.y, value ^ v.z, value ^ v.w};
}

template <class T>
[[nodiscard]] constexpr Vec<4, T> operator^(Vec<1, T> v1, Vec<4, T> v2) noexcept
{
	return {v1.x ^ v2.x, v1.x ^ v2.y, v1.x ^ v2.z, v1.x ^ v2.w};
}

template <class T>
[[nodiscard]] constexpr Vec<4, T> operator^(Vec<4, T> v1, Vec<4, T> v2) noexcept
{
	return {v1.x ^ v2.x, v1.y ^ v2.y, v1.z ^ v2.z, v1.w ^ v2.w};
}

template <class T>
[[nodiscard]] constexpr Vec<4, T> operator<<(Vec<4, T> v, T value) noexcept
{
	return {v.x << value, v.y << value, v.z << value, v.w << value};
}

template <class T>
[[nodiscard]] constexpr Vec<4, T> operator<<(Vec<4, T> v1, Vec<1, T> v2) noexcept
{
	return {v1.x << v2.x, v1.y << v2.x, v1.z << v2.x, v1.w << v2.x};
}

template <class T>
[[nodiscard]] constexpr Vec<4, T> operator<<(T value, Vec<4, T> v) noexcept
{
	return {value << v.x, value << v.y, value << v.z, value << v.w};
}

template <class T>
[[nodiscard]] constexpr Vec<4, T> operator<<(Vec<1, T> v1, Vec<4, T> v2) noexcept
{
	return {v1.x << v2.x, v1.x << v2.y, v1.x << v2.z, v1.x << v2.w};
}

template <class T>
[[nodiscard]] constexpr Vec<4, T> operator<<(Vec<4, T> v1, Vec<4, T> v2) noexcept
{
	return {v1.x << v2.x, v1.y << v2.y, v1.z << v2.z, v1.w << v2.w};
}

template <class T>
[[nodiscard]] constexpr Vec<4, T> operator>>(Vec<4, T> v, T value) noexcept
{
	return {v.x >> value, v.y >> value, v.z >> value, v.w >> value};
}

template <class T>
[[nodiscard]] constexpr Vec<4, T> operator>>(Vec<4, T> v1, Vec<1, T> v2) noexcept
{
	return {v1.x >> v2.x, v1.y >> v2.x, v1.z >> v2.x, v1.w >> v2.x};
}

template <class T>
[[nodiscard]] constexpr Vec<4, T> operator>>(T value, Vec<4, T> v) noexcept
{
	return {value >> v.x, value >> v.y, value >> v.z, value >> v.w};
}

template <class T>
[[nodiscard]] constexpr Vec<4, T> operator>>(Vec<1, T> v1, Vec<4, T> v2) noexcept
{
	return {v1.x >> v2.x, v1.x >> v2.y, v1.x >> v2.z, v1.x >> v2.w};
}

template <class T>
[[nodiscard]] constexpr Vec<4, T> operator>>(Vec<4, T> v1, Vec<4, T> v2) noexcept
{
	return {v1.x >> v2.x, v1.y >> v2.y, v1.z >> v2.z, v1.w >> v2.w};
}

[[nodiscard]] constexpr Vec<4, bool> operator&&(Vec<4, bool> v1, Vec<4, bool> v2)
{
	return {v1.x && v2.x, v1.y && v2.y, v1.z && v2.z, v1.w && v2.w};
}

[[nodiscard]] constexpr Vec<4, bool> operator||(Vec<4, bool> v1, Vec<4, bool> v2)
{
	return {v1.x || v2.x, v1.y || v2.y, v1.z || v2.z, v1.w || v2.w};
}

/**************************************************************************************
|                                                                                     |
|                                       Compare                                       |
|                                                                                     |
**************************************************************************************/

template <class T>
[[nodiscard]] constexpr bool operator==(Vec<4, T> lhs, Vec<4, T> rhs) noexcept
{
	return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
}

template <class T>
[[nodiscard]] constexpr bool operator!=(Vec<4, T> lhs, Vec<4, T> rhs) noexcept
{
	return !(lhs == rhs);
}
}  // namespace ufo

#endif  // UFO_MATH_VEC4_HPP