/*!
 * UFOMap: An Efficient Probabilistic 3D Mapping Framework That Embraces the Unknown
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

#ifndef UFO_MATH_NUMBERS_HPP
#define UFO_MATH_NUMBERS_HPP

#if __cplusplus >= 202002L
#include <numbers>
// C++20 (and later) code
namespace ufo::numbers
{
using namespace std::numbers;
}  // namespace ufo::numbers
#else
// STL
#include <type_traits>

namespace ufo::numbers
{
namespace detail
{
template <class T>
constexpr inline bool False = false;

template <class T>
struct IllFormed {
	static_assert(False<T>,
	              "A program that instantiates a primary template of a mathematical "
	              "constant variable template is ill-formed.");
};
};  // namespace detail

template <class T, class Enable = void>
constexpr inline T e_v = detail::IllFormed<T>{};

template <class T, class Enable = void>
constexpr inline T log2e_v = detail::IllFormed<T>{};

template <class T, class Enable = void>
constexpr inline T log10e_v = detail::IllFormed<T>{};

template <class T, class Enable = void>
constexpr inline T pi_v = detail::IllFormed<T>{};

template <class T, class Enable = void>
constexpr inline T inv_pi_v = detail::IllFormed<T>{};

template <class T, class Enable = void>
constexpr inline T inv_sqrtpi_v = detail::IllFormed<T>{};

template <class T, class Enable = void>
constexpr inline T ln2_v = detail::IllFormed<T>{};

template <class T, class Enable = void>
constexpr inline T ln10_v = detail::IllFormed<T>{};

template <class T, class Enable = void>
constexpr inline T sqrt2_v = detail::IllFormed<T>{};

template <class T, class Enable = void>
constexpr inline T sqrt3_v = detail::IllFormed<T>{};

template <class T, class Enable = void>
constexpr inline T inv_sqrt3_v = detail::IllFormed<T>{};

template <class T, class Enable = void>
constexpr inline T egamma_v = detail::IllFormed<T>{};

template <class T, class Enable = void>
constexpr inline T phi_v = detail::IllFormed<T>{};

template <class T>
constexpr inline T e_v<T, typename std::enable_if_t<std::is_floating_point_v<T>>> =
    2.718281828459045235360287471352662;

template <class T>
constexpr inline T log2e_v<T, typename std::enable_if_t<std::is_floating_point_v<T>>> =
    1.442695040888963407359924681001892;

template <class T>
constexpr inline T log10e_v<T, typename std::enable_if_t<std::is_floating_point_v<T>>> =
    0.434294481903251827651128918916605;

template <class T>
constexpr inline T pi_v<T, typename std::enable_if_t<std::is_floating_point_v<T>>> =
    3.141592653589793238462643383279502;

template <class T>
constexpr inline T inv_pi_v<T, typename std::enable_if_t<std::is_floating_point_v<T>>> =
    0.318309886183790671537767526745028;

template <class T>
constexpr inline T
    inv_sqrtpi_v<T, typename std::enable_if_t<std::is_floating_point_v<T>>> =
        0.564189583547756286948079451560772;

template <class T>
constexpr inline T ln2_v<T, typename std::enable_if_t<std::is_floating_point_v<T>>> =
    0.693147180559945309417232121458176;

template <class T>
constexpr inline T ln10_v<T, typename std::enable_if_t<std::is_floating_point_v<T>>> =
    2.302585092994045684017991454684364;

template <class T>
constexpr inline T sqrt2_v<T, typename std::enable_if_t<std::is_floating_point_v<T>>> =
    1.414213562373095048801688724209698;

template <class T>
constexpr inline T sqrt3_v<T, typename std::enable_if_t<std::is_floating_point_v<T>>> =
    1.732050807568877293527446341505872;

template <class T>
constexpr inline T
    inv_sqrt3_v<T, typename std::enable_if_t<std::is_floating_point_v<T>>> =
        0.577350269189625764509148780501957;

template <class T>
constexpr inline T egamma_v<T, typename std::enable_if_t<std::is_floating_point_v<T>>> =
    0.577215664901532860606512090082402;

template <class T>
constexpr inline T phi_v<T, typename std::enable_if_t<std::is_floating_point_v<T>>> =
    1.618033988749894848204586834365638;

constexpr inline double e          = e_v<double>;
constexpr inline double log2e      = log2e_v<double>;
constexpr inline double log10e     = log10e_v<double>;
constexpr inline double pi         = pi_v<double>;
constexpr inline double inv_pi     = inv_pi_v<double>;
constexpr inline double inv_sqrtpi = inv_sqrtpi_v<double>;
constexpr inline double ln2        = ln2_v<double>;
constexpr inline double ln10       = ln10_v<double>;
constexpr inline double sqrt2      = sqrt2_v<double>;
constexpr inline double sqrt3      = sqrt3_v<double>;
constexpr inline double inv_sqrt3  = inv_sqrt3_v<double>;
constexpr inline double egamma     = egamma_v<double>;
constexpr inline double phi        = phi_v<double>;
}  // namespace ufo::numbers
#endif

#endif  // UFO_MATH_NUMBERS_HPP