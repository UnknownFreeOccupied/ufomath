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

#ifndef UFO_MATH_DETAIL_TRANSFORM_FUN_HPP
#define UFO_MATH_DETAIL_TRANSFORM_FUN_HPP

// UFO
#include <ufo/execution/execution.hpp>
#include <ufo/math/detail/transform.hpp>
#include <ufo/math/mat3x3.hpp>
#include <ufo/math/mat4x4.hpp>
#include <ufo/math/vec2.hpp>
#include <ufo/math/vec3.hpp>
#include <ufo/utility/type_traits.hpp>

// STL
#include <cstddef>
#include <iterator>
#include <type_traits>
#include <vector>

namespace ufo
{
template <std::size_t Dim, class T>
[[nodiscard]] Vec<Dim, T> transform(Transform<Dim, T> const& t, Vec<Dim, T> const& v)
{
	return t * v;
}

template <std::size_t Dim, class T, class InputIt, class OutputIt>
OutputIt transform(Transform<Dim, T> const& t, InputIt first, InputIt last,
                   OutputIt d_first)
{
	return transform(execution::seq, t, first, last, d_first);
}

template <std::size_t Dim, class T, class InputIt>
[[nodiscard]] auto transform(Transform<Dim, T> const& t, InputIt first, InputIt last)
{
	using V = typename std::iterator_traits<InputIt>::value_type;
	std::vector<V> v;
	v.reserve(std::distance(first, last));
	transform(t, first, last, std::back_inserter(v));
	return v;
}

template <std::size_t Dim, class T, class Range>
[[nodiscard]] auto transform(Transform<Dim, T> const& t, Range const& range)
{
	using std::begin;
	using std::end;
	return transform(t, begin(range), end(range));
}

template <
    class ExecutionPolicy, std::size_t Dim, class T, class RandomIt1, class RandomIt2,
    std::enable_if_t<execution::is_execution_policy_v<ExecutionPolicy>, bool> = true>
RandomIt2 transform(ExecutionPolicy&& policy, Transform<Dim, T> const& t, RandomIt1 first,
                    RandomIt1 last, RandomIt2 d_first)
{
	if constexpr (execution::is_seq_v<ExecutionPolicy>) {
		return std::transform(UFO_PAR_STL_SEQ first, last, d_first,
		                      [&t](auto const& x) { return t * x; });
	} else if constexpr (execution::is_unseq_v<ExecutionPolicy>) {
		return std::transform(UFO_PAR_STL_UNSEQ first, last, d_first,
		                      [&t](auto const& x) { return t * x; });
	} else if constexpr (execution::is_par_v<ExecutionPolicy>) {
		return std::transform(UFO_PAR_STL_PAR first, last, d_first,
		                      [&t](auto const& x) { return t * x; });
	} else if constexpr (execution::is_par_unseq_v<ExecutionPolicy>) {
		return std::transform(UFO_PAR_STL_PAR_UNSEQ first, last, d_first,
		                      [&t](auto const& x) { return t * x; });
	}
#if defined(UFO_PAR_GCD)
	else if constexpr (execution::is_gcd_v<ExecutionPolicy> ||
	                   execution::is_gcd_unseq_v<ExecutionPolicy>) {
		// TODO: Implement
		static_assert(dependent_false_v<ExecutionPolicy>,
		              "Not implemented for the execution policy");
	}
#endif
	else if constexpr (execution::is_tbb_v<ExecutionPolicy> ||
	                   execution::is_tbb_unseq_v<ExecutionPolicy>) {
		// TODO: Implement
		static_assert(dependent_false_v<ExecutionPolicy>,
		              "Not implemented for the execution policy");
	} else if constexpr (execution::is_omp_v<ExecutionPolicy> ||
	                     execution::is_omp_unseq_v<ExecutionPolicy>) {
		std::size_t size = std::distance(first, last);

#pragma omp parallel for
		for (std::size_t i = 0; i != size; ++i) {
			d_first[i] = t * first[i];
		}

		return d_first + size;
	} else {
		static_assert(dependent_false_v<ExecutionPolicy>,
		              "create not implemented for the execution policy");
	}
}

template <
    class ExecutionPolicy, std::size_t Dim, class T, class RandomIt,
    std::enable_if_t<execution::is_execution_policy_v<ExecutionPolicy>, bool> = true>
auto transform(ExecutionPolicy&& policy, Transform<Dim, T> const& t, RandomIt first,
               RandomIt last)
{
	using V = typename std::iterator_traits<RandomIt>::value_type;
	std::vector<V> v(std::distance(first, last));
	transform(std::forward<ExecutionPolicy>(policy), t, first, last, v.begin());
	return v;
}

template <
    class ExecutionPolicy, std::size_t Dim, class T, class Range,
    std::enable_if_t<execution::is_execution_policy_v<ExecutionPolicy>, bool> = true>
auto transform(ExecutionPolicy&& policy, Transform<Dim, T> const& t, Range const& range)
{
	using std::begin;
	using std::end;
	return transform(std::forward<ExecutionPolicy>(policy), t, begin(range), end(range));
}

template <std::size_t Dim, class T, class InputOutputIt>
InputOutputIt transformInPlace(Transform<Dim, T> const& t, InputOutputIt first,
                               InputOutputIt last)
{
	return transform(t, first, last, first);
}

template <std::size_t Dim, class T, class Range>
void transformInPlace(Transform<Dim, T> const& t, Range& range)
{
	using std::begin;
	using std::end;
	transformInPlace(t, begin(range), end(range));
}

template <
    class ExecutionPolicy, std::size_t Dim, class T, class RandomInOutIt,
    std::enable_if_t<execution::is_execution_policy_v<ExecutionPolicy>, bool> = true>
RandomInOutIt transformInPlace(ExecutionPolicy&& policy, Transform<Dim, T> const& t,
                               RandomInOutIt first, RandomInOutIt last)
{
	return transform(std::forward<ExecutionPolicy>(policy), t, first, last, first);
}

template <
    class ExecutionPolicy, std::size_t Dim, class T, class Range,
    std::enable_if_t<execution::is_execution_policy_v<ExecutionPolicy>, bool> = true>
void transformInPlace(ExecutionPolicy&& policy, Transform<Dim, T> const& t, Range& range)
{
	using std::begin;
	using std::end;
	transformInPlace(std::forward<ExecutionPolicy>(policy), t, begin(range), end(range));
}

template <std::size_t Dim, class T>
[[nodiscard]] Transform<Dim, T> inverse(Transform<Dim, T> const& t)
{
	Mat<Dim, Dim, T> inv = transpose(Mat<Dim, Dim, T>(t));
	return Transform<Dim, T>(inv, inv * -t.translation);
}
}  // namespace ufo

#endif  // UFO_MATH_DETAIL_TRANSFORM_FUN_HPP