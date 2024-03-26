/*!
 * UFOMap: An Efficient Probabilistic 3D Mapping Framework That Embraces the Unknown
 *
 * @author Daniel Duberg (dduberg@kth.se)
 * @see https://github.com/UnknownFreeOccupied/ufomap
 * @version 1.0
 * @date 2022-05-13
 *
 * @copyright Copyright (c) 2022, Daniel Duberg, KTH Royal Institute of Technology
 *
 * BSD 3-Clause License
 *
 * Copyright (c) 2022, Daniel Duberg, KTH Royal Institute of Technology
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *     list of conditions and the following disclaimer.
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
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef UFO_MATH_VEC4_HPP
#define UFO_MATH_VEC4_HPP

// STL
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <ostream>

namespace ufo
{
template <typename T>
struct Vec4 {
	T x = 0;
	T y = 0;
	T z = 0;
	T w = 0;

	constexpr Vec4() noexcept = default;

	constexpr Vec4(T x, T y, T z, T w) noexcept : x(x), y(y), z(z), w(w) {}

	constexpr Vec4(Vec4 const&) noexcept = default;  // Redundant

	template <typename T2, class = std::enable_if_t<not std::is_same_v<T, T2>>>
	constexpr Vec4(Vec4<T2> const other) noexcept
	    : x(static_cast<T>(other.x))
	    , y(static_cast<T>(other.y))
	    , z(static_cast<T>(other.z))
	    , w(static_cast<T>(other.w))
	{
	}

	constexpr Vec4& operator=(Vec4 const&) noexcept = default;  // Redundant

	template <typename T2, class = std::enable_if_t<not std::is_same_v<T, T2>>>
	constexpr Vec4& operator=(Vec4<T2> const rhs) noexcept
	{
		x = static_cast<T>(rhs.x);
		y = static_cast<T>(rhs.y);
		z = static_cast<T>(rhs.z);
		w = static_cast<T>(rhs.w);
		return *this;
	}

	constexpr Vec4 cross(Vec4 const& other) const noexcept { return cross(*this, other); }

	static constexpr Vec4 cross(Vec4 const& first, Vec4 const& second) noexcept
	{
		// TODO: Implement
		return Vec4((first.y * second.z) - (first.z * second.y),
		            (first.z * second.x) - (first.x * second.z),
		            (first.x * second.y) - (first.y * second.x));
	}

	constexpr T dot(Vec4 const& other) const noexcept { return dot(*this, other); }

	static constexpr T dot(Vec4 const& first, Vec4 const& second) noexcept
	{
		// TODO: Implement
		return (first.x * second.x) + (first.y * second.y) + (first.z * second.z);
	}

	constexpr T& operator()(size_t idx) noexcept { return *(&x + idx); }

	constexpr T const& operator()(size_t idx) const noexcept { return *(&x + idx); }

	constexpr T& operator[](size_t idx) noexcept { return *(&x + idx); }

	constexpr T const& operator[](size_t idx) const noexcept { return *(&x + idx); }

	constexpr Vec4 operator-() const noexcept { return Vec4(-x, -y, -z, -w); }

	constexpr Vec4 operator-(Vec4 const& other) const noexcept
	{
		return Vec4(x - other.x, y - other.y, z - other.z, w - other.w);
	}

	constexpr Vec4 operator-(T value) const noexcept
	{
		return Vec4(x - value, y - value, z - value, w - value);
	}

	constexpr Vec4 operator+(Vec4 const& other) const noexcept
	{
		return Vec4(x + other.x, y + other.y, z + other.z, w + other.z);
	}

	constexpr Vec4 operator+(T value) const noexcept
	{
		return Vec4(x + value, y + value, z + value, w + value);
	}

	constexpr Vec4 operator*(Vec4 const& other) const noexcept
	{
		return Vec4(x * other.x, y * other.y, z * other.z, w * other.w);
	}

	constexpr Vec4 operator*(T value) const noexcept
	{
		return Vec4(x * value, y * value, z * value, w * value);
	}

	constexpr Vec4 operator/(Vec4 const& other) const noexcept
	{
		return Vec4(x / other.x, y / other.y, z / other.z, w / other.w);
	}

	constexpr Vec4 operator/(T value) const noexcept
	{
		return Vec4(x / value, y / value, z / value, w / value);
	}

	constexpr void operator-=(Vec4 const& other) noexcept
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;
	}

	constexpr void operator+=(Vec4 const& other) noexcept
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;
	}

	constexpr void operator*=(Vec4 const& other) noexcept
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		w *= other.w;
	}

	constexpr void operator/=(Vec4 const& other) noexcept
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		w /= other.w;
	}

	constexpr void operator-=(T value) noexcept
	{
		x -= value;
		y -= value;
		z -= value;
		w -= value;
	}

	constexpr void operator+=(T value) noexcept
	{
		x += value;
		y += value;
		z += value;
		w += value;
	}

	constexpr void operator*=(T value) noexcept
	{
		x *= value;
		y *= value;
		z *= value;
		w *= value;
	}

	constexpr void operator/=(T value) noexcept
	{
		x /= value;
		y /= value;
		z /= value;
		w /= value;
	}

	constexpr bool operator==(Vec4 const& other) const noexcept
	{
		return x == other.x && y == other.y && z == other.z && w == other.w;
	}

	constexpr bool operator!=(Vec4 const& other) const noexcept
	{
		return !(*this == other);
	}

	constexpr auto norm() const noexcept { return std::sqrt(squaredNorm()); }

	constexpr T squaredNorm() const noexcept
	{
		return (x * x) + (y * y) + (z * z) + (w * w);
	}

	constexpr Vec4& normalize() noexcept
	{
		*this /= norm();
		return *this;
	}

	constexpr Vec4 normalized() const noexcept { return Vec4(*this).normalize(); }

	constexpr auto angleTo(Vec4 const& other) const noexcept
	{
		// TODO: Implement
		return std::acos(dot(other) / (norm() * other.norm()));
	}

	constexpr T squaredDistance(Vec4 const& other) const noexcept
	{
		T d_x = x - other.x;
		T d_y = y - other.y;
		T d_z = z - other.z;
		T d_w = w - other.w;
		return (d_x * d_x) + (d_y * d_y) + (d_z * d_z) + (d_w * d_w);
	}

	constexpr auto distance(Vec4 const& other) const noexcept
	{
		return std::sqrt(squaredDistance(other));
	}

	constexpr T squaredDistanceXY(Vec4 const& other) const noexcept
	{
		T d_x = x - other.x;
		T d_y = y - other.y;
		return (d_x * d_x) + (d_y * d_y);
	}

	constexpr auto distanceXY(Vec4 const& other) const noexcept
	{
		return std::sqrt(squaredDistanceXY(other));
	}

	static constexpr std::size_t size() noexcept { return 3; }

	constexpr T min() const noexcept { return std::min({x, y, z, w}); }

	constexpr T max() const noexcept { return std::max({x, y, z, w}); }

	constexpr std::size_t minElementIndex() const noexcept
	{
		return x <= y ? (x <= z ? (x <= w ? 0 : 3) : (z <= w ? 2 : 3))
		              : (y <= z ? (y <= w ? 1 : 3) : (z <= w ? 2 : 3));
	}

	constexpr std::size_t maxElementIndex() const noexcept
	{
		return x >= y ? (x >= z ? (x >= w ? 0 : 3) : (z >= w ? 2 : 3))
		              : (y >= z ? (y >= w ? 1 : 3) : (z >= w ? 2 : 3));
	}

	constexpr Vec4& ceil() noexcept
	{
		x = std::ceil(x);
		y = std::ceil(y);
		z = std::ceil(z);
		w = std::ceil(w);
		return *this;
	}

	constexpr Vec4 ceil() const noexcept
	{
		return Vec4(std::ceil(x), std::ceil(y), std::ceil(z), std::ceil(w));
	}

	constexpr Vec4& floor() noexcept
	{
		x = std::floor(x);
		y = std::floor(y);
		z = std::floor(z);
		w = std::floor(w);
		return *this;
	}

	constexpr Vec4 floor() const noexcept
	{
		return Vec4(std::floor(x), std::floor(y), std::floor(z), std::floor(w));
	}

	constexpr Vec4& trunc() noexcept
	{
		x = std::trunc(x);
		y = std::trunc(y);
		z = std::trunc(z);
		w = std::trunc(w);
		return *this;
	}

	constexpr Vec4 trunc() const noexcept
	{
		return Vec4(std::trunc(x), std::trunc(y), std::trunc(z), std::trunc(w));
	}

	constexpr Vec4& round() noexcept
	{
		x = std::round(x);
		y = std::round(y);
		z = std::round(z);
		w = std::round(w);
		return *this;
	}

	constexpr Vec4 round() const noexcept
	{
		return Vec4(std::round(x), std::round(y), std::round(z), std::round(w));
	}

	constexpr Vec4& clamp(Vec4 const& min, Vec4 const& max) noexcept
	{
		x = std::clamp(x, min.x, max.x);
		y = std::clamp(y, min.y, max.y);
		z = std::clamp(z, min.z, max.z);
		w = std::clamp(w, min.w, max.w);
		return *this;
	}

	constexpr Vec4 clamp(Vec4 const& min, Vec4 const& max) const noexcept
	{
		return clamp(*this, min, max);
	}

	static constexpr Vec4 clamp(Vec4 const& value, Vec4 const& min,
	                            Vec4 const& max) noexcept
	{
		return Vec4(std::clamp(value.x, min.x, max.x), std::clamp(value.y, min.y, max.y),
		            std::clamp(value.z, min.z, max.z), std::clamp(value.w, min.w, max.w));
	}

	constexpr Vec4& abs() noexcept
	{
		x = std::abs(x);
		y = std::abs(y);
		z = std::abs(z);
		w = std::abs(w);
		return *this;
	}

	constexpr Vec4 abs() const noexcept { return abs(*this); }

	static constexpr Vec4 abs(Vec4 const& value)
	{
		return Vec4(std::abs(value.x), std::abs(value.y), std::abs(value.z),
		            std::abs(value.w));
	}
};

template <typename T>
std::ostream &operator<<(std::ostream &out, ufo::Vec4<T> vec) {
	return out << "x: " << vec.x << " y: " << vec.y << " z: " << vec.z << " w: " << vec.w;
}

using Vec4f = Vec4<float>;
using Vec4d = Vec4<double>;
using Vec4i = Vec4<int>;
}  // namespace ufo

#endif  // UFO_MATH_VEC4_HPP