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

#ifndef UFO_MATH_TRANSFORM3_HPP
#define UFO_MATH_TRANSFORM3_HPP

// UFO
#include <ufo/math/detail/transform.hpp>
#include <ufo/math/detail/transform_fun.hpp>
#include <ufo/math/mat3x3.hpp>
#include <ufo/math/mat4x4.hpp>
#include <ufo/math/quat.hpp>
#include <ufo/math/vec3.hpp>

namespace ufo
{
template <class T>
struct Transform<3, T> {
	using value_type = T;
	using size_type  = std::size_t;

	Mat<3, 3, T> rotation;
	Vec<3, T>    translation;

	/**************************************************************************************
	|                                                                                     |
	|                                    Constructors                                     |
	|                                                                                     |
	**************************************************************************************/

	constexpr Transform() noexcept                 = default;
	constexpr Transform(Transform const&) noexcept = default;

	constexpr Transform(Mat<3, 3, T> const& rotation, Vec<3, T> const& translation)
	    : rotation(rotation), translation(translation)
	{
	}

	constexpr explicit Transform(Mat<3, 3, T> const& rotation) : rotation(rotation) {}

	template <class T1, class T2>
	constexpr Transform(Mat<3, 3, T1> const& rotation, Vec<3, T2> const& translation)
	    : rotation(rotation), translation(translation)
	{
	}

	template <class U>
	constexpr explicit Transform(Mat<3, 3, U> const& rotation) : rotation(rotation)
	{
	}

	template <class T1, class T2>
	constexpr Transform(Quat<T1> const& rotation, Vec<3, T2> const& translation)
	    : Transform(Mat<3, 3, T1>(rotation), translation)
	{
	}

	template <class U>
	constexpr explicit Transform(Quat<U> const& rotation)
	    : Transform(Mat<3, 3, U>(rotation))
	{
	}

	template <class U>
	constexpr explicit Transform(Mat<4, 4, U> const& m)
	    : Transform(Mat<3, 3, U>(m), Vec<3, U>(m[3]))
	{
	}

	template <class U>
	constexpr explicit Transform(Transform<3, U> const& other) noexcept
	    : rotation(other.rotation), translation(other.translation)
	{
	}

	/**************************************************************************************
	|                                                                                     |
	|                                 Assignment operator                                 |
	|                                                                                     |
	**************************************************************************************/

	constexpr Transform& operator=(Transform const&) noexcept = default;

	template <class U>
	constexpr Transform& operator=(Transform<3, U> const& rhs) noexcept
	{
		rotation    = rhs.rotation;
		translation = rhs.translation;
		return *this;
	}

	/**************************************************************************************
	|                                                                                     |
	|                                 Conversion operator                                 |
	|                                                                                     |
	**************************************************************************************/

	template <class U>
	constexpr explicit operator Mat<3, 3, U>() const
	{
		return Mat<3, 3, U>(rotation);
	}

	template <class U>
	constexpr explicit operator Mat<4, 4, U>() const
	{
		Mat<4, 4, U> m(rotation);
		m[3] = Vec<4, U>(translation, U(1));
		return m;
	}

	template <class U>
	constexpr explicit operator Quat<U>() const
	{
		return Quat<U>(rotation);
	}

	/**************************************************************************************
	|                                                                                     |
	|                                      Something                                      |
	|                                                                                     |
	**************************************************************************************/

	template <class U>
	[[nodiscard]] Vec<3, U> operator()(Vec<3, U> const& v) const
	{
		// clang-format off
		return Vec<3, U>(
				rotation[0][0] * v[0] + rotation[1][0] * v[1] + rotation[2][0] * v[2] + translation[0],
				rotation[0][1] * v[0] + rotation[1][1] * v[1] + rotation[2][1] * v[2] + translation[1],
				rotation[0][2] * v[0] + rotation[1][2] * v[1] + rotation[2][2] * v[2] + translation[2]
			);
		// clang-format on
		// return Mat<4, 4, U>(*this) * Vec<4, U>(v, U(1));
	}

	template <class U>
	[[nodiscard]] Quat<U> operator()(Quat<U> const& q) const
	{
		return Quat<U>(*this) * q;
	}

	template <class U>
	Transform& operator*=(Transform<3, U> const& t)
	{
		auto tmp = *this * t.translation;
		rotation *= t.rotation;
		translation = tmp;
	}
};

template <class T>
Transform<3, T> operator*(Transform<3, T> const& t1, Transform<3, T> const& t2)
{
	Transform<3, T> t = t1;
	t *= t2;
	return t;
}

template <class T>
Vec<3, T> operator*(Transform<3, T> const& t, Vec<3, T> const& v)
{
	return t(v);
}

template <class T>
Quat<T> operator*(Transform<3, T> const& t, Quat<T> const& q)
{
	return t(q);
}

template <class T>
std::ostream& operator<<(std::ostream& out, Transform<3, T> const& t)
{
	return out << "Translation: " << t.translation << ", Rotation: " << Quat<T>(t);
}

/**************************************************************************************
|                                                                                     |
|                                       Compare                                       |
|                                                                                     |
**************************************************************************************/

template <class T>
[[nodiscard]] constexpr bool operator==(Transform<3, T> const& lhs,
                                        Transform<3, T> const& rhs) noexcept
{
	return lhs.rotation == rhs.rotation && lhs.translation == rhs.translation;
}

template <class T>
[[nodiscard]] constexpr bool operator!=(Transform<3, T> const& lhs,
                                        Transform<3, T> const& rhs) noexcept
{
	return lhs.rotation != rhs.rotation || lhs.translation != rhs.translation;
}
}  // namespace ufo

#endif  // UFO_MATH_TRANSFORM3_HPP