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

#ifndef UFO_MATH_DETAIL_VEC_FUN_HPP
#define UFO_MATH_DETAIL_VEC_FUN_HPP

// UFO
#include <ufo/math/detail/vec.hpp>

// STL
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <ostream>

namespace ufo
{
template <std::size_t Dim, class T>
std::ostream &operator<<(std::ostream &out, Vec<Dim, T> v)
{
	out << "x: " << v.x;
	if constexpr (1 < Dim) {
		out << " y: " << v.y;
	}
	if constexpr (2 < Dim) {
		out << " z: " << v.z;
	}
	if constexpr (3 < Dim) {
		out << " w: " << v.w;
	}
	return out;
}

template <std::size_t Dim, class T>
void swap(Vec<Dim, T> &lhs, Vec<Dim, T> &rhs) noexcept
{
	lhs.swap(rhs);
}

template <std::size_t Dim, class T>
[[nodiscard]] T *begin(Vec<Dim, T> &v) noexcept
{
	return &v.x;
}

template <std::size_t Dim, class T>
[[nodiscard]] T const *begin(Vec<Dim, T> const &v) noexcept
{
	return &v.x;
}

template <std::size_t Dim, class T>
[[nodiscard]] T const *cbegin(Vec<Dim, T> const &v) noexcept
{
	return begin(v);
}

template <std::size_t Dim, class T>
[[nodiscard]] T *end(Vec<Dim, T> &v) noexcept
{
	return &v.x + Dim;
}

template <std::size_t Dim, class T>
[[nodiscard]] T const *end(Vec<Dim, T> const &v) noexcept
{
	return &v.x + Dim;
}

template <std::size_t Dim, class T>
[[nodiscard]] T const *cend(Vec<Dim, T> const &v) noexcept
{
	return end(v);
}

template <class T, std::size_t Dim, class U>
[[nodiscard]] constexpr Vec<Dim, T> cast(Vec<Dim, U> const &v)
{
	return Vec<Dim, T>(v);
}

template <std::size_t Dim, class T>
[[nodiscard]] constexpr T normSquared(Vec<Dim, T> v)
{
	for (std::size_t i{}; Dim > i; ++i) {
		v[i] *= v[i];
	}
	T r = v[0];
	for (std::size_t i = 1; Dim > i; ++i) {
		r += v[i];
	}
	return r;
}

template <std::size_t Dim, class T>
[[nodiscard]] constexpr T norm(Vec<Dim, T> v)
{
	return std::sqrt(normSquared(v));
}

template <std::size_t Dim, class T>
[[nodiscard]] constexpr Vec<Dim, T> normalize(Vec<Dim, T> v)
{
	return v / norm(v);
}

template <std::size_t Dim, class T>
[[nodiscard]] constexpr T distanceSquared(Vec<Dim, T> a, Vec<Dim, T> b)
{
	for (std::size_t i{}; Dim > i; ++i) {
		a[i] -= b[i];
		a[i] *= a[i];
	}
	T r = a[0];
	for (std::size_t i = 1; Dim > i; ++i) {
		r += a[i];
	}
	return r;
}

template <std::size_t Dim, class T>
[[nodiscard]] constexpr T distance(Vec<Dim, T> a, Vec<Dim, T> b)
{
	return std::sqrt(distanceSquared(a, b));
}

template <std::size_t Dim, class T>
[[nodiscard]] constexpr T dot(Vec<Dim, T> a, Vec<Dim, T> b)
{
	for (std::size_t i{}; Dim > i; ++i) {
		a[i] *= b[i];
	}
	T r = a[0];
	for (std::size_t i = 1; Dim > i; ++i) {
		r += a[i];
	}
	return r;
}

template <class T>
[[nodiscard]] constexpr Vec3<T> cross(Vec3<T> a, Vec3<T> b)
{
	return {(a.y * b.z) - (a.z * b.y), (a.z * b.x) - (a.x * b.z),
	        (a.x * b.y) - (a.y * b.x)};
}

template <std::size_t Dim, class T>
[[nodiscard]] constexpr Vec<Dim, T> min(Vec<Dim, T> v1, Vec<Dim, T> v2)
{
	Vec<Dim, T> res;
	for (std::size_t i{}; Dim > i; ++i) {
		res[i] = std::min(v1[i], v2[i]);
	}
	return res;
}

template <std::size_t Dim, class T>
[[nodiscard]] constexpr T min(Vec<Dim, T> v)
{
	if constexpr (1 == Dim) {
		return v.x;
	} else if constexpr (4 >= Dim) {
		if constexpr (3 == Dim) {
			v.x = v.x < v.z ? v.x : v.z;
		} else if constexpr (4 == Dim) {
			v.x = v.x < v.z ? v.x : v.z;
			v.y = v.y < v.w ? v.y : v.w;
		}
		return v.x < v.y ? v.x : v.y;
	} else {
		// Error
	}
}

template <std::size_t Dim, class T>
[[nodiscard]] constexpr Vec<Dim, T> max(Vec<Dim, T> v1, Vec<Dim, T> v2)
{
	Vec<Dim, T> res;
	for (std::size_t i{}; Dim > i; ++i) {
		res[i] = std::max(v1[i], v2[i]);
	}
	return res;
}

template <std::size_t Dim, class T>
[[nodiscard]] constexpr T max(Vec<Dim, T> v)
{
	if constexpr (1 == Dim) {
		return v.x;
	} else if constexpr (4 >= Dim) {
		if constexpr (3 == Dim) {
			v.x = v.x > v.z ? v.x : v.z;
		} else if constexpr (4 == Dim) {
			v.x = v.x > v.z ? v.x : v.z;
			v.y = v.y > v.w ? v.y : v.w;
		}
		return v.x > v.y ? v.x : v.y;
	} else {
		// Error
	}
}

template <std::size_t Dim, class T>
[[nodiscard]] constexpr std::size_t minIndex(Vec<Dim, T> v)
{
	if constexpr (1 == Dim) {
		return 0;
	} else if constexpr (2 == Dim) {
		return v.x < v.y ? 0 : 1;
	} else if constexpr (3 == Dim) {
		return v.x < v.y ? (v.x < v.z ? 0 : 2) : (v.y < v.z ? 1 : 2);
	} else if constexpr (4 == Dim) {
		std::size_t a = v.x < v.z ? 0 : 2;
		std::size_t b = v.y < v.w ? 1 : 3;
		return v[a] < v[b] ? a : b;
	} else {
		// Error
	}
}

template <std::size_t Dim, class T>
[[nodiscard]] constexpr std::size_t maxIndex(Vec<Dim, T> v)
{
	if constexpr (1 == Dim) {
		return 0;
	} else if constexpr (2 == Dim) {
		return v.x > v.y ? 0 : 1;
	} else if constexpr (3 == Dim) {
		return v.x > v.y ? (v.x > v.z ? 0 : 2) : (v.y > v.z ? 1 : 2);
	} else if constexpr (4 == Dim) {
		std::size_t a = v.x > v.z ? 0 : 2;
		std::size_t b = v.y > v.w ? 1 : 3;
		return v[a] > v[b] ? a : b;
	} else {
		// Error
	}
}

template <std::size_t Dim, class T>
[[nodiscard]] constexpr T sum(Vec<Dim, T> v)
{
	T sum = v[0];
	for (std::size_t i{1}; Dim > i; ++i) {
		sum += std::abs(v[i]);
	}
	return sum;
}

template <std::size_t Dim, class T>
[[nodiscard]] constexpr Vec<Dim, T> abs(Vec<Dim, T> v)
{
	for (std::size_t i{}; Dim > i; ++i) {
		v[i] = std::abs(v[i]);
	}
	return v;
}

template <std::size_t Dim, class T>
[[nodiscard]] constexpr Vec<Dim, T> clamp(Vec<Dim, T> v, Vec<Dim, T> lo, Vec<Dim, T> hi)
{
	for (std::size_t i{}; Dim > i; ++i) {
		v[i] = std::clamp(v[i], lo[i], hi[i]);
	}
	return v;
}

template <std::size_t Dim, class T>
[[nodiscard]] constexpr Vec<Dim, T> ceil(Vec<Dim, T> v)
{
	for (std::size_t i{}; Dim > i; ++i) {
		v[i] = std::ceil(v[i]);
	}
	return v;
}

template <std::size_t Dim, class T>
[[nodiscard]] constexpr Vec<Dim, T> floor(Vec<Dim, T> v)
{
	for (std::size_t i{}; Dim > i; ++i) {
		v[i] = std::floor(v[i]);
	}
	return v;
}

template <std::size_t Dim, class T>
[[nodiscard]] constexpr Vec<Dim, T> trunc(Vec<Dim, T> v)
{
	for (std::size_t i{}; Dim > i; ++i) {
		v[i] = std::trunc(v[i]);
	}
	return v;
}

template <std::size_t Dim, class T>
[[nodiscard]] constexpr Vec<Dim, T> round(Vec<Dim, T> v)
{
	for (std::size_t i{}; Dim > i; ++i) {
		v[i] = std::round(v[i]);
	}
	return v;
}

template <std::size_t Dim, class T>
[[nodiscard]] constexpr bool equal(Vec<Dim, T> v1, Vec<Dim, T> v2)
{
	for (std::size_t i{}; Dim > i; ++i) {
		if (v1[i] != v2[i]) {
			return false;
		}
	}
	return true;
}

template <std::size_t Dim>
[[nodiscard]] constexpr bool all(Vec<Dim, bool> v)
{
	for (std::size_t i{}; Dim > i; ++i) {
		if (!v[i]) {
			return false;
		}
	}
	return true;
}

template <std::size_t Dim>
[[nodiscard]] constexpr bool any(Vec<Dim, bool> v)
{
	for (std::size_t i{}; Dim > i; ++i) {
		if (v[i]) {
			return true;
		}
	}
	return false;
}

template <std::size_t Dim>
[[nodiscard]] constexpr bool some(Vec<Dim, bool> v)
{
	bool t = false;
	bool f = false;
	for (std::size_t i{}; Dim > i; ++i) {
		t = t || v[i];
		f = f || !v[i];
	}
	return t && f;
}

template <std::size_t Dim>
[[nodiscard]] constexpr bool none(Vec<Dim, bool> v)
{
	for (std::size_t i{}; Dim > i; ++i) {
		if (v[i]) {
			return false;
		}
	}
	return true;
}
}  // namespace ufo

#endif  // UFO_MATH_DETAIL_VEC_FUN_HPP