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

#ifndef UFO_MATH_DETAIL_VEC_HPP
#define UFO_MATH_DETAIL_VEC_HPP

// STL
#include <cstddef>

namespace ufo
{
template <std::size_t Dim, class T = float>
struct Vec;

// template <class T, class... U>
// Vec(T, U...) -> Vec<1 + sizeof...(U), T>;

template <class T = float>
using Vec1 = Vec<1, T>;
template <class T = float>
using Vec2 = Vec<2, T>;
template <class T = float>
using Vec3 = Vec<3, T>;
template <class T = float>
using Vec4 = Vec<4, T>;

using Vec1f = Vec1<float>;
using Vec1d = Vec1<double>;
using Vec1i = Vec1<int>;
using Vec1u = Vec1<unsigned>;
using Vec1b = Vec1<bool>;
using Vec2f = Vec2<float>;
using Vec2d = Vec2<double>;
using Vec2i = Vec2<int>;
using Vec2u = Vec2<unsigned>;
using Vec2b = Vec2<bool>;
using Vec3f = Vec3<float>;
using Vec3d = Vec3<double>;
using Vec3i = Vec3<int>;
using Vec3u = Vec3<unsigned>;
using Vec3b = Vec3<bool>;
using Vec4f = Vec4<float>;
using Vec4d = Vec4<double>;
using Vec4i = Vec4<int>;
using Vec4u = Vec4<unsigned>;
using Vec4b = Vec4<bool>;
}  // namespace ufo

#endif  // UFO_MATH_DETAIL_VEC_HPP