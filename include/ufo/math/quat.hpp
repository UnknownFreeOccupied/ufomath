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

#ifndef UFO_MATH_QUAT_HPP
#define UFO_MATH_QUAT_HPP

// UFO
#include <ufo/math/detail/quat.hpp>
#include <ufo/math/detail/quat_fun.hpp>
#include <ufo/math/mat3x3.hpp>
#include <ufo/math/mat4x4.hpp>
#include <ufo/math/vec3.hpp>
#include <ufo/math/vec4.hpp>

// STL
#include <cmath>
#include <ostream>

namespace ufo
{
template <class T>
struct Quat {
	using value_type = T;
	using size_type  = std::size_t;

	T w{1};
	T x{};
	T y{};
	T z{};

	/**************************************************************************************
	|                                                                                     |
	|                                    Constructors                                     |
	|                                                                                     |
	**************************************************************************************/

	constexpr Quat() noexcept            = default;
	constexpr Quat(Quat const&) noexcept = default;

	template <class U>
	constexpr Quat(Quat<U> const& q) noexcept
	    : w(static_cast<T>(q.w))
	    , x(static_cast<T>(q.x))
	    , y(static_cast<T>(q.y))
	    , z(static_cast<T>(q.z))
	{
	}

	constexpr Quat(T w, T x, T y, T z) noexcept : w(w), x(x), y(y), z(z) {}

	constexpr Quat(T s, Vec3<T> const& v) noexcept : Quat(s, v.x, v.y, v.z) {}

	Quat(Vec<3, T> const& u, Vec<3, T> const& v)
	{
		// Taken straight from GLM

		T         norm_u_norm_v = std::sqrt(dot(u, u) * dot(v, v));
		T         real_part     = norm_u_norm_v + dot(u, v);
		Vec<3, T> t;

		if (real_part < static_cast<T>(1.e-6f) * norm_u_norm_v) {
			// If u and v are exactly opposite, rotate 180 degrees
			// around an arbitrary orthogonal axis. Axis normalisation
			// can happen later, when we normalise the quaternion.
			real_part = static_cast<T>(0);
			t         = std::abs(u.x) > std::abs(u.z) ? Vec<3, T>(-u.y, u.x, static_cast<T>(0))
			                                          : Vec<3, T>(static_cast<T>(0), -u.z, u.y);
		} else {
			// Otherwise, build quaternion the standard way.
			t = cross(u, v);
		}

		*this = normalize(Quat<T>(real_part, t.x, t.y, t.z));
	}

	// Build a quaternion from euler angles (pitch, yaw, roll (in whatever order you
	// believe, try multiple times)), in radians.
	// NOTE: This seems to be the same as setRPY from ROS 2
	explicit Quat(Vec<3, T> const& euler_angles)
	{
		// Taken straight from GLM

		Vec<3, T> c = cos(euler_angles * T(0.5));
		Vec<3, T> s = sin(euler_angles * T(0.5));

		w = c.x * c.y * c.z + s.x * s.y * s.z;
		x = s.x * c.y * c.z - c.x * s.y * s.z;
		y = c.x * s.y * c.z + s.x * c.y * s.z;
		z = c.x * c.y * s.z - s.x * s.y * c.z;
	}

	constexpr Quat(Mat3x3<T> const& m) noexcept
	{
		// Taken from ROS 2 geometry2 but changed to wxyz, hopefully correct

		T trace = m[0][0] + m[1][1] + m[2][2];

		// So we can treat w, x, y, z as an array
		T* q = &w;

		if (trace > T(0.0)) {
			T s  = std::sqrt(trace + T(1.0));
			q[0] = s * T(0.5);
			s    = T(0.5) / s;

			q[1] = (m[1][2] - m[2][1]) * s;
			q[2] = (m[2][0] - m[0][2]) * s;
			q[3] = (m[0][1] - m[1][0]) * s;
		} else {
			unsigned i = m[0][0] < m[1][1] ? (m[1][1] < m[2][2] ? 2u : 1u)
			                               : (m[0][0] < m[2][2] ? 2u : 0u);
			unsigned j = (i + 1u) % 3u;
			unsigned k = (i + 2u) % 3u;

			T s      = std::sqrt(m[i][i] - m[j][j] - m[k][k] + T(1.0));
			q[i + 1] = s * T(0.5);
			s        = T(0.5) / s;

			q[0]     = (m[j][k] - m[k][j]) * s;
			q[j + 1] = (m[i][j] + m[j][i]) * s;
			q[k + 1] = (m[i][k] + m[k][i]) * s;
		}
	}

	constexpr Quat(Mat4x4<T> const& m) noexcept : Quat(Mat3x3<T>(m)) {}

	/**************************************************************************************
	|                                                                                     |
	|                                 Assignment operator                                 |
	|                                                                                     |
	**************************************************************************************/

	constexpr Quat& operator=(Quat const&) noexcept = default;

	template <class U>
	constexpr Quat& operator=(Quat<U> const& rhs) noexcept
	{
		w = static_cast<T>(rhs.w);
		x = static_cast<T>(rhs.x);
		y = static_cast<T>(rhs.y);
		z = static_cast<T>(rhs.z);
		return *this;
	}

	/**************************************************************************************
	|                                                                                     |
	|                                 Conversion operator                                 |
	|                                                                                     |
	**************************************************************************************/

