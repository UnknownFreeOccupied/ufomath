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
#include <ufo/math/mat3x3.hpp>
#include <ufo/math/mat4x4.hpp>
#include <ufo/math/vec3.hpp>
#include <ufo/math/vec4.hpp>

// STL
#include <cmath>
#include <ostream>

namespace ufo
{
template <class T = float>
struct Quat {
	using value_type = T;
	using size_type  = std::size_t;

	T x{};
	T y{};
	T z{};
	T w{1};

	/**************************************************************************************
	|                                                                                     |
	|                                    Constructors                                     |
	|                                                                                     |
	**************************************************************************************/

	constexpr Quat() noexcept             = default;
	constexpr Quat(Quat const &) noexcept = default;

	constexpr Quat(T x, T y, T z, T w) noexcept : x(x), y(y), z(z), w(w) {}

	// TODO: Is the one below correct?
	constexpr Quat(T roll, T pitch, T yaw) noexcept
	{
		T sroll  = std::sin(roll);
		T spitch = std::sin(pitch);
		T syaw   = std::sin(yaw);
		T croll  = std::cos(roll);
		T cpitch = std::cos(pitch);
		T cyaw   = std::cos(yaw);

		T m[3][3] = {// create rotational Matrix
		             {cyaw * cpitch, cyaw * spitch * sroll - syaw * croll,
		              cyaw * spitch * croll + syaw * sroll},
		             {syaw * cpitch, syaw * spitch * sroll + cyaw * croll,
		              syaw * spitch * croll - cyaw * sroll},
		             {-spitch, cpitch * sroll, cpitch * croll}};

		T _w = std::sqrt(std::max(T(0), T(1) + m[0][0] + m[1][1] + m[2][2])) / T(2);
		T _x = std::sqrt(std::max(T(0), T(1) + m[0][0] - m[1][1] - m[2][2])) / T(2);
		T _y = std::sqrt(std::max(T(0), T(1) - m[0][0] + m[1][1] - m[2][2])) / T(2);
		T _z = std::sqrt(std::max(T(0), T(1) - m[0][0] - m[1][1] + m[2][2])) / T(2);

		w = _w;
		x = (m[2][1] - m[1][2]) >= T(0) ? std::abs(_x) : -std::abs(_x);
		y = (m[0][2] - m[2][0]) >= T(0) ? std::abs(_y) : -std::abs(_y);
		z = (m[1][0] - m[0][1]) >= T(0) ? std::abs(_z) : -std::abs(_z);
	}

	constexpr Quat(Vec3<T> axis, T angle) noexcept
	{
		T s = std::sin(angle * T(0.5)) / norm(axis);
		w   = std::cos(angle * T(0.5));
		x   = axis.x * s;
		y   = axis.y * s;
		z   = axis.z * s;
	}

	template <class U>
	constexpr Quat(Quat<U> q) noexcept
	    : x(static_cast<T>(q.x))
	    , y(static_cast<T>(q.y))
	    , z(static_cast<T>(q.z))
	    , w(static_cast<T>(q.w))
	{
	}

