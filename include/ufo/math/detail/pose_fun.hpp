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

#ifndef UFO_MATH_DETAIL_POSE_FUN_HPP
#define UFO_MATH_DETAIL_POSE_FUN_HPP

// UFO
#include <ufo/math/detail/pose.hpp>
#include <ufo/math/mat3x3.hpp>
#include <ufo/math/mat4x4.hpp>
#include <ufo/math/vec2.hpp>
#include <ufo/math/vec3.hpp>
#include <ufo/utility/execution.hpp>

// STL
#include <cstddef>
#include <iterator>
#include <ostream>
#include <type_traits>

namespace ufo
{
template <std::size_t Dim, class T>
std::ostream& operator<<(std::ostream& out, Pose<Dim, T> p)
{
	// TODO: Implement
	return out;
}

template <std::size_t Dim, class T, class U>
[[nodiscard]] Vec<Dim, U> transform(Pose<Dim, T> const& p, Vec<Dim, U> v)
{
	// TODO: Implement
}

template <std::size_t Dim, class T, class InputIt, class OutputIt>
OutputIt transform(Pose<Dim, T> const& p, InputIt first, InputIt last, OutputIt d_first)
{
	// TODO: Correct?

	std::transform(
	    first, last, d_first,
	    [m = static_cast<Mat<Dim + 1, Dim + 1, T>>(p)](auto const& e) { return m * e; });
}

template <std::size_t Dim, class T, class InputIt>
void transform(Pose<Dim, T> const& p, InputIt first, InputIt last)
{
	transform(p, first, last, first);
}

template <std::size_t Dim, class T, class Range>
void transform(Pose<Dim, T> const& p, Range& range)
{
	using std::begin;
	using std::end;
	transform(p, begin(range), end(range));
}

template <
    class ExecutionPolicy, std::size_t Dim, class T, class ForwardIt1, class ForwardIt2,
    std::enable_if_t<is_execution_policy_v<std::decay_t<ExecutionPolicy>>, bool> = true>
ForwardIt2 transform(ExecutionPolicy&& policy, Pose<Dim, T> const& p, ForwardIt1 first,
                     ForwardIt1 last, ForwardIt2 d_first)
{
	// TODO: Correct?

	std::transform(
	    first, last, d_first,
	    [m = static_cast<Mat<Dim + 1, Dim + 1, T>>(p)](auto const& e) { return m * e; });
}

template <
    class ExecutionPolicy, std::size_t Dim, class T, class ForwardIt,
    std::enable_if_t<is_execution_policy_v<std::decay_t<ExecutionPolicy>>, bool> = true>
void transform(ExecutionPolicy&& policy, Pose<Dim, T> const& p, ForwardIt first,
               ForwardIt last)
{
	transform(std::forward<ExecutionPolicy>(policy), p, first, last, first);
}

template <
    class ExecutionPolicy, std::size_t Dim, class T, class Range,
    std::enable_if_t<is_execution_policy_v<std::decay_t<ExecutionPolicy>>, bool> = true>
void transform(ExecutionPolicy&& policy, Pose<Dim, T> const& p, Range& range)
{
	using std::begin;
	using std::end;
	transform(std::forward<ExecutionPolicy>(policy), p, begin(range), end(range));
}

template <std::size_t Dim, class T>
[[nodiscard]] Pose<Dim, T> inverse(Pose<Dim, T> const& p)
{
	// TODO: Implement
}
}  // namespace ufo

#endif  // UFO_MATH_DETAIL_POSE_FUN_HPP