	constexpr explicit operator Mat3x3<T>() const
	{
		T xx(x * x);
		T yy(y * y);
		T zz(z * z);
		T xz(x * z);
		T xy(x * y);
		T yz(y * z);
		T wx(w * x);
		T wy(w * y);
		T wz(w * z);

		T x1 = T(1) - T(2) * (yy + zz);
		T y1 = T(2) * (xy + wz);
		T z1 = T(2) * (xz - wy);

		T x2 = T(2) * (xy - wz);
		T y2 = T(1) - T(2) * (xx + zz);
		T z2 = T(2) * (yz + wx);

		T x3 = T(2) * (xz + wy);
		T y3 = T(2) * (yz - wx);
		T z3 = T(1) - T(2) * (xx + yy);

		return Mat3x3<T>(x1, y1, z1,   // First column
		                 x2, y2, z2,   // Second column
		                 x3, y3, z3);  // Third column
	}

	constexpr explicit operator Mat4x4<T>() const
	{
		return Mat4x4<T>(static_cast<Mat3x3<T>>(*this));
	}

	/**************************************************************************************
	|                                                                                     |
	|                                   Element access                                    |
	|                                                                                     |
	**************************************************************************************/

	[[nodiscard]] constexpr T& operator[](size_type pos) noexcept
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
	|                            Compound assignment operator                             |
	|                                                                                     |
	**************************************************************************************/

	template <class U>
	Quat<T>& operator+=(Quat<U> const& q)
	{
		w += q.w;
		x += q.x;
		y += q.y;
		z += q.z;
		return *this;
	}

	template <class U>
	Quat<T>& operator-=(Quat<U> const& q)
	{
		w -= q.w;
		x -= q.x;
		y -= q.y;
		z -= q.z;
		return *this;
	}

	template <class U>
	Quat<T>& operator*=(Quat<U> const& q)
	{
		Quat<T> const p(*this);
		Quat<T> const qt(q);

		w = p.w * qt.w - p.x * qt.x - p.y * qt.y - p.z * qt.z;
		x = p.w * qt.x + p.x * qt.w + p.y * qt.z - p.z * qt.y;
		y = p.w * qt.y + p.y * qt.w + p.z * qt.x - p.x * qt.z;
		z = p.w * qt.z + p.z * qt.w + p.x * qt.y - p.y * qt.x;

		return *this;
	}

	template <class U>
	Quat<T>& operator*=(U s)
	{
		w *= s;
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}

	template <class U>
	Quat<T>& operator/=(U s)
	{
		w /= s;
		x /= s;
		y /= s;
		z /= s;
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

	void swap(Quat& other) noexcept
	{
		std::swap(x, other.x);
		std::swap(y, other.y);
		std::swap(z, other.z);
		std::swap(w, other.w);
	}
};

/**************************************************************************************
|                                                                                     |
|                                   Unary operators                                   |
|                                                                                     |
**************************************************************************************/

template <class T>
Quat<T> operator+(Quat<T> const& q)
{
	return q;
}

template <class T>
Quat<T> operator-(Quat<T> const& q)
{
	return Quat<T>(-q.w, -q.x, -q.y, -q.z);
}

/**************************************************************************************
|                                                                                     |
|                                  Binary operators                                   |
|                                                                                     |
**************************************************************************************/

template <class T>
Quat<T> operator+(Quat<T> const& q, Quat<T> const& p)
{
	return Quat<T>(q) += p;
}

template <class T>
Quat<T> operator-(Quat<T> const& q, Quat<T> const& p)
{
	return Quat<T>(q) -= p;
}

template <class T>
Quat<T> operator*(Quat<T> const& q, Quat<T> const& p)
{
	return Quat<T>(q) *= p;
}

template <class T>
Vec<3, T> operator*(Quat<T> const& q, Vec<3, T> const& v)
{
	Vec<3, T> const quat_vector(q.x, q.y, q.z);
	Vec<3, T> const uv(cross(quat_vector, v));
	Vec<3, T> const uuv(cross(quat_vector, uv));

	return v + ((uv * q.w) + uuv) * T(2);
}

template <class T>
Vec<3, T> operator*(Vec<3, T> const& v, Quat<T> const& q)
{
	return inverse(q) * v;
}

template <class T>
Vec<4, T> operator*(Quat<T> const& q, Vec<4, T> const& v)
{
	return Vec<4, T>(q * Vec<3, T>(v), v.w);
}

template <class T>
Vec<4, T> operator*(Vec<4, T> const& v, Quat<T> const& q)
{
	return inverse(q) * v;
}

template <class T>
Quat<T> operator*(Quat<T> const& q, T const& s)
{
	return Quat<T>(q.w * s, q.x * s, q.y * s, q.z * s);
}

template <class T>
Quat<T> operator*(T const& s, Quat<T> const& q)
{
	return q * s;
}

template <class T>
Quat<T> operator/(Quat<T> const& q, T const& s)
{
	return Quat<T>(q.w / s, q.x / s, q.y / s, q.z / s);
}

/**************************************************************************************
|                                                                                     |
|                                       Compare                                       |
|                                                                                     |
**************************************************************************************/

template <class T>
[[nodiscard]] constexpr bool operator==(Quat<T> const& lhs, Quat<T> const& rhs) noexcept
{
	return lhs.w == rhs.w && lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

template <class T>
[[nodiscard]] constexpr bool operator!=(Quat<T> const& lhs, Quat<T> const& rhs) noexcept
{
	return !(lhs == rhs);
}

/**************************************************************************************
|                                                                                     |
|                                     Operations                                      |
|                                                                                     |
**************************************************************************************/

template <class T>
void swap(Quat<T>& lhs, Quat<T>& rhs) noexcept
{
	lhs.swap(rhs);
}

template <class T>
std::ostream& operator<<(std::ostream& out, Quat<T> const& q)
{
	return out << "qw: " << q.w << " qx: " << q.x << " qy: " << q.y << " qz: " << q.z;
}
}  // namespace ufo

#endif  // UFO_MATH_QUAT_HPP