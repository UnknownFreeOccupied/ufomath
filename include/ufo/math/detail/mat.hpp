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

#ifndef UFO_MATH_DETAIL_MAT_HPP
#define UFO_MATH_DETAIL_MAT_HPP

// STL
#include <cstddef>

namespace ufo
{
template <std::size_t Cols, std::size_t Rows, class T = float>
struct Mat;

template <class T = float>
using Mat2x2 = Mat<2, 2, T>;
template <class T = float>
using Mat3x3 = Mat<3, 3, T>;
template <class T = float>
using Mat4x4 = Mat<4, 4, T>;

template <class T = float>
using Mat2 = Mat2x2<T>;
template <class T = float>
using Mat3 = Mat3x3<T>;
template <class T = float>
using Mat4 = Mat4x4<T>;

using Mat2x2f = Mat2x2<float>;
using Mat2x2d = Mat2x2<double>;
using Mat2x2i = Mat2x2<int>;
using Mat2x2u = Mat2x2<unsigned>;
using Mat3x3f = Mat3x3<float>;
using Mat3x3d = Mat3x3<double>;
using Mat3x3i = Mat3x3<int>;
using Mat3x3u = Mat3x3<unsigned>;
using Mat4x4f = Mat4x4<float>;
using Mat4x4d = Mat4x4<double>;
using Mat4x4i = Mat4x4<int>;
using Mat4x4u = Mat4x4<unsigned>;

using Mat2f = Mat2x2f;
using Mat2d = Mat2x2d;
using Mat2i = Mat2x2i;
using Mat2u = Mat2x2u;
using Mat3f = Mat3x3f;
using Mat3d = Mat3x3d;
using Mat3i = Mat3x3i;
using Mat3u = Mat3x3u;
using Mat4f = Mat4x4f;
using Mat4d = Mat4x4d;
using Mat4i = Mat4x4i;
using Mat4u = Mat4x4u;
}  // namespace ufo

#endif  // UFO_MATH_DETAIL_MAT_HPP