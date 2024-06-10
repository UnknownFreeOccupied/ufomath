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

#ifndef UFO_MATH_POSE2_HPP
#define UFO_MATH_POSE2_HPP

// UFO
#include <ufo/math/detail/pose.hpp>
#include <ufo/math/detail/pose_fun.hpp>
#include <ufo/math/mat2x2.hpp>
#include <ufo/math/mat3x3.hpp>
#include <ufo/math/vec2.hpp>

// STL
#include <cmath>
#include <cstddef>

namespace ufo
{
template <class T>
struct Pose<2, T> {
	using value_type = T;
	using size_type  = std::size_t;

	Vec2<T> position;
	// Orientation in radius
	T theta{};

	/**************************************************************************************
	|                                                                                     |
	|                                    Constructors                                     |
	|                                                                                     |
	**************************************************************************************/

	constexpr Pose() noexcept             = default;
	constexpr Pose(Pose const &) noexcept = default;

	constexpr Pose(Vec2<T> position, T theta) noexcept : position(position), theta(theta) {}

	template <class Position, class Theta>
	constexpr Pose(Vec2<Position> position, Theta theta) noexcept
	    : position(position), theta(static_cast<T>(theta))
	{
	}

	template <class Position, class U>
	constexpr Pose(Vec2<Position> position, Mat2x2<U> const &theta) noexcept
	    : position(position), theta(...)
	{
	}

	template <class U>
	constexpr explicit Pose(Mat3x3<U> const &m) : position(m[2]), theta(...)
	{
	}

	constexpr Pose(T x, T y, T theta) noexcept : position(x, y), theta(theta) {}

	template <class X, class Y, class Theta>
	constexpr Pose(X x, Y y, Theta theta) noexcept
	    : position(x, y), theta(static_cast<T>(theta))
	{
	}

	template <class U>
	constexpr Pose(Pose<2, U> const &other) noexcept
	    : position(other.position), theta(static_cast<T>(other.theta))
	{
	}

	/**************************************************************************************
	|                                                                                     |
	|                                 Assignment operator                                 |
	|                                                                                     |
	**************************************************************************************/

	constexpr Pose &operator=(Pose const &) noexcept = default;

	template <class U>
	constexpr Pose &operator=(Pose<2, U> rhs) noexcept
	{
		position = rhs.position;
		theta    = static_cast<T>(rhs.theta);
		return *this;
	}

	/**************************************************************************************
	|                                                                                     |
	|                                 Conversion operator                                 |
	|                                                                                     |
	**************************************************************************************/

	constexpr explicit operator Mat2x2<T>() const
	{
		auto sin_theta = std::sin(theta);
		auto cos_theta = std::cos(theta);

		// clang-format off
		return {cos_theta, -sin_theta,
		        sin_theta,  cos_theta};
		// clang-format on
	}

	constexpr explicit operator Mat3x3<T>() const
	{
		auto sin_theta = std::sin(theta);
		auto cos_theta = std::cos(theta);

		// clang-format off
		return {cos_theta, -sin_theta, position.x,
		        sin_theta,  cos_theta, position.y,
						T(0),       T(0),      T(1)};
		// clang-format on
	}
};
}  // namespace ufo

#endif  // UFO_MATH_POSE2_HPP