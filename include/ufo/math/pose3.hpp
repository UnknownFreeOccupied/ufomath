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

#ifndef UFO_MATH_POSE3_HPP
#define UFO_MATH_POSE3_HPP

// UFO
#include <ufo/math/vec2.hpp>

// STL
#include <cmath>
#include <ostream>
#include <type_traits>

namespace ufo {
template <typename T> struct Pose3 : public Vec2<T> {
  T yaw;

  constexpr Pose3() noexcept = default;

  template <typename T1, typename T2>
  constexpr Pose3(Vec2<T1> const &translation, T yaw) noexcept
      : Vec2<T>(translation), yaw(yaw) {}

  constexpr Pose3(T x, T y, T yaw) noexcept : Vec2<T>(x, y), yaw(yaw) {}

  constexpr Pose3(Pose3 const &) noexcept = default; // Redundant

  template <typename T2, class = std::enable_if_t<not std::is_same_v<T, T2>>>
  constexpr Pose3(Pose3<T2> const other) noexcept
      : Vec2<T>(static_cast<Vec2<T2>>(other)), yaw(other.yaw) {}

  constexpr Pose3 &operator=(Pose3 const &) noexcept = default; // Redundant

  template <typename T2, class = std::enable_if_t<not std::is_same_v<T, T2>>>
  constexpr Pose3 &operator=(Pose3<T2> const rhs) noexcept {
    static_cast<Vec2<T> &>(*this) = static_cast<Vec2<T2>>(rhs);
    yaw = rhs.yaw;
    return *this;
  }

  friend constexpr bool operator==(Pose3 lhs, Pose3 rhs) noexcept {
    return static_cast<Vec2<T>>(lhs) == static_cast<Vec2<T>>(rhs) &&
           lhs.yaw == rhs.yaw;
  }

  friend constexpr bool operator!=(Pose3 lhs, Pose3 rhs) noexcept {
    return !(lhs == rhs);
  }

  template <class P> constexpr P transform(P point) const noexcept {
    transformInPlace(point);
    return point;
  }

  template <class P> constexpr void transformInPlace(P &point) const noexcept {
    auto sin_yaw = std::sin(yaw);
    auto cos_yaw = std::cos(yaw);

    auto tmp = point;
    point.x = cos_yaw * tmp.x - sin_yaw * tmp.y + tmp.x;
    point.y = sin_yaw * tmp.x + cos_yaw * tmp.y + tmp.y;
  }

  constexpr Pose3 inversed() const noexcept {
    Pose3 result(*this);
    return result.inverse();
  }

  constexpr Pose3 &inverse() noexcept {
    auto sin_yaw = std::sin(yaw);
    auto cos_yaw = std::cos(yaw);
    auto x = -this->x * cos_yaw - this->y * sin_yaw;
    auto y = this->x * sin_yaw - this->y * cos_yaw;
    this->x = x;
    this->y = y;
    yaw = -yaw;
    return *this;
  }

  // TODO: Implement
  // constexpr Pose3 operator*(Pose3 other) const noexcept
  // {
  // 	Quat<T> rotationnew    = rotation * other.rotation;
  // 	Vec2<T> transation_new = rotation.rotate(other.translation) +
  // translation; 	return Pose3(transation_new, rotationnew.normalize());
  // }

  // TODO: Implement
  // constexpr void operator*=(Pose3 other) noexcept
  // {
  // 	translation += rotation.rotate(other.translation);
  // 	rotation = rotation * other.rotation;
  // }

  [[nodiscard]] constexpr auto distance(Pose3 other) const noexcept {
    return static_cast<Vec2<T>>(*this).distance(static_cast<Vec2<T>>(other));
  }

  constexpr auto translationLength() const noexcept {
    return static_cast<Vec2<T>>(*this).norm();
  }

  constexpr std::array<T, 9> transformMatrix() const noexcept {
    auto sin_yaw = std::sin(yaw);
    auto cos_yaw = std::cos(yaw);

    // clang-format off
		return {cos_yaw, -sin_yaw, this->x,
		        sin_yaw,  cos_yaw, this->y,
						T(0),     T(0),    T(1)};
    // clang-format on
  }
};

template <typename T>
std::ostream &operator<<(std::ostream &out, ufo::Pose3<T> pose) {
  return out << "x: " << pose.x << " y: " << pose.y << " yaw: " << pose.yaw;
}

using Pose3f = Pose3<float>;
using Pose3d = Pose3<double>;
} // namespace ufo

#endif // UFO_MATH_POSE3_HPP