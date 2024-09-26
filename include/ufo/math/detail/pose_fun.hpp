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
#include <vector>

namespace ufo
{
template <std::size_t Dim, class T>
std::ostream& operator<<(std::ostream& out, Pose<Dim, T> const& p)
{
	return out << "Position: " << p.position << ", Orientation: " << p.orientation;
}

template <std::size_t Dim, class T, class U>
[[nodiscard]] Vec<Dim, U> transform(Pose<Dim, T> const& tf, Vec<Dim, U> v)
{
	Mat<Dim + 1, Dim + 1, T> t = static_cast<Mat<Dim + 1, Dim + 1, T>>(tf);
	Vec<Dim + 1, U>          p(v, 1);
	return static_cast<Vec<Dim, U>>(t * p);
}

template <std::size_t Dim, class T, class InputIt, class OutputIt>
OutputIt transform(Pose<Dim, T> const& tf, InputIt first, InputIt last, OutputIt d_first)
{
	return std::transform(first, last, d_first,
	                      [t = static_cast<Mat<Dim + 1, Dim + 1, T>>(tf)](auto e) {
		                      Vec v = e;
		                      // std::cout << "Weee: " << v << std::endl;
		                      using U = typename std::decay_t<decltype(v)>::value_type;
		                      Vec<Dim + 1, U> p(v, 1);
		                      // std::cout << "Peee: " << p << std::endl;
		                      // std::cout << "Teee:\n" << t << std::endl;
		                      static_cast<decltype(v)&>(e) = static_cast<Vec<Dim, U>>(t * p);
		                      // std::cout << "Eeee:\n" << e << std::endl;
		                      return e;
	                      });
}

template <std::size_t Dim, class T, class InputIt>
auto transform(Pose<Dim, T> const& tf, InputIt first, InputIt last)
{
	using V = typename std::iterator_traits<InputIt>::value_type;
	std::vector<V> v;
	v.reserve(std::distance(first, last));
	transform(tf, first, last, std::back_inserter(v));
	return v;
}

template <std::size_t Dim, class T, class Range>
auto transform(Pose<Dim, T> const& tf, Range const& range)
{
	using std::begin;
	using std::end;
	return transform(tf, begin(range), end(range));
}

template <std::size_t Dim, class T, class InputOutputIt>
InputOutputIt transformInPlace(Pose<Dim, T> const& tf, InputOutputIt first,
                               InputOutputIt last)
{
	return transform(tf, first, last, first);
}

template <std::size_t Dim, class T, class Range>
void transformInPlace(Pose<Dim, T> const& tf, Range& range)
{
	using std::begin;
	using std::end;
	transformInPlace(tf, begin(range), end(range));
}

template <
    class ExecutionPolicy, std::size_t Dim, class T, class RandomIt1, class RandomIt2,
    std::enable_if_t<is_execution_policy_v<std::decay_t<ExecutionPolicy>>, bool> = true>
RandomIt2 transform(ExecutionPolicy&& policy, Pose<Dim, T> const& tf, RandomIt1 first,
                    RandomIt1 last, RandomIt2 d_first)
{
	if constexpr (std::is_same_v<execution::sequenced_policy,
	                             std::decay_t<ExecutionPolicy>>) {
		return transform(tf, first, last, d_first);
	}

#if !defined(UFO_TBB) && !defined(UFO_OMP)
	return transform(tf, first, last, d_first);
#endif

	auto trans = [t = static_cast<Mat<Dim + 1, Dim + 1, T>>(tf)](auto e) {
		Vec v = e;
		// std::cout << "Weee: " << v << std::endl;
		using U = typename std::decay_t<decltype(v)>::value_type;
		Vec<Dim + 1, U> p(v, 1);
		// std::cout << "Peee: " << p << std::endl;
		// std::cout << "Teee:\n" << t << std::endl;
		static_cast<decltype(v)&>(e) = static_cast<Vec<Dim, U>>(t * p);
		// std::cout << "Eeee:\n" << e << std::endl;
		return e;
	};

#if defined(UFO_TBB)
	return std::transform(std::forward<ExecutionPolicy>(policy), first, last, d_first,
	                      trans);
#elif defined(UFO_OMP)
	std::size_t size = std::distance(first, last);

#pragma omp parallel for
	for (std::size_t i = 0; i != size; ++i) {
		d_first[i] = trans(first[i]);
	}

	return std::next(d_first, size);
#endif
}

template <
    class ExecutionPolicy, std::size_t Dim, class T, class RandomIt,
    std::enable_if_t<is_execution_policy_v<std::decay_t<ExecutionPolicy>>, bool> = true>
auto transform(ExecutionPolicy&& policy, Pose<Dim, T> const& tf, RandomIt first,
               RandomIt last)
{
	using V = typename std::iterator_traits<RandomIt>::value_type;
	std::vector<V> v(std::distance(first, last));
	transform(std::forward<ExecutionPolicy>(policy), tf, first, last, v.begin());
	return v;
}

template <
    class ExecutionPolicy, std::size_t Dim, class T, class Range,
    std::enable_if_t<is_execution_policy_v<std::decay_t<ExecutionPolicy>>, bool> = true>
auto transform(ExecutionPolicy&& policy, Pose<Dim, T> const& tf, Range& range)
{
	using std::begin;
	using std::end;
	return transform(std::forward<ExecutionPolicy>(policy), tf, begin(range), end(range));
}

template <
    class ExecutionPolicy, std::size_t Dim, class T, class RandomInOutIt,
    std::enable_if_t<is_execution_policy_v<std::decay_t<ExecutionPolicy>>, bool> = true>
RandomInOutIt transformInPlace(ExecutionPolicy&& policy, Pose<Dim, T> const& tf,
                               RandomInOutIt first, RandomInOutIt last)
{
	return transform(std::forward<ExecutionPolicy>(policy), tf, first, last, first);
}

template <
    class ExecutionPolicy, std::size_t Dim, class T, class Range,
    std::enable_if_t<is_execution_policy_v<std::decay_t<ExecutionPolicy>>, bool> = true>
void transformInPlace(ExecutionPolicy&& policy, Pose<Dim, T> const& tf, Range& range)
{
	using std::begin;
	using std::end;
	transformInPlace(std::forward<ExecutionPolicy>(policy), tf, begin(range), end(range));
}

template <std::size_t Dim, class T>
[[nodiscard]] Pose<Dim, T> inverse(Pose<Dim, T> const& p)
{
	// TODO: Implement
}
}  // namespace ufo

#endif  // UFO_MATH_DETAIL_POSE_FUN_HPP