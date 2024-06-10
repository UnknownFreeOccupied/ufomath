/*!
 * UFOMap: An Efficient Probabilistic 3D Mapping Framework That Embraces the Unknown
 *
 * @author Daniel Duberg (dduberg@kth.se)
 * @see https://github.com/UnknownFreeOccupied/ufomap
 * @version 1.0
 * @date 2022-05-13
 *
 * @copyright Copyright (c) 2022, Daniel Duberg, KTH Royal Institute of Technology
 *
 * BSD 3-Clause License
 *
 * Copyright (c) 2022, Daniel Duberg, KTH Royal Institute of Technology
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *     list of conditions and the following disclaimer.
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
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef UFO_MATH_UTILITY_HPP
#define UFO_MATH_UTILITY_HPP

// STL
#include <type_traits>

namespace ufo
{
template <class T>
[[nodiscard]] constexpr int sgn(T val) noexcept
{
	if constexpr (std::is_unsigned_v<T>) {
		return T(0) < val;
	} else {
		return (T(0) < val) - (val < T(0));
	}
}

template <class T>
[[nodiscard]] constexpr T radians(T degrees) noexcept
{
	// returns degrees * (pi / 180)
	if constexpr (std::is_same_v<T, long double>) {
		return degrees *
		       static_cast<T>(
		           0.0174532925199432957692369076848861271344287188854172545609719144L);
	} else {
		return degrees *
		       static_cast<T>(
		           0.0174532925199432957692369076848861271344287188854172545609719144);
	}
}

template <class T>
[[nodiscard]] constexpr T degrees(T radians) noexcept
{
	// returns radians * (180 / pi)
	if constexpr (std::is_same_v<T, long double>) {
		return radians *
		       static_cast<T>(
		           57.295779513082320876798154814105170332405472466564321549160243861L);
	} else {
		return radians *
		       static_cast<T>(
		           57.295779513082320876798154814105170332405472466564321549160243861);
	}
}

template <class T>
[[nodiscard]] constexpr T ipow(T base, int exp)
{
	T result = static_cast<T>(sgn(base));
	for (int e = 0 <= exp ? exp : -exp; 0 != e; --e) {
		result *= base;
	}
	return 0 <= exp ? result : T(1) / result;
}
}  // namespace ufo

#endif  // UFO_MATH_UTILITY_HPP