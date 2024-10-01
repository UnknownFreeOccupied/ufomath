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

#ifndef UFO_MATH_TRANS3_HPP
#define UFO_MATH_TRANS3_HPP

// UFO
#include <ufo/math/detail/trans.hpp>
#include <ufo/math/detail/trans_fun.hpp>
#include <ufo/math/mat3x3.hpp>
#include <ufo/math/mat4x4.hpp>
#include <ufo/math/quat.hpp>
#include <ufo/math/vec3.hpp>

namespace ufo
{
template <class T>
struct Trans<3, T> {
	using value_type = T;
	using size_type  = std::size_t;

	Mat<3, 3, T> rotation;
	Vec<3, T>    translation;

	/**************************************************************************************
	|                                                                                     |
	|                                    Constructors                                     |
	|                                                                                     |
	**************************************************************************************/

	constexpr Trans() noexcept             = default;
	constexpr Trans(Trans const&) noexcept = default;

	constexpr Trans(Mat<3, 3, T> const& rotation, Vec<3, T> const& translation)
	    : rotation(rotation), translation(translation)
	{
	}

	constexpr explicit Trans(Mat<3, 3, T> const& rotation) : rotation(rotation) {}

	template <class T1, class T2>
	constexpr Trans(Mat<3, 3, T1> const& rotation, Vec<3, T2> const& translation)
	    : rotation(rotation), translation(translation)
	{
	}

	template <class U>
	constexpr explicit Trans(Mat<3, 3, U> const& rotation) : rotation(rotation)
	{
	}

	template <class T1, class T2>
	constexpr Trans(Quat<T1> const& rotation, Vec<3, T2> const& translation)
	    : Trans(Mat<3, 3, T1>(rotation), translation)
	{
	}

	template <class U>
	constexpr explicit Trans(Quat<U> const& rotation) : Trans(Mat<3, 3, U>(rotation))
	{
	}

	template <class U>
	constexpr explicit Trans(Mat<4, 4, U> const& m)
	    : Trans(Mat<3, 3, U>(m), Vec<3, U>(m[3]))
	{
	}

	template <class U>
	constexpr explicit Trans(Trans<3, U> const& other) noexcept
	    : rotation(other.rotation), translation(other.translation)
	{
	}

	/**************************************************************************************
	|                                                                                     |
	|                                 Assignment operator                                 |
	|                                                                                     |
	**************************************************************************************/

	constexpr Trans& operator=(Trans const&) noexcept = default;

	template <class U>
	constexpr Trans& operator=(Trans<3, U> const& rhs) noexcept
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
		m[3] = {translation.x, translation.y, translation.z, U(1)};
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
		return Mat<4, 4, U>(*this) * Vec<4, U>(v, U(1));
	}

	template <class U>
	[[nodiscard]] Quat<U> operator()(Quat<U> const& q) const
	{
		return Quat<U>(*this) * q;
	}

	template <class U>
	Trans& operator*=(Trans<3, U> const& t)
	{
		auto trans = *this * t.translation;
		rotation *= t.rotation;
		translation = trans;
	}
};

template <class T>
Trans<3, T> operator*(Trans<3, T> const& t1, Trans<3, T> const& t2)
{
	Trans<3, T> t = t1;
	t *= t2;
	return t;
}

template <class T>
Vec<3, T> operator*(Trans<3, T> const& t, Vec<3, T> const& v)
{
	return t(v);
}

template <class T>
Quat<T> operator*(Trans<3, T> const& t, Quat<T> const& q)
{
	return t(q);
}

template <class T>
std::ostream& operator<<(std::ostream& out, Trans<3, T> const& t)
{
	return out << "Translation: " << t.translation << ", Rotation: " << Quat<T>(t);
}
}  // namespace ufo

#endif  // UFO_MATH_TRANS3_HPP