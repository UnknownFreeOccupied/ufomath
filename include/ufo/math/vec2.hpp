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

// STL
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <ostream>
#include <type_traits>

namespace ufo
{
template <typename T>
struct Vec2 {
	T x = 0;
	T y = 0;

	constexpr Vec2() noexcept = default;

	constexpr Vec2(T x, T y) noexcept : x(x), y(y) {}

	constexpr Vec2(Vec2 const &) noexcept = default;  // Redundant

	template <typename T2, std::enable_if_t<not std::is_same_v<T, T2>, bool> = true>
	constexpr Vec2(Vec2<T2> const other) noexcept
	    : x(static_cast<T>(other.x)), y(static_cast<T>(other.y))
	{
	}

	constexpr Vec2 &operator=(Vec2 const &) noexcept = default;  // Redundant

	template <typename T2, std::enable_if_t<not std::is_same_v<T, T2>, bool> = true>
	constexpr Vec2 &operator=(Vec2<T2> const rhs) noexcept
	{
		x = rhs.x;
		y = rhs.y;
		return *this;
	}

	// Compound addition
	constexpr Vec2 &operator+=(T const &other)
	{
		x += other;
		y += other;
		return *this;
	}

	constexpr Vec2 &operator+=(Vec2 const &other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	// Compound subtraction
	constexpr Vec2 &operator-=(T const &other)
	{
		x -= other;
		y -= other;
		return *this;
	}

	constexpr Vec2 &operator-=(Vec2 const &other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	// Compound multiplication
	constexpr Vec2 &operator*=(T const &other)
	{
		x *= other;
		y *= other;
		return *this;
	}

	constexpr Vec2 &operator*=(Vec2 const &other)
	{
		x *= other.x;
		y *= other.y;
		return *this;
	}

	// Compound division
	constexpr Vec2 &operator/=(T const &other)
	{
		x /= other;
		y /= other;
		return *this;
	}

	constexpr Vec2 &operator/=(Vec2 const &other)
	{
		x /= other.x;
		y /= other.y;
		return *this;
	}

	constexpr T cross(Vec2 const &other) const noexcept { return cross(*this, other); }

	static constexpr T cross(Vec2 const &first, Vec2 const &second) noexcept
	{
		return (first.x * second.y) - (first.y * second.x);
	}

	constexpr T dot(Vec2 const &other) const noexcept { return dot(*this, other); }

	static constexpr T dot(Vec2 const &first, Vec2 const &second) noexcept
	{
		return (first.x * second.x) + (first.y * second.y);
	}

	constexpr T &operator()(size_t idx) noexcept { return *(&x + idx); }

	constexpr T const &operator()(size_t idx) const noexcept { return *(&x + idx); }

	constexpr T &operator[](size_t idx) noexcept { return *(&x + idx); }

	constexpr T const &operator[](size_t idx) const noexcept { return *(&x + idx); }

	constexpr auto norm() const noexcept { return std::sqrt(squaredNorm()); }

	constexpr T squaredNorm() const noexcept { return (x * x) + (y * y); }

	constexpr Vec2 &normalize() noexcept
	{
		*this /= norm();
		return *this;
	}

	constexpr Vec2 normalized() const noexcept { return Vec2(*this).normalize(); }

	constexpr auto angleTo(Vec2 const &other) const noexcept
	{
		return std::acos(dot(other) / (norm() * other.norm()));
	}

	constexpr T squaredDistance(Vec2 const &other) const noexcept
	{
		T d_x = x - other.x;
		T d_y = y - other.y;
		return (d_x * d_x) + (d_y * d_y);
	}

	constexpr auto distance(Vec2 const &other) const noexcept
	{
		return std::sqrt(squaredDistance(other));
	}

	static constexpr std::size_t size() noexcept { return 2; }

	constexpr T min() const noexcept { return x <= y ? x : y; }

	constexpr T max() const noexcept { return x >= y ? x : y; }

	constexpr std::size_t minElementIndex() const noexcept { return x <= y ? 0 : 1; }

	constexpr std::size_t maxElementIndex() const noexcept { return x >= y ? 0 : 1; }

	constexpr Vec2 &ceil() noexcept
	{
		x = std::ceil(x);
		y = std::ceil(y);
		return *this;
	}

	constexpr Vec2 ceil() const noexcept { return {std::ceil(x), std::ceil(y)}; }

	constexpr Vec2 &floor() noexcept
	{
		x = std::floor(x);
		y = std::floor(y);
		return *this;
	}

	constexpr Vec2 floor() const noexcept { return {std::floor(x), std::floor(y)}; }

	constexpr Vec2 &trunc() noexcept
	{
		x = std::trunc(x);
		y = std::trunc(y);
		return *this;
	}

	constexpr Vec2 trunc() const noexcept { return {std::trunc(x), std::trunc(y)}; }

	constexpr Vec2 &round() noexcept
	{
		x = std::round(x);
		y = std::round(y);
		return *this;
	}

	constexpr Vec2 round() const noexcept { return {std::round(x), std::round(y)}; }

	constexpr Vec2 &clamp(Vec2 const &min, Vec2 const &max) noexcept
	{
		x = std::clamp(x, min.x, max.x);
		y = std::clamp(y, min.y, max.y);
		return *this;
	}

	constexpr Vec2 clamp(Vec2 const &min, Vec2 const &max) const noexcept
	{
		return clamp(*this, min, max);
	}

	static constexpr Vec2 clamp(Vec2 const &value, Vec2 const &min,
	                            Vec2 const &max) noexcept
	{
		return {std::clamp(value.x, min.x, max.x), std::clamp(value.y, min.y, max.y)};
	}

	constexpr Vec2 &abs() noexcept
	{
		x = std::abs(x);
		y = std::abs(y);
		return *this;
	}

	constexpr Vec2 abs() const noexcept { return abs(*this); }

	static constexpr Vec2 abs(Vec2 const &value)
	{
		return {std::abs(value.x), std::abs(value.y)};
	}
};

template <typename T>
std::ostream &operator<<(std::ostream &out, ufo::Vec2<T> vec)
{
	return out << "x: " << vec.x << " y: " << vec.y;
}

template <class T>
constexpr bool operator==(Vec2<T> const &lhs, Vec2<T> const &rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

template <class T>
constexpr bool operator!=(Vec2<T> const &lhs, Vec2<T> const &rhs)
{
	return !(lhs == rhs);
}

// Addition
template <class T>
constexpr Vec2<T> operator+(Vec2<T> const &lhs, Vec2<T> const &rhs)
{
	return {lhs.x + rhs.x, lhs.y + rhs.y};
}

template <class T>
constexpr Vec2<T> operator+(Vec2<T> const &lhs, T const &rhs)
{
	return {lhs.x + rhs, lhs.y + rhs};
}

template <class T>
constexpr Vec2<T> operator+(T const &lhs, Vec2<T> const &rhs)
{
	return {lhs + rhs.x, lhs + rhs.y};
}

// Subtraction
template <class T>
constexpr Vec2<T> operator-(Vec2<T> const &lhs, Vec2<T> const &rhs)
{
	return {lhs.x - rhs.x, lhs.y - rhs.y};
}

template <class T>
constexpr Vec2<T> operator-(Vec2<T> const &lhs, T const &rhs)
{
	return {lhs.x - rhs, lhs.y - rhs};
}

template <class T>
constexpr Vec2<T> operator-(T const &lhs, Vec2<T> const &rhs)
{
	return {lhs - rhs.x, lhs - rhs.y};
}

template <class T>
constexpr Vec2<T> operator-(Vec2<T> const &val)
{
	return {-val.x, -val.y};
}

// Multiplication
template <class T>
constexpr Vec2<T> operator*(Vec2<T> const &lhs, Vec2<T> const &rhs)
{
	return {lhs.x * rhs.x, lhs.y * rhs.y};
}

template <class T>
constexpr Vec2<T> operator*(Vec2<T> const &lhs, T const &rhs)
{
	return {lhs.x * rhs, lhs.y * rhs};
}

template <class T>
constexpr Vec2<T> operator*(T const &lhs, Vec2<T> const &rhs)
{
	return {lhs * rhs.x, lhs * rhs.y};
}

// Division
template <class T>
constexpr Vec2<T> operator/(Vec2<T> const &lhs, Vec2<T> const &rhs)
{
	return {lhs.x / rhs.x, lhs.y / rhs.y};
}

template <class T>
constexpr Vec2<T> operator/(Vec2<T> const &lhs, T const &rhs)
{
	return {lhs.x / rhs, lhs.y / rhs};
}

template <class T>
constexpr Vec2<T> operator/(T const &lhs, Vec2<T> const &rhs)
{
	return {lhs / rhs.x, lhs / rhs.y};
}

using Vec2f = Vec2<float>;
using Vec2d = Vec2<double>;
using Vec2i = Vec2<int>;
}  // namespace ufo

#endif  // UFO_MATH_VEC2_HPP