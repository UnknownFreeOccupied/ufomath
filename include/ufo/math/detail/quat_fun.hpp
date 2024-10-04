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

#ifndef UFO_MATH_DETAIL_QUAT_FUN_HPP
#define UFO_MATH_DETAIL_QUAT_FUN_HPP

// UFO
#include <ufo/math/detail/quat.hpp>
#include <ufo/math/detail/vec.hpp>
// We need this here because of Vec<4, bool>
#include <ufo/math/mat.hpp>
#include <ufo/math/vec4.hpp>

// STL
#include <cmath>
#include <limits>

namespace ufo
{
//
// Common
//

template <class T>
[[nodiscard]] Quat<T> mix(Quat<T> const& x, Quat<T> const& y, T a)
{
	T const cos_theta = dot(x, y);

	// Perform a linear interpolation when cosTheta is close to 1 to avoid side effect of
	// sin(angle) becoming a zero denominator
	if (cos_theta > T(1) - std::numeric_limits<T>::epsilon()) {
		// Linear interpolation
		return Quat<T>(mix(x.w, y.w, a), mix(x.x, y.x, a), mix(x.y, y.y, a),
		               mix(x.z, y.z, a));
	}

	// Essential Mathematics, page 467
	T angle = std::acos(cos_theta);
	return (std::sin((T(1) - a) * angle) * x + std::sin(a * angle) * y) / std::sin(angle);
}

template <class T>
[[nodiscard]] Quat<T> lerp(Quat<T> const& x, Quat<T> const& y, T a)
{
	// Lerp is only defined in [0, 1]
	assert(a >= T(0));
	assert(a <= T(1));

	return x * (T(1) - a) + (y * a);
}

template <class T>
[[nodiscard]] Quat<T> slerp(Quat<T> const& x, Quat<T> const& y, T a)
{
	Quat<T> z = y;

	T cos_theta = dot(x, y);

	// If cos_theta < 0, the interpolation will take the long way around the sphere.
	// To fix this, one quat must be negated.
	if (cos_theta < T(0)) {
		z         = -y;
		cos_theta = -cos_theta;
	}

	// Perform a linear interpolation when cos_theta is close to 1 to avoid side effect of
	// sin(angle) becoming a zero denominator
	if (cos_theta > T(1) - std::numeric_limits<T>::epsilon()) {
		// Linear interpolation
		return Quat<T>(mix(x.w, z.w, a), mix(x.x, z.x, a), mix(x.y, z.y, a),
		               mix(x.z, z.z, a));
	}

	// Essential Mathematics, page 467
	T angle = std::acos(cos_theta);
	return (std::sin((T(1) - a) * angle) * x + std::sin(a * angle) * z) / std::sin(angle);
}

template <class T, class S>
[[nodiscard]] Quat<T> slerp(Quat<T> const& x, Quat<T> const& y, T a, S k)
{
	Quat<T> z = y;

	T cos_theta = dot(x, y);

	// If cos_theta < 0, the interpolation will take the long way around the sphere.
	// To fix this, one quat must be negated.
	if (cos_theta < static_cast<T>(0)) {
		z         = -y;
		cos_theta = -cos_theta;
	}

	// Perform a linear interpolation when cos_theta is close to 1 to avoid side effect of
	// sin(angle) becoming a zero denominator
	if (cos_theta > T(1) - std::numeric_limits<T>::epsilon()) {
		// Linear interpolation
		return Quat<T>(mix(x.w, z.w, a), mix(x.x, z.x, a), mix(x.y, z.y, a),
		               mix(x.z, z.z, a));
	}
	// Graphics Gems III, page 96
	T angle = std::acos(cos_theta);
	T phi   = angle + T(k) * T(M_PI);
	return (std::sin(angle - a * phi) * x + std::sin(a * phi) * z) / std::sin(angle);
}

template <class T>
[[nodiscard]] Quat<T> conjugate(Quat<T> const& q)
{
	return Quat<T>(q.w, -q.x, -q.y, -q.z);
}

template <class T>
[[nodiscard]] Quat<T> inverse(Quat<T> const& q)
{
	return conjugate(q) / normSquared(q);
}

template <class T>
[[nodiscard]] Vec<4, bool> isnan(Quat<T> const& q)
{
	return Vec<4, bool>(std::isnan(q.x), std::isnan(q.y), std::isnan(q.z), std::isnan(q.w));
}

template <class T>
[[nodiscard]] Vec<4, bool> isinf(Quat<T> const& q)
{
	return Vec<4, bool>(std::isinf(q.x), std::isinf(q.y), std::isinf(q.z), std::isinf(q.w));
}

//
// TODO: Exponential
//

// template <class T>
// [[nodiscard]] Quat<T> exp(Quat<T> const& q)
// {
// 	// TODO: Implement
// }

// template <class T>
// [[nodiscard]] Quat<T> log(Quat<T> const& q)
// {
// 	// TODO: Implement
// }

// template <class T>
// [[nodiscard]] Quat<T> pow(Quat<T> const& q, T y)
// {
// 	// TODO: Implement
// }

// template <class T>
// [[nodiscard]] Quat<T> sqrt(Quat<T> const& q)
// {
// 	return pow(x, T(0.5));
// }

//
// Geometric
//

template <class T>
[[nodiscard]] T normSquared(Quat<T> const& q)
{
	return dot(q, q);
}

template <class T>
[[nodiscard]] T norm(Quat<T> const& q)
{
	return std::sqrt(normSquared(q));
}

template <class T>
[[nodiscard]] Quat<T> normalize(Quat<T> const& q)
{
	T len = norm(q);
	if (len <= T(0)) {
		// Problem
		return Quat<T>(T(1), T(0), T(0), T(0));
	}
	T one_over_len = T(1) / len;
	return Quat<T>(q.w * one_over_len, q.x * one_over_len, q.y * one_over_len,
	               q.z * one_over_len);
}

template <class T>
[[nodiscard]] T dot(Quat<T> const& x, Quat<T> const& y)
{
	Vec<4, T> tmp(x.w * y.w, x.x * y.x, x.y * y.y, x.z * y.z);
	return (tmp.x + tmp.y) + (tmp.z + tmp.w);
}

template <class T>
[[nodiscard]] Quat<T> cross(Quat<T> const& q1, Quat<T> const& q2)
{
	return Quat<T>(q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z,
	               q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y,
	               q1.w * q2.y + q1.y * q2.w + q1.z * q2.x - q1.x * q2.z,
	               q1.w * q2.z + q1.z * q2.w + q1.x * q2.y - q1.y * q2.x);
}

//
// Transform
//

template <class T>
[[nodiscard]] Quat<T> rotate(Quat<T> const& q, T const& angle, Vec<3, T> axis)
{
	// Axis of rotation must be normalised
	T len = norm(axis);
	if (std::abs(len - T(1)) > T(0.001)) {
		T one_over_len = T(1) / len;
		axis.x *= one_over_len;
		axis.y *= one_over_len;
		axis.z *= one_over_len;
	}

	T const sin = std::sin(angle * T(0.5));

	return q * Quat<T>(std::cos(angle * T(0.5)), axis.x * sin, axis.y * sin, axis.z * sin);
}

//
// Trigonometric
//

template <class T>
[[nodiscard]] T angle(Quat<T> const& q)
{
	constexpr T const cos_one_over_two = 0.877582561890372716130286068203503191;
	if (std::abs(q.w) > cos_one_over_two) {
		T const a = std::asin(std::sqrt(q.x * q.x + q.y * q.y + q.z * q.z)) * T(2);
		if (q.w < T(0)) {
			return T(M_PI) * T(2) - a;
		}
		return a;
	}

	return std::acos(q.w) * T(2);
}

template <class T>
[[nodiscard]] Vec<3, T> axis(Quat<T> const& q)
{
	T const tmp1 = T(1) - q.w * q.w;
	if (tmp1 <= T(0)) {
		return Vec<3, T>(0, 0, 1);
	}
	T const tmp2 = T(1) / std::sqrt(tmp1);
	return Vec<3, T>(q.x * tmp2, q.y * tmp2, q.z * tmp2);
}

template <class T>
[[nodiscard]] Quat<T> angleAxis(T const& angle, Vec<3, T> const& axis)
{
	return Quat<T>(std::cos(angle * T(0.5)), axis * std::sin(angle * T(0.5)));
}

//
// Extra
//

template <class T>
[[nodiscard]] Vec<3, T> eulerAngles(Quat<T> const& q)
{
	return Vec<3, T>(pitch(q), yaw(q), roll(q));
}

template <class T>
[[nodiscard]] T roll(Quat<T> const& q)
{
	T const y = T(2) * (q.x * q.y + q.w * q.z);
	T const x = q.w * q.w + q.x * q.x - q.y * q.y - q.z * q.z;

	if (all(equal(Vec<2, T>(x, y), Vec<2, T>(0), std::numeric_limits<T>::epsilon()))) {
		// avoid atan2(0,0) - handle singularity - Matiis
		return T(0);
	}

	return T(std::atan2(y, x));
}

template <class T>
[[nodiscard]] T pitch(Quat<T> const& q)
{
	T const y = T(2) * (q.y * q.z + q.w * q.x);
	T const x = q.w * q.w - q.x * q.x - q.y * q.y + q.z * q.z;

	if (all(equal(Vec<2, T>(x, y), Vec<2, T>(0), std::numeric_limits<T>::epsilon()))) {
		// avoid atan2(0,0) - handle singularity - Matiis
		return T(T(2) * std::atan2(q.x, q.w));
	}

	return T(std::atan2(y, x));
}

template <class T>
[[nodiscard]] T yaw(Quat<T> const& q)
{
	return std::asin(std::clamp(T(-2) * (q.x * q.z - q.w * q.y), T(-1), T(1)));
}

template <class T, bool RightHanded = true>
[[nodiscard]] Quat<T> quatLookAt(Vec<3, T> const& direction, Vec<3, T> const& up)
{
	Mat<3, 3, T> m;

	if constexpr (RightHanded) {
		m[2] = -direction;
	} else {
		m[2] = direction;
	}
	Vec<3, T> const& right = cross(up, m[2]);
	m[0]                   = right * (T(1) / std::max(std::sqrt(T(0.00001)), norm(right)));
	m[1]                   = cross(m[2], m[0]);

	return Quat<T>(m);
}
}  // namespace ufo

#endif  // UFO_MATH_DETAIL_QUAT_FUN_HPP