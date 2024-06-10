// UFO
#include <ufo/math/mat2x2.hpp>

// Catch2
#include <catch2/catch_test_macros.hpp>

// STL
#include <iostream>

TEST_CASE("Mat2x2")
{
	ufo::Mat2f m(3.123123123f, 1124124.1238f, -1231231.0f, 1231.812904f);
	std::cout << m << std::endl;
}