	constexpr Quat(Mat3x3<T> const &m) noexcept
	{
		T fourXSquaredMinus1 = m[0][0] - m[1][1] - m[2][2];
		T fourYSquaredMinus1 = m[1][1] - m[0][0] - m[2][2];
		T fourZSquaredMinus1 = m[2][2] - m[0][0] - m[1][1];
		T fourWSquaredMinus1 = m[0][0] + m[1][1] + m[2][2];

		int biggestIndex             = 0;
		T   fourBiggestSquaredMinus1 = fourWSquaredMinus1;
		if (fourXSquaredMinus1 > fourBiggestSquaredMinus1) {
			fourBiggestSquaredMinus1 = fourXSquaredMinus1;
			biggestIndex             = 1;
		}
		if (fourYSquaredMinus1 > fourBiggestSquaredMinus1) {
			fourBiggestSquaredMinus1 = fourYSquaredMinus1;
			biggestIndex             = 2;
		}
		if (fourZSquaredMinus1 > fourBiggestSquaredMinus1) {
			fourBiggestSquaredMinus1 = fourZSquaredMinus1;
			biggestIndex             = 3;
		}

		T biggestVal =
		    sqrt(fourBiggestSquaredMinus1 + static_cast<T>(1)) * static_cast<T>(0.5);
		T mult = static_cast<T>(0.25) / biggestVal;

		switch (biggestIndex) {
			case 0:
				x = (m[1][2] - m[2][1]) * mult;
				y = (m[2][0] - m[0][2]) * mult;
				z = (m[0][1] - m[1][0]) * mult;
				w = biggestVal;
				break;
			case 1:
				x = biggestVal;
				y = (m[0][1] + m[1][0]) * mult;
				z = (m[2][0] + m[0][2]) * mult;
				w = (m[1][2] - m[2][1]) * mult;
				break;
			case 2:
				x = (m[0][1] + m[1][0]) * mult;
				y = biggestVal;
				z = (m[1][2] + m[2][1]) * mult;
				w = (m[2][0] - m[0][2]) * mult;
			case 3:
				x = (m[2][0] + m[0][2]) * mult;
				y = (m[1][2] + m[2][1]) * mult;
				z = biggestVal;
				w = (m[0][1] - m[1][0]) * mult;
				break;
			default:  // Silence a -Wswitch-default warning in GCC. Should never actually get
			          // here. Assert is just for sanity.
				assert(false);
				x = T(0);
				y = T(0);
				z = T(0);
				w = T(1);
				break;
		}

		// T trace = m[0][0] + m[1][1] + m[2][2];
		// T temp[4];

		// if (T(0) < trace) {
		// 	T s     = std::sqrt(trace + T(1));
		// 	temp[3] = (s * static_cast<T>(0.5));
		// 	s       = static_cast<T>(0.5) / s;

		// 	temp[0] = ((m[1][2] - m[2][1]) * s);
		// 	temp[1] = ((m[2][0] - m[0][2]) * s);
		// 	temp[2] = ((m[0][1] - m[1][0]) * s);
		// } else {
		// 	int i =
		// 	    m[0][0] < m[1][1] ? (m[1][1] < m[2][2] ? 2 : 1) : (m[0][0] < m[2][2] ? 2 : 0);
		// 	int j = (i + 1) % 3;
		// 	int k = (i + 2) % 3;

		// 	T s     = std::sqrt(m[i][i] - m[j][j] - m[k][k] + T(1));
		// 	temp[i] = s * static_cast<T>(0.5);
		// 	s       = static_cast<T>(0.5) / s;

		// 	temp[3] = (m[j][k] - m[k][j]) * s;
		// 	temp[j] = (m[i][j] + m[j][i]) * s;
		// 	temp[k] = (m[i][k] + m[k][i]) * s;
		// }
		// x = temp[0];
		// y = temp[1];
		// z = temp[2];
		// w = temp[3];
	}

	constexpr Quat(Mat4x4<T> const &m) noexcept : Quat(Mat3x3<T>(m)) {}

	/**************************************************************************************
	|                                                                                     |
	|                                 Assignment operator                                 |
	|                                                                                     |
	**************************************************************************************/

	constexpr Quat &operator=(Quat const &) noexcept = default;

	template <class U>
	constexpr Quat &operator=(Quat<U> rhs) noexcept
	{
		w = rhs.w;
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		return *this;
	}

	/**************************************************************************************
	|                                                                                     |
	|                                 Conversion operator                                 |
	|                                                                                     |
	**************************************************************************************/

