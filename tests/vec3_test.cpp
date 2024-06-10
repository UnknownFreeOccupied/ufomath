// UFO
#include <ufo/math/vec3.hpp>

// Catch2
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Vec3")
{
	REQUIRE(1.0f == norm(ufo::Vec3f(1, 0, 0)));
	REQUIRE(1.0f == norm(ufo::Vec3f(0, 1, 0)));
	REQUIRE(1.0f == norm(ufo::Vec3f(0, 0, 1)));
}