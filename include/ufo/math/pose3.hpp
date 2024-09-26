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

#ifndef UFO_MATH_POSE3_HPP
#define UFO_MATH_POSE3_HPP

// UFO
#include <ufo/math/detail/pose.hpp>
#include <ufo/math/detail/pose_fun.hpp>
#include <ufo/math/mat3x3.hpp>
#include <ufo/math/mat4x4.hpp>
#include <ufo/math/quat.hpp>
#include <ufo/math/vec3.hpp>

namespace ufo
{
template <class T>
struct Pose<3, T> {
	using value_type = T;
	using size_type  = std::size_t;

	Vec3<T> position;
	Quat<T> orientation;

	/**************************************************************************************
	|                                                                                     |
	|                                    Constructors                                     |
	|                                                                                     |
	**************************************************************************************/

	constexpr Pose() noexcept             = default;
	constexpr Pose(Pose const &) noexcept = default;

	constexpr Pose(Vec3<T> position, Quat<T> orientation) noexcept
	    : position(position), orientation(orientation)
	{
	}

	template <class Position, class Orientation>
	constexpr Pose(Vec3<Position> position, Quat<Orientation> orientation) noexcept
	    : position(position), orientation(orientation)
	{
	}

	template <class Position, class U>
	constexpr Pose(Vec3<Position> position, Mat3x3<U> const &orientation) noexcept
	    : position(position), orientation(orientation)
	{
	}

	template <class U>
	constexpr explicit Pose(Mat4x4<U> const &m) noexcept
	    : position(m[3]), orientation(Mat3x3<U>(m))
	{
	}

	constexpr Pose(T x, T y, T z, T qx, T qy, T qz, T qw) noexcept
	    : position(x, y, z), orientation(qx, qy, qz, qw)
	{
	}

	template <class X, class Y, class Z, class QX, class QY, class QZ, class QW>
	constexpr Pose(X x, Y y, Z z, QX qx, QY qy, QZ qz, QW qw) noexcept
	    : position(x, y, z), orientation(qx, qy, qz, qw)
	{
	}

	template <class U>
	constexpr Pose(Pose<3, U> const &other) noexcept
	    : position(other.position), orientation(other.orientation)
	{
	}

	/**************************************************************************************
	|                                                                                     |
	|                                 Assignment operator                                 |
	|                                                                                     |
	**************************************************************************************/

	constexpr Pose &operator=(Pose const &) noexcept = default;

	template <class U>
	constexpr Pose &operator=(Pose<3, U> const &rhs) noexcept
	{
		position    = rhs.position;
		orientation = rhs.orientation;
		return *this;
	}

	/**************************************************************************************
	|                                                                                     |
	|                                 Conversion operator                                 |
	|                                                                                     |
	**************************************************************************************/

	constexpr explicit operator Mat3x3<T>() const
	{
		T d = normSquared(orientation);

		assert(d != T(0));

		T s = T(2) / d;

		T xs = orientation.x * s;
		T ys = orientation.y() * s;
		T zs = orientation.z() * s;
		T wx = orientation.w * xs;
		T wy = orientation.w() * ys;
		T wz = orientation.w() * zs;
		T xx = orientation.x * xs;
		T xy = orientation.x() * ys;
		T xz = orientation.x() * zs;
		T yy = orientation.y * ys;
		T yz = orientation.y() * zs;
		T zz = orientation.z() * zs;

		// clang-format off
		return {T(1) - (yy + zz), xy + wz,          xz - wy, 
		        xy - wz,          T(1) - (xx + zz), yz + wx, 
						xz + wy,          yz - wx,          T(1) - (xx + yy)};
		// clang-format on
	}

	constexpr explicit operator Mat4x4<T>() const
	{
		// TODO: T d = normSquared(orientation);
		T d = orientation.normSquared();

		assert(d != T(0));

		T s = T(2) / d;

		T xs = orientation.x * s;
		T ys = orientation.y * s;
		T zs = orientation.z * s;
		T wx = orientation.w * xs;
		T wy = orientation.w * ys;
		T wz = orientation.w * zs;
		T xx = orientation.x * xs;
		T xy = orientation.x * ys;
		T xz = orientation.x * zs;
		T yy = orientation.y * ys;
		T yz = orientation.y * zs;
		T zz = orientation.z * zs;

		// clang-format off
		return {T(1) - (yy + zz), xy + wz,          xz - wy,          T(0),
		        xy - wz,          T(1) - (xx + zz), yz + wx,          T(0),
						xz + wy,          yz - wx,          T(1) - (xx + yy), T(0),
						position.x,       position.y,       position.z,       T(1)};
		// clang-format on
	}
};
}  // namespace ufo

#endif  // UFO_MATH_POSE3_HPP