	constexpr explicit operator Mat3x3<T>() const
	{
		Mat3x3<T> Result(T(1));
		T         qxx(x * x);
		T         qyy(y * y);
		T         qzz(z * z);
		T         qxz(x * z);
		T         qxy(x * y);
		T         qyz(y * z);
		T         qwx(w * x);
		T         qwy(w * y);
		T         qwz(w * z);

		Result[0][0] = T(1) - T(2) * (qyy + qzz);
		Result[0][1] = T(2) * (qxy + qwz);
		Result[0][2] = T(2) * (qxz - qwy);

		Result[1][0] = T(2) * (qxy - qwz);
		Result[1][1] = T(1) - T(2) * (qxx + qzz);
		Result[1][2] = T(2) * (qyz + qwx);

		Result[2][0] = T(2) * (qxz + qwy);
		Result[2][1] = T(2) * (qyz - qwx);
		Result[2][2] = T(1) - T(2) * (qxx + qyy);
		return Result;
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

	[[nodiscard]] static constexpr Quat fromEuler(T yaw, T pitch, T roll) noexcept
	{
		T hy = yaw * T(0.5);
		T hp = pitch * T(0.5);
		T hr = roll * T(0.5);
		T cy = std::cos(hy);
		T sy = std::sin(hy);
		T cp = std::cos(hp);
		T sp = std::sin(hp);
		T cr = std::cos(hr);
		T sr = std::sin(hr);
		return {
		    cr * sp * cy + sr * cp * sy,  // x
		    cr * cp * sy - sr * sp * cy,  // y
		    sr * cp * cy - cr * sp * sy,  // z
		    cr * cp * cy + sr * sp * sy   // w
		};
	}

	[[nodiscard]] static constexpr Quat fromRPY(T roll, T pitch, T yaw) noexcept
	{
		T hy = yaw * T(0.5);
		T hp = pitch * T(0.5);
		T hr = roll * T(0.5);
		T cy = std::cos(hy);
		T sy = std::sin(hy);
		T cp = std::cos(hp);
		T sp = std::sin(hp);
		T cr = std::cos(hr);
		T sr = std::sin(hr);
		return {
		    sr * cp * cy - cr * sp * sy,  // x
		    cr * sp * cy + sr * cp * sy,  // y
		    cr * cp * sy - sr * sp * cy,  // z
		    cr * cp * cy + sr * sp * sy   // w
		};
	}

	constexpr Vec3<T> toEuler() const noexcept
	{  // create rotational matrix
		T n = norm();
		T s = n > T(0) ? T(2) / (n * n) : T(0);

		T xs = x * s;
		T ys = y * s;
		T zs = z * s;

		T wx = w * xs;
		T wy = w * ys;
		T wz = w * zs;

		T xx = x * xs;
		T xy = x * ys;
		T xz = x * zs;

		T yy = y * ys;
		T yz = y * zs;
		T zz = z * zs;

		T m[3][3];

		m[0][0] = T(1) - (yy + zz);
		m[1][1] = T(1) - (xx + zz);
		m[2][2] = T(1) - (xx + yy);

		m[1][0] = xy + wz;
		m[0][1] = xy - wz;

		m[2][0] = xz - wy;
		m[0][2] = xz + wy;
		m[2][1] = yz + wx;
		m[1][2] = yz - wx;

		T roll  = std::atan2(m[2][1], m[2][2]);
		T pitch = std::atan2(-m[2][0], std::sqrt(m[2][1] * m[2][1] + m[2][2] * m[2][2]));
		T yaw   = std::atan2(m[1][0], m[0][0]);

		return Vec3<T>(roll, pitch, yaw);
	}

	constexpr auto norm() const noexcept
	{
		T n = 0;
		for (unsigned int i = 0; i < 4; i++) {
			n += operator[](i) * operator[](i);
		}
		return std::sqrt(n);
	}

	constexpr auto normSquared() const noexcept
	{
		T n = 0;
		for (unsigned int i = 0; i < 4; i++) {
			n += operator[](i) * operator[](i);
		}
		return n;
	}

	constexpr Quat normalized() const noexcept
	{
		Quat result(*this);
		result.normalize();
		return result;
	}

	constexpr Quat &normalize() noexcept
	{
		T len = norm();
		if (len > T(0)) *this /= len;
		return *this;
	}

	constexpr void operator/=(T x) noexcept
	{
		for (unsigned int i = 0; i < 4; ++i) {
			operator[](i) /= x;
		}
	}

	constexpr bool operator==(Quat const &rhs) const noexcept
	{
		for (unsigned int i = 0; i < 4; i++) {
			if (operator[](i) != rhs[i]) {
				return false;
			}
		}
		return true;
	}

	constexpr bool operator!=(Quat const &rhs) const noexcept { return !(*this == rhs); }

	constexpr Quat operator*(Quat const &rhs) const noexcept
	{
		return Quat(w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z,
		            w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y,
		            w * rhs.y - x * rhs.z + y * rhs.w + z * rhs.x,
		            w * rhs.z + x * rhs.y - y * rhs.x + z * rhs.w);
	}

	template <typename T2>
	constexpr Quat operator*(Vec3<T2> const &v) const noexcept
	{
		return *this * Quat(0, v(0), v(1), v(2));
	}

	constexpr Quat inversed() const noexcept { return Quat(w, -x, -y, -z); }

	constexpr Quat &inverse() noexcept
	{
		x = -x;
		y = -y;
		z = -z;
		return *this;
	}

	template <class P>
	constexpr P rotate(P point) const noexcept
	{
		Quat q  = *this * point * this->inversed();
		point.x = q.x;
		point.y = q.y;
		point.z = q.z;
		return point;
	}

	template <class P>
	constexpr void rotateInPlace(P &point) const noexcept
	{
		Quat q  = *this * point * this->inversed();
		point.x = q.x;
		point.y = q.y;
		point.z = q.z;
	}

	constexpr T roll() const noexcept { return toEuler()[0]; }

	constexpr T pitch() const noexcept { return toEuler()[1]; }

	constexpr T yaw() const noexcept { return toEuler()[2]; }

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

	void swap(Quat &other) noexcept
	{
		std::swap(x, other.x);
		std::swap(y, other.y);
		std::swap(z, other.z);
		std::swap(w, other.w);
	}
};

using Quatf = Quat<float>;
using Quatd = Quat<double>;

/**************************************************************************************
|                                                                                     |
|                                     Operations                                      |
|                                                                                     |
**************************************************************************************/

template <class T>
void swap(Quat<T> &lhs, Quat<T> &rhs) noexcept
{
	lhs.swap(rhs);
}

template <class T>
std::ostream &operator<<(std::ostream &out, Quat<T> q)
{
	return out << "qx: " << q.x << " qy: " << q.y << " qz: " << q.z << " qw: " << q.w;
}

/**************************************************************************************
|                                                                                     |
|                                       Compare                                       |
|                                                                                     |
**************************************************************************************/

template <class T>
[[nodiscard]] constexpr bool operator==(Quat<T> lhs, Quat<T> rhs) noexcept
{
	return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
}

template <class T>
[[nodiscard]] constexpr bool operator!=(Quat<T> lhs, Quat<T> rhs) noexcept
{
	return !(lhs == rhs);
}
}  // namespace ufo

#endif  // UFO_MATH_QUAT_HPP