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

#ifndef UFO_MATH_POSE6_HPP
#define UFO_MATH_POSE6_HPP

// UFO
#include <ufo/math/quat.hpp>
#include <ufo/math/vec3.hpp>

// STL
#include <ostream>
#include <type_traits>

namespace ufo {
template <typename T> struct Pose6 {
  Vec3<T> translation;
  Quat<T> rotation;

  constexpr Pose6() noexcept = default;

  template <typename T1, typename T2>
  constexpr Pose6(Vec3<T1> const &translation,
                  Quat<T2> const &rotation) noexcept
      : translation(translation), rotation(rotation) {}

  constexpr Pose6(T x, T y, T z, T roll, T pitch, T yaw) noexcept
      : translation(x, y, z), rotation(roll, pitch, yaw) {}

  constexpr Pose6(T t_x, T t_y, T t_z, T r_w, T r_x, T r_y, T r_z) noexcept
      : translation(t_x, t_y, t_z), rotation(r_w, r_x, r_y, r_z) {}

  constexpr Pose6(Pose6 const &) noexcept = default; // Redundant

  template <typename T2, class = std::enable_if_t<not std::is_same_v<T, T2>>>
  constexpr Pose6(Pose6<T2> const other) noexcept
      : translation(other.translation), rotation(other.rotation) {}

  constexpr Pose6 &operator=(Pose6 const &) noexcept = default; // Redundant

  template <typename T2, class = std::enable_if_t<not std::is_same_v<T, T2>>>
  constexpr Pose6 &operator=(Pose6<T2> const rhs) noexcept {
    translation = rhs.translation;
    rotation = rhs.rotation;
    return *this;
  }

  constexpr bool operator==(Pose6 const &rhs) noexcept {
    return translation == rhs.translation && rotation == rhs.rotation;
  }

  constexpr bool operator!=(Pose6 const &rhs) noexcept {
    return !(*this == rhs);
  }

  constexpr T &x() noexcept { return translation.x; }

  constexpr T x() const noexcept { return translation.x; }

  constexpr T &y() noexcept { return translation.y; }

  constexpr T y() const noexcept { return translation.y; }

  constexpr T &z() noexcept { return translation.z; }

  constexpr T z() const noexcept { return translation.z; }

  constexpr T &qx() noexcept { return rotation.x; }

  constexpr T qx() const noexcept { return rotation.x; }

  constexpr T &qy() noexcept { return rotation.y; }

  constexpr T qy() const noexcept { return rotation.y; }

  constexpr T &qz() noexcept { return rotation.z; }

  constexpr T qz() const noexcept { return rotation.z; }

  constexpr T &qw() noexcept { return rotation.w; }

  constexpr T qw() const noexcept { return rotation.w; }

  constexpr T roll() const noexcept { return rotation.roll(); }

  constexpr T pitch() const noexcept { return rotation.pitch(); }

  constexpr T yaw() const noexcept { return rotation.yaw(); }

  template <class P> constexpr P transform(P point) const noexcept {
    point = rotation.rotate(point);
    point += translation;
    return point;
  }

  template <class P> constexpr void transformInPlace(P &point) const noexcept {
    rotation.rotateInPlace(point);
    point += translation;
  }

  constexpr Pose6 inversed() const noexcept {
    Pose6 result(*this);
    return result.inverse();
  }

  constexpr Pose6 &inverse() noexcept {
    rotation.inverse().normalize();
    translation = -translation;
    rotation.rotateInPlace(translation);
    return *this;
  }

  constexpr Pose6 operator*(Pose6 const &other) const noexcept {
    Quat<T> rotationnew = rotation * other.rotation;
    Vec3<T> transation_new = rotation.rotate(other.translation) + translation;
    return Pose6(transation_new, rotationnew.normalize());
  }

  constexpr Pose6 &operator*=(Pose6 const &other) noexcept {
    translation += rotation.rotate(other.translation);
    rotation = rotation * other.rotation;
    return *this;
  }

  constexpr auto distance(Pose6 const &other) const noexcept {
    return translation.distance(other.translation);
  }

  constexpr auto translationLength() const noexcept {
    return translation.norm();
  }

  constexpr std::array<T, 16> transformMatrix() const noexcept {
    T const n = rotation.norm();
    T const s = n > T(0) ? T(2) / (n * n) : T(0);

    T const xs = rotation.x * s;
    T const ys = rotation.y * s;
    T const zs = rotation.z * s;

    T const wx = rotation.w * xs;
    T const wy = rotation.w * ys;
    T const wz = rotation.w * zs;

    T const xx = rotation.x * xs;
    T const xy = rotation.x * ys;
    T const xz = rotation.x * zs;

    T const yy = rotation.y * ys;
    T const yz = rotation.y * zs;
    T const zz = rotation.z * zs;

    // clang-format off
		return {T(1) - (yy + zz), xy - wz,          xz + wy,          translation.x,
		        xy + wz,          T(1) - (xx + zz), yz - wx,          translation.y,
		        xz - wy,          yz + wx,          T(1) - (xx + yy), translation.z,
						T(0),             T(0),             T(0),             T(1)};
    // clang-format on
  }
};

template <typename T>
std::ostream &operator<<(std::ostream &out, ufo::Pose6<T> pose) {
  return out << pose.translation << " " << pose.rotation;
}

using Pose6f = Pose6<float>;
using Pose6d = Pose6<double>;
} // namespace ufo

#endif // UFO_MATH_POSE6_HPP