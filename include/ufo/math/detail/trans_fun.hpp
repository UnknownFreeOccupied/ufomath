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

#ifndef UFO_MATH_DETAIL_TRANS_FUN_HPP
#define UFO_MATH_DETAIL_TRANS_FUN_HPP

// UFO
#include <ufo/math/detail/trans.hpp>
#include <ufo/math/mat3x3.hpp>
#include <ufo/math/mat4x4.hpp>
#include <ufo/math/vec2.hpp>
#include <ufo/math/vec3.hpp>
#include <ufo/utility/execution.hpp>

// STL
#include <cstddef>
#include <iterator>
#include <type_traits>
#include <vector>

namespace ufo
{
template <std::size_t Dim, class T>
[[nodiscard]] Vec<Dim, T> trans(Trans<Dim, T> const& t, Vec<Dim, T> const& v)
{
	return t * v;
}

template <std::size_t Dim, class T, class InputIt, class OutputIt>
OutputIt trans(Trans<Dim, T> const& t, InputIt first, InputIt last, OutputIt d_first)
{
	return std::transform(first, last, d_first, [t = Mat<Dim + 1, Dim + 1, T>(t)](auto e) {
		Vec v = e;
		// std::cout << "Weee: " << v << std::endl;
		using U = typename std::decay_t<decltype(v)>::value_type;
		Vec<Dim + 1, U> v_h(v, U(1));
		// std::cout << "Peee: " << p << std::endl;
		// std::cout << "Teee:\n" << t << std::endl;
		static_cast<decltype(v)&>(e) = static_cast<Vec<Dim, U>>(t * v_h);
		// std::cout << "Eeee:\n" << e << std::endl;
		return e;
	});
}

template <std::size_t Dim, class T, class InputIt>
auto trans(Trans<Dim, T> const& t, InputIt first, InputIt last)
{
	using V = typename std::iterator_traits<InputIt>::value_type;
	std::vector<V> v;
	v.reserve(std::distance(first, last));
	trans(t, first, last, std::back_inserter(v));
	return v;
}

template <std::size_t Dim, class T, class Range>
auto trans(Trans<Dim, T> const& t, Range const& range)
{
	using std::begin;
	using std::end;
	return trans(t, begin(range), end(range));
}

template <std::size_t Dim, class T, class InputOutputIt>
InputOutputIt transInPlace(Trans<Dim, T> const& t, InputOutputIt first,
                           InputOutputIt last)
{
	return trans(t, first, last, first);
}

template <std::size_t Dim, class T, class Range>
void transInPlace(Trans<Dim, T> const& t, Range& range)
{
	using std::begin;
	using std::end;
	transInPlace(t, begin(range), end(range));
}

template <
    class ExecutionPolicy, std::size_t Dim, class T, class RandomIt1, class RandomIt2,
    std::enable_if_t<execution::is_execution_policy_v<ExecutionPolicy>,
                     bool> = true>
RandomIt2 trans(ExecutionPolicy&& policy, Trans<Dim, T> const& t, RandomIt1 first,
                RandomIt1 last, RandomIt2 d_first)
{
	if constexpr (std::is_same_v<execution::sequenced_policy,
	                             std::decay_t<ExecutionPolicy>>) {
		return trans(t, first, last, d_first);
	}

#if !defined(UFO_TBB) && !defined(UFO_OMP)
	return trans(t, first, last, d_first);
#endif

	auto trans = [t = Mat<Dim + 1, Dim + 1, T>(t)](auto e) {
		Vec v = e;
		// std::cout << "Weee: " << v << std::endl;
		using U = typename std::decay_t<decltype(v)>::value_type;
		Vec<Dim + 1, U> v_h(v, 1);
		// std::cout << "Peee: " << p << std::endl;
		// std::cout << "Teee:\n" << t << std::endl;
		static_cast<decltype(v)&>(e) = static_cast<Vec<Dim, U>>(t * v_h);
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
    std::enable_if_t<execution::is_execution_policy_v<ExecutionPolicy>,
                     bool> = true>
auto trans(ExecutionPolicy&& policy, Trans<Dim, T> const& t, RandomIt first,
           RandomIt last)
{
	using V = typename std::iterator_traits<RandomIt>::value_type;
	std::vector<V> v(std::distance(first, last));
	trans(std::forward<ExecutionPolicy>(policy), t, first, last, v.begin());
	return v;
}

template <
    class ExecutionPolicy, std::size_t Dim, class T, class Range,
    std::enable_if_t<execution::is_execution_policy_v<ExecutionPolicy>,
                     bool> = true>
auto trans(ExecutionPolicy&& policy, Trans<Dim, T> const& t, Range& range)
{
	using std::begin;
	using std::end;
	return trans(std::forward<ExecutionPolicy>(policy), t, begin(range), end(range));
}

template <
    class ExecutionPolicy, std::size_t Dim, class T, class RandomInOutIt,
    std::enable_if_t<execution::is_execution_policy_v<ExecutionPolicy>,
                     bool> = true>
RandomInOutIt transInPlace(ExecutionPolicy&& policy, Trans<Dim, T> const& t,
                           RandomInOutIt first, RandomInOutIt last)
{
	return trans(std::forward<ExecutionPolicy>(policy), t, first, last, first);
}

template <
    class ExecutionPolicy, std::size_t Dim, class T, class Range,
    std::enable_if_t<execution::is_execution_policy_v<ExecutionPolicy>,
                     bool> = true>
void transInPlace(ExecutionPolicy&& policy, Trans<Dim, T> const& t, Range& range)
{
	using std::begin;
	using std::end;
	transInPlace(std::forward<ExecutionPolicy>(policy), t, begin(range), end(range));
}

template <std::size_t Dim, class T>
[[nodiscard]] Trans<Dim, T> inverse(Trans<Dim, T> const& t)
{
	Mat<Dim, Dim, T> inv = transpose(Mat<Dim, Dim, T>(t));
	return Trans<Dim, T>(inv, inv * -t.translation);
}
}  // namespace ufo

#endif  // UFO_MATH_DETAIL_TRANS_FUN_HPP