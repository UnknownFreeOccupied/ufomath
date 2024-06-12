// UFO
#include <cmath>
#include <iostream>
#include <ufo/math/vec3.hpp>

// Catch2
#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("[Vec3f] [operator==] Equality operator")
{
	ufo::Vec3f vec1(1.5f, 2.0f, 3.5f);
	ufo::Vec3f vec2(1.5f, 2.0f, 3.5f);
	REQUIRE(equal(ufo::Vec3b(true), vec1 == vec2));
}

TEST_CASE("[Vec3f] [operator!=] Inequality operator")
{
	ufo::Vec3f vec1(1.5f, 3.0f, 4.0f);
	ufo::Vec3f vec2(1.5f, 2.0f, 4.0f);
	REQUIRE(equal(ufo::Vec3b(false, true, false), vec1 != vec2));
}

TEST_CASE("[Vec3f] [operator+] Addition operator")
{
	ufo::Vec3f vec1(1.0f, 2.0f, 3.0f);
	ufo::Vec3f vec2(3.0f, 4.0f, 5.0f);
	float      scalar = 2.0f;

	SECTION("Addition (+) operator with Vec3f and Vec3f")
	{
		ufo::Vec3f result = vec1 + vec2;
		REQUIRE(result.x == 4.0f);
		REQUIRE(result.y == 6.0f);
		REQUIRE(result.z == 8.0f);
	}

	SECTION("Addition (+) operator with Vec3f and scalar from left")
	{
		ufo::Vec3f result = vec1 + scalar;
		REQUIRE(result.x == 3.0f);
		REQUIRE(result.y == 4.0f);
		REQUIRE(result.z == 5.0f);
	}

	SECTION("Addition (+) operator with Vec3f and scalar from right")
	{
		ufo::Vec3f result = scalar + vec1;
		REQUIRE(result.x == 3.0f);
		REQUIRE(result.y == 4.0f);
		REQUIRE(result.z == 5.0f);
	}
}

TEST_CASE("[Vec3f] [operator-] Subtraction operator")
{
	ufo::Vec3f vec1(1.0f, 2.0f, 3.0f);
	ufo::Vec3f vec2(3.0f, 4.0f, 5.0f);
	float      scalar = 2.0f;

	SECTION("Subtraction (-) operator with Vec3f and Vec3f")
	{
		ufo::Vec3f result = vec1 - vec2;
		REQUIRE(result.x == -2.0f);
		REQUIRE(result.y == -2.0f);
		REQUIRE(result.z == -2.0f);
	}

	SECTION("Subtraction (-) operator with Vec3f and scalar from left")
	{
		ufo::Vec3f result = vec1 - scalar;
		REQUIRE(result.x == -1.0f);
		REQUIRE(result.y == 0.0f);
		REQUIRE(result.z == 1.0f);
	}

	SECTION("Subtraction (-) operator with scalar and Vec3f from right")
	{
		ufo::Vec3f result = scalar - vec1;
		REQUIRE(result.x == 1.0f);
		REQUIRE(result.y == 0.0f);
		REQUIRE(result.z == -1.0f);
	}

	SECTION("Unary negation")
	{
		ufo::Vec3f result = -vec1;
		REQUIRE(result.x == -1.0f);
		REQUIRE(result.y == -2.0f);
		REQUIRE(result.z == -3.0f);
	}
}

TEST_CASE("[Vec3f] [operator*] Multiplication operator")
{
	ufo::Vec3f vec(1.0f, 2.0f, 3.0f);
	float      scalar = 2.0f;

	SECTION("Multiplication (*) operator with scalar from left")
	{
		ufo::Vec3f result = vec * scalar;
		REQUIRE(result.x == 2.0f);
		REQUIRE(result.y == 4.0f);
		REQUIRE(result.z == 6.0f);
	}

	SECTION("Multiplication of zero vector with scalar from left")
	{
		ufo::Vec3f zero_vec(0.0f, 0.0f, 0.0f);
		ufo::Vec3f result = zero_vec * scalar;
		REQUIRE(result.x == 0.0f);
		REQUIRE(result.y == 0.0f);
		REQUIRE(result.z == 0.0f);
	}

	SECTION("Multiplication of negative scalar with Vec3f from left")
	{
		float      negative_scalar = -2.0f;
		ufo::Vec3f result          = vec * negative_scalar;
		REQUIRE(result.x == -2.0f);
		REQUIRE(result.y == -4.0f);
		REQUIRE(result.z == -6.0f);
	}

	SECTION("Multiplication (*) operator with scalar from right")
	{
		ufo::Vec3f result = scalar * vec;
		REQUIRE(result.x == 2.0f);
		REQUIRE(result.y == 4.0f);
		REQUIRE(result.z == 6.0f);
	}

	SECTION("Multiplication of zero scalar with Vec3f from right")
	{
		float      zero_scalar = 0.0f;
		ufo::Vec3f result      = zero_scalar * vec;
		REQUIRE(result.x == 0.0f);
		REQUIRE(result.y == 0.0f);
		REQUIRE(result.z == 0.0f);
	}

	SECTION("Multiplication of negative scalar with Vec3f from right")
	{
		float      negative_scalar = -2.0f;
		ufo::Vec3f result          = negative_scalar * vec;
		REQUIRE(result.x == -2.0f);
		REQUIRE(result.y == -4.0f);
		REQUIRE(result.z == -6.0f);
	}

	SECTION("Multiplication with Vec3f")
	{
		ufo::Vec3f v1(-2.5f, 3.1f, 4.2f);
		ufo::Vec3f v2(2.0f, 3.0f, 4.0f);
		ufo::Vec3f result = v1 * v2;
		REQUIRE(result.x == Catch::Approx(-5.0f));
		REQUIRE(result.y == Catch::Approx(9.3f));
		REQUIRE(result.z == Catch::Approx(16.8f));
	}
}

TEST_CASE("[Vec3f] [operator/] Division operator")
{
	ufo::Vec3f vec1(4.0f, 6.0f, 8.0f);
	ufo::Vec3f vec2(2.0f, 3.0f, 4.0f);
	float      scalar = 2.0f;

	SECTION("Division (/) operator with Vec3f and Vec3f")
	{
		ufo::Vec3f result = vec1 / vec2;
		REQUIRE(result.x == 2.0f);
		REQUIRE(result.y == 2.0f);
		REQUIRE(result.z == 2.0f);
	}

	SECTION("Division (/) operator with Vec3f and scalar from left")
	{
		ufo::Vec3f result = vec1 / scalar;
		REQUIRE(result.x == 2.0f);
		REQUIRE(result.y == 3.0f);
		REQUIRE(result.z == 4.0f);
	}

	SECTION("Division (/) operator with Vec3f and zero from left")
	{
		float      zero_scalar = 0.0f;
		ufo::Vec3f result      = vec1 / zero_scalar;
		REQUIRE(std::isinf(result.x));  // Division by zero results in Inf
		REQUIRE(std::isinf(result.y));  // Division by zero results in Inf
		REQUIRE(std::isinf(result.z));  // Division by zero results in Inf
	}

	SECTION("Division (/) operator with scalar and Vec3f from right")
	{
		ufo::Vec3f result = scalar / vec1;
		REQUIRE(result.x == 2.0f / 4.0f);
		REQUIRE(result.y == 2.0f / 6.0f);
		REQUIRE(result.z == 2.0f / 8.0f);
	}

	SECTION("Division (/) operator with division by zero")
	{
		ufo::Vec3f zero_vec(0.0f, 0.0f, 0.0f);
		ufo::Vec3f result = scalar / zero_vec;
		REQUIRE(std::isinf(result.x));  // Division by zero results in Inf
		REQUIRE(std::isinf(result.y));  // Division by zero results in Inf
		REQUIRE(std::isinf(result.z));  // Division by zero results in Inf
	}
}

TEST_CASE("[Vec3f] [operator+=] Compound Addition operator")
{
	ufo::Vec3f vec(1.0f, 2.0f, 3.0f);
	ufo::Vec3f other_vec(3.0f, 4.0f, 5.0f);
	float      scalar = 2.0f;

	SECTION("Compound addition (+=) operator with Vec3f")
	{
		vec += other_vec;
		REQUIRE(vec.x == 4.0f);
		REQUIRE(vec.y == 6.0f);
		REQUIRE(vec.z == 8.0f);
	}

	SECTION("Compound addition (+=) operator with scalar")
	{
		vec += scalar;
		REQUIRE(vec.x == 3.0f);
		REQUIRE(vec.y == 4.0f);
		REQUIRE(vec.z == 5.0f);
	}
}

TEST_CASE("[Vec3f] [operator-=] Compound Subtraction operator")
{
	ufo::Vec3f vec(1.0f, 5.0f, 8.0f);
	ufo::Vec3f other_vec(3.0f, 4.0f, 5.0f);
	float      scalar = 2.0f;

	SECTION("Compound subtraction (-=) operator with Vec3f")
	{
		vec -= other_vec;
		REQUIRE(vec.x == -2.0f);
		REQUIRE(vec.y == 1.0f);
		REQUIRE(vec.z == 3.0f);
	}

	SECTION("Compound subtraction (-=) operator with scalar")
	{
		vec -= scalar;
		REQUIRE(vec.x == -1.0f);
		REQUIRE(vec.y == 3.0f);
		REQUIRE(vec.z == 6.0f);
	}
}

TEST_CASE("[Vec3f] [operator*=] Compound Multiplication operator")
{
	ufo::Vec3f vec(1.0f, 5.0f, 8.0f);
	ufo::Vec3f other_vec(3.0f, 4.0f, 5.0f);
	float      scalar = 2.0f;

	SECTION("Compound multiplication (*=) operator with Vec3f")
	{
		vec *= other_vec;
		REQUIRE(vec.x == 3.0f);
		REQUIRE(vec.y == 20.0f);
		REQUIRE(vec.z == 40.0f);
	}

	SECTION("Compound multiplication (*=) operator with scalar")
	{
		vec *= scalar;
		REQUIRE(vec.x == 2.0f);
		REQUIRE(vec.y == 10.0f);
		REQUIRE(vec.z == 16.0f);
	}
}

TEST_CASE("[Vec3f] [operator/=] Compound division operator")
{
	ufo::Vec3f vec(6.0f, 10.0f, 15.0f);
	ufo::Vec3f other_vec(3.0f, 2.0f, 3.0f);
	float      scalar = 2.0f;

	SECTION("Compound division (/=) operator with Vec3f")
	{
		vec /= other_vec;
		REQUIRE(vec.x == 2.0f);
		REQUIRE(vec.y == 5.0f);
		REQUIRE(vec.z == 5.0f);
	}

	SECTION("Compound division (/=) operator with scalar")
	{
		vec /= scalar;
		REQUIRE(vec.x == 3.0f);
		REQUIRE(vec.y == 5.0f);
		REQUIRE(vec.z == 7.5f);
	}
}

TEST_CASE("[Vec3f] [dot] Dot product")
{
	SECTION("Dot product of zero vectors")
	{
		ufo::Vec3f v1(0.0f, 0.0f, 0.0f);
		ufo::Vec3f v2(0.0f, 0.0f, 0.0f);
		REQUIRE(dot(v1, v2) == Catch::Approx(0.0f));
	}

	SECTION("Dot product with one zero vector")
	{
		ufo::Vec3f v1(1.0f, 2.0f, 3.0f);
		ufo::Vec3f v2(0.0f, 0.0f, 0.0f);
		REQUIRE(dot(v1, v2) == Catch::Approx(0.0f));
	}

	SECTION("Dot product of orthogonal vectors")
	{
		ufo::Vec3f v1(1.0f, 0.0f, 0.0f);
		ufo::Vec3f v2(0.0f, 1.0f, 0.0f);
		REQUIRE(dot(v1, v2) == Catch::Approx(0.0f));
	}

	SECTION("Dot product of parallel vectors")
	{
		ufo::Vec3f v1(1.0f, 1.0f, 1.0f);
		ufo::Vec3f v2(2.0f, 2.0f, 2.0f);
		REQUIRE(dot(v1, v2) == Catch::Approx(6.0f));
	}

	SECTION("Dot product with negative components")
	{
		ufo::Vec3f v1(1.0f, -1.0f, 1.0f);
		ufo::Vec3f v2(-1.0f, 1.0f, -1.0f);
		REQUIRE(dot(v1, v2) == Catch::Approx(-3.0f));
	}

	SECTION("Dot product of arbitrary vectors")
	{
		ufo::Vec3f v1(3.0f, 4.0f, 5.0f);
		ufo::Vec3f v2(1.0f, 2.0f, 3.0f);
		REQUIRE(dot(v1, v2) == Catch::Approx(26.0f));
	}
}

TEST_CASE("[Vec3f] [operator[]]")
{
	ufo::Vec3f v(1.5f, 4.3f, 2.1f);
	REQUIRE(v[0] == Catch::Approx(1.5f));
	REQUIRE(v[1] == Catch::Approx(4.3f));
	REQUIRE(v[2] == Catch::Approx(2.1f));

	ufo::Vec3f const cv(2.3f, 0.1f, 5.2f);
	REQUIRE(cv[0] == Catch::Approx(2.3f));
	REQUIRE(cv[1] == Catch::Approx(0.1f));
	REQUIRE(cv[2] == Catch::Approx(5.2f));
}

TEST_CASE("[Vec3f] [norm]")
{
	SECTION("Norm of a zero vector")
	{
		ufo::Vec3f v(0.0f, 0.0f, 0.0f);
		REQUIRE(norm(v) == Catch::Approx(0.0f));
	}

	SECTION("Norm of a unit vector along x-axis")
	{
		ufo::Vec3f v(1.0f, 0.0f, 0.0f);
		REQUIRE(norm(v) == Catch::Approx(1.0f));
	}

	SECTION("Norm of a unit vector along y-axis")
	{
		ufo::Vec3f v(0.0f, 1.0f, 0.0f);
		REQUIRE(norm(v) == Catch::Approx(1.0f));
	}

	SECTION("Norm of a unit vector along z-axis")
	{
		ufo::Vec3f v(0.0f, 0.0f, 1.0f);
		REQUIRE(norm(v) == Catch::Approx(1.0f));
	}

	SECTION("Norm of a vector with equal components")
	{
		ufo::Vec3f v(1.0f, 1.0f, 1.0f);
		REQUIRE(norm(v) == Catch::Approx(std::sqrt(3.0f)));
	}

	SECTION("Norm of a vector with negative components")
	{
		ufo::Vec3f v(-3.0f, -4.0f, -5.0f);
		REQUIRE(norm(v) == Catch::Approx(std::sqrt(50)));
	}

	SECTION("Norm of an arbitrary vector")
	{
		ufo::Vec3f v(3.0f, 4.0f, 5.0f);
		REQUIRE(norm(v) == Catch::Approx(std::sqrt(50)));
	}
}

TEST_CASE("Vec3f")
{
	REQUIRE(1.0f == norm(ufo::Vec3f(1, 0, 0)));
	REQUIRE(1.0f == norm(ufo::Vec3f(0, 1, 0)));
	REQUIRE(1.0f == norm(ufo::Vec3f(0, 0, 1)));

	REQUIRE(1.0f == norm(ufo::Vec3f(-1, 0, 0)));
	REQUIRE(1.0f == norm(ufo::Vec3f(0, -1, 0)));
	REQUIRE(1.0f == norm(ufo::Vec3f(0, 0, -1)));

	ufo::Vec3f v1(1, 2, 3);
	ufo::Vec3f v2(v1);
	REQUIRE(1.0f == v2.x);
	REQUIRE(2.0f == v2.y);
	REQUIRE(3.0f == v2.z);

	ufo::Vec3f v3(2.3f, 3, 6.1f);
	ufo::Vec3f cross_test = cross(v1, v3);
	ufo::Vec3f cross_expected(3.2f, 0.8f, -1.6f);
}

TEST_CASE("Vec3f cross product")
{
	// Test case 1: Cross product of orthogonal vectors
	SECTION("Cross product of orthogonal vectors")
	{
		ufo::Vec3f a(1.0, 0.0, 0.0);
		ufo::Vec3f b(0.0, 1.0, 0.0);
		ufo::Vec3f result = cross(a, b);
		ufo::Vec3f expected(0.0, 0.0, 1.0);
		REQUIRE(equal(result, expected));
	}

	// Test case 2: Cross product of parallel vectors (should result in zero vector)
	SECTION("Cross product of parallel vectors")
	{
		ufo::Vec3f a(2.0, 3.0, 4.0);
		ufo::Vec3f b(4.0, 6.0, 8.0);
		ufo::Vec3f result = cross(a, b);
		ufo::Vec3f expected(0.0, 0.0, 0.0);
		REQUIRE(equal(result, expected));
	}

	// Test case 3: Cross product of vectors with negative components
	SECTION("Cross product of vectors with negative components")
	{
		ufo::Vec3f a(-1.0, 2.0, -3.0);
		ufo::Vec3f b(4.0, -5.0, 6.0);
		ufo::Vec3f result = cross(a, b);
		ufo::Vec3f expected(-3, -6, -3);
		REQUIRE(equal(result, expected));
	}
}

TEST_CASE("[Vec3f] [normalize]")
{
	SECTION("Normalize zero vector")
	{
		ufo::Vec3f v(0.0f, 0.0f, 0.0f);
		auto       v1 = normalize(v);
		// TODO what should happen when normalizing zero vector
	}

	SECTION("Normalize unit vector along x-axis")
	{
		ufo::Vec3f v(1.0f, 0.0f, 0.0f);
		v = normalize(v);
		REQUIRE(v.x == Catch::Approx(1.0f));
		REQUIRE(v.y == Catch::Approx(0.0f));
		REQUIRE(v.z == Catch::Approx(0.0f));
	}

	SECTION("Normalize unit vector along y-axis")
	{
		ufo::Vec3f v(0.0f, 1.0f, 0.0f);
		v = normalize(v);
		REQUIRE(v.x == Catch::Approx(0.0f));
		REQUIRE(v.y == Catch::Approx(1.0f));
		REQUIRE(v.z == Catch::Approx(0.0f));
	}

	SECTION("Normalize unit vector along z-axis")
	{
		ufo::Vec3f v(0.0f, 0.0f, 1.0f);
		v = normalize(v);
		REQUIRE(v.x == Catch::Approx(0.0f));
		REQUIRE(v.y == Catch::Approx(0.0f));
		REQUIRE(v.z == Catch::Approx(1.0f));
	}

	SECTION("Normalize arbitrary vector")
	{
		ufo::Vec3f v(3.0f, 4.0f, 5.0f);
		v            = normalize(v);
		float length = std::sqrt(3.0f * 3.0f + 4.0f * 4.0f + 5.0f * 5.0f);
		REQUIRE(v.x == Catch::Approx(3.0f / length));
		REQUIRE(v.y == Catch::Approx(4.0f / length));
		REQUIRE(v.z == Catch::Approx(5.0f / length));
	}
}

TEST_CASE("[Vec3f][distance]")
{
	SECTION("Distance between identical vectors")
	{
		ufo::Vec3f v1(1.0f, 2.0f, 3.0f);
		ufo::Vec3f v2(1.0f, 2.0f, 3.0f);
		REQUIRE(distance(v1, v2) == Catch::Approx(0.0f));
	}

	SECTION("Distance between zero vectors")
	{
		ufo::Vec3f v1(0.0f, 0.0f, 0.0f);
		ufo::Vec3f v2(0.0f, 0.0f, 0.0f);
		REQUIRE(distance(v1, v2) == Catch::Approx(0.0f));
	}

	SECTION("Distance between vectors with one zero component")
	{
		ufo::Vec3f v1(1.0f, 0.0f, 0.0f);
		ufo::Vec3f v2(0.0f, 1.0f, 1.0f);
		REQUIRE(distance(v1, v2) == Catch::Approx(std::sqrt(3.0f)));
	}

	SECTION("Distance between arbitrary vectors")
	{
		ufo::Vec3f v1(1.0f, 2.0f, 3.0f);
		ufo::Vec3f v2(4.0f, 6.0f, 8.0f);
		REQUIRE(distance(v1, v2) == Catch::Approx(sqrt(50.0f)));
	}
}

TEST_CASE("[Vec3f] [size]")
{
	ufo::Vec3f v(1, 2, 3);
	REQUIRE(v.size() == 3);
}

TEST_CASE("[Vec3f][min]")
{
	SECTION("Minimum of zero vector")
	{
		ufo::Vec3f v(0.0f, 0.0f, 0.0f);
		auto       result = min(v);
		REQUIRE(result == Catch::Approx(0.0f));
	}

	SECTION("Minimum of vector with equal components")
	{
		ufo::Vec3f v(2.0f, 2.0f, 2.0f);
		auto       result = min(v);
		REQUIRE(result == Catch::Approx(2.0f));
	}

	SECTION("Minimum of arbitrary vector")
	{
		ufo::Vec3f v(3.0f, 1.5f, 4.0f);
		auto       result = min(v);
		REQUIRE(result == Catch::Approx(1.5f));
	}

	SECTION("Minimum of vector with negative components")
	{
		ufo::Vec3f v(-2.0f, -4.0f, -1.0f);
		auto       result = min(v);
		REQUIRE(result == Catch::Approx(-4.0f));
	}
}

TEST_CASE("[Vec3f][max]")
{
	SECTION("Maximum of zero vector")
	{
		ufo::Vec3f v(0.0f, 0.0f, 0.0f);
		auto       result = max(v);
		REQUIRE(result == Catch::Approx(0.0f));
	}

	SECTION("Maximum of vector with equal components")
	{
		ufo::Vec3f v(2.0f, 2.0f, 2.0f);
		auto       result = max(v);
		REQUIRE(result == Catch::Approx(2.0f));
	}

	SECTION("Maximum of arbitrary vector")
	{
		ufo::Vec3f v(3.0f, 4.5f, 1.5f);
		auto       result = max(v);
		REQUIRE(result == Catch::Approx(4.5f));
	}

	SECTION("Maximum of vector with negative components")
	{
		ufo::Vec3f v(-2.0f, -4.0f, -1.0f);
		auto       result = max(v);
		REQUIRE(result == Catch::Approx(-1.0f));
	}
}

TEST_CASE("[Vec3f][minElementIndex]")
{
	SECTION("Minimum element index of zero vector")
	{
		ufo::Vec3f v(0.0f, 0.0f, 0.0f);
		auto       result = minIndex(v);
		REQUIRE((0 == result || 1 == result || 2 == result));
	}

	SECTION("Minimum element index of vector with equal components")
	{
		ufo::Vec3f v(2.0f, 2.0f, 2.0f);
		auto       result = minIndex(v);
		REQUIRE((0 == result || 1 == result || 2 == result));
	}

	SECTION("Minimum element index of arbitrary vector")
	{
		ufo::Vec3f v(3.0f, 1.5f, 4.0f);
		auto       result = minIndex(v);
		REQUIRE(1 == result);
	}

	SECTION("Minimum element index of vector with negative components")
	{
		ufo::Vec3f v(-2.0f, -4.0f, -10.0f);
		auto       result = minIndex(v);
		REQUIRE(2 == result);
	}
}

TEST_CASE("[Vec3f][maxElementIndex]")
{
	SECTION("Maximum element index of zero vector")
	{
		ufo::Vec3f v(0.0f, 0.0f, 0.0f);
		auto       result = maxIndex(v);
		REQUIRE((0 == result || 1 == result || 2 == result));
	}

	SECTION("Maximum element index of vector with equal components")
	{
		ufo::Vec3f v(2.0f, 2.0f, 2.0f);
		auto       result = maxIndex(v);
		REQUIRE((0 == result || 1 == result || 2 == result));
	}

	SECTION("Maximum element index of arbitrary vector")
	{
		ufo::Vec3f v(3.0f, 4.5f, 1.5f);
		auto       result = maxIndex(v);
		REQUIRE(1 == result);
	}

	SECTION("Maximum of vector with negative components")
	{
		ufo::Vec3f v(-2.0f, -4.0f, -1.0f);
		auto       result = maxIndex(v);
		REQUIRE(2 == result);
	}
}

TEST_CASE("[Vec3f][ceil]")
{
	SECTION("Ceiling of zero vector")
	{
		ufo::Vec3f v(0.0f, 0.0f, 0.0f);
		ufo::Vec3f result = ceil(v);
		REQUIRE(result.x == Catch::Approx(0.0f));
		REQUIRE(result.y == Catch::Approx(0.0f));
		REQUIRE(result.z == Catch::Approx(0.0f));
	}

	SECTION("Ceiling of positive components")
	{
		ufo::Vec3f v(1.5f, 2.7f, 3.1f);
		ufo::Vec3f result = ceil(v);
		REQUIRE(result.x == Catch::Approx(2.0f));
		REQUIRE(result.y == Catch::Approx(3.0f));
		REQUIRE(result.z == Catch::Approx(4.0f));
	}

	SECTION("Ceiling of negative components")
	{
		ufo::Vec3f v(-1.5f, -2.7f, -3.1f);
		ufo::Vec3f result = ceil(v);
		REQUIRE(result.x == Catch::Approx(-1.0f));
		REQUIRE(result.y == Catch::Approx(-2.0f));
		REQUIRE(result.z == Catch::Approx(-3.0f));
	}

	SECTION("Ceiling of mixed components")
	{
		ufo::Vec3f v(1.2f, -3.8f, 2.5f);
		ufo::Vec3f result = ceil(v);
		REQUIRE(result.x == Catch::Approx(2.0f));
		REQUIRE(result.y == Catch::Approx(-3.0f));
		REQUIRE(result.z == Catch::Approx(3.0f));
	}

	SECTION("Ceiling of mixed components (const)")
	{
		ufo::Vec3f const v(1.2f, -3.8f, 2.5f);
		ufo::Vec3f       result = ceil(v);
		REQUIRE(result.x == Catch::Approx(2.0f));
		REQUIRE(result.y == Catch::Approx(-3.0f));
		REQUIRE(result.z == Catch::Approx(3.0f));
	}
}

TEST_CASE("[Vec3f][floor]")
{
	SECTION("Floor of zero vector")
	{
		ufo::Vec3f v(0.0f, 0.0f, 0.0f);
		ufo::Vec3f result = floor(v);
		REQUIRE(result.x == Catch::Approx(0.0f));
		REQUIRE(result.y == Catch::Approx(0.0f));
		REQUIRE(result.z == Catch::Approx(0.0f));
	}

	SECTION("Floor of positive components")
	{
		ufo::Vec3f v(1.5f, 2.7f, 3.1f);
		ufo::Vec3f result = floor(v);
		REQUIRE(result.x == Catch::Approx(1.0f));
		REQUIRE(result.y == Catch::Approx(2.0f));
		REQUIRE(result.z == Catch::Approx(3.0f));
	}

	SECTION("Floor of negative components")
	{
		ufo::Vec3f v(-1.5f, -2.7f, -3.1f);
		ufo::Vec3f result = floor(v);
		REQUIRE(result.x == Catch::Approx(-2.0f));
		REQUIRE(result.y == Catch::Approx(-3.0f));
		REQUIRE(result.z == Catch::Approx(-4.0f));
	}

	SECTION("Floor of mixed components")
	{
		ufo::Vec3f v(1.2f, -3.8f, 2.5f);
		ufo::Vec3f result = floor(v);
		REQUIRE(result.x == Catch::Approx(1.0f));
		REQUIRE(result.y == Catch::Approx(-4.0f));
		REQUIRE(result.z == Catch::Approx(2.0f));
	}

	SECTION("Floor of mixed components (const)")
	{
		ufo::Vec3f const v(1.2f, -3.8f, 2.5f);
		ufo::Vec3f       result = floor(v);
		REQUIRE(result.x == Catch::Approx(1.0f));
		REQUIRE(result.y == Catch::Approx(-4.0f));
		REQUIRE(result.z == Catch::Approx(2.0f));
	}
}

TEST_CASE("[Vec3f][trunc]")
{
	SECTION("Truncate of zero vector")
	{
		ufo::Vec3f v(0.0f, 0.0f, 0.0f);
		ufo::Vec3f result = trunc(v);
		REQUIRE(result.x == Catch::Approx(0.0f));
		REQUIRE(result.y == Catch::Approx(0.0f));
		REQUIRE(result.z == Catch::Approx(0.0f));
	}

	SECTION("Truncate of positive components")
	{
		ufo::Vec3f v(1.5f, 2.7f, 3.9f);
		ufo::Vec3f result = trunc(v);
		REQUIRE(result.x == Catch::Approx(1.0f));
		REQUIRE(result.y == Catch::Approx(2.0f));
		REQUIRE(result.z == Catch::Approx(3.0f));
	}

	SECTION("Truncate of negative components")
	{
		ufo::Vec3f v(-1.5f, -2.7f, -3.9f);
		ufo::Vec3f result = trunc(v);
		REQUIRE(result.x == Catch::Approx(-1.0f));
		REQUIRE(result.y == Catch::Approx(-2.0f));
		REQUIRE(result.z == Catch::Approx(-3.0f));
	}

	SECTION("Truncate of mixed components")
	{
		ufo::Vec3f v(1.2f, -3.8f, 2.5f);
		ufo::Vec3f result = trunc(v);
		REQUIRE(result.x == Catch::Approx(1.0f));
		REQUIRE(result.y == Catch::Approx(-3.0f));
		REQUIRE(result.z == Catch::Approx(2.0f));
	}

	SECTION("Truncate of mixed components (const)")
	{
		ufo::Vec3f const v(1.2f, -3.8f, 2.5f);
		ufo::Vec3f       result = trunc(v);
		REQUIRE(result.x == Catch::Approx(1.0f));
		REQUIRE(result.y == Catch::Approx(-3.0f));
		REQUIRE(result.z == Catch::Approx(2.0f));
	}
}

TEST_CASE("[Vec3f][round]")
{
	SECTION("Rounding of zero vector")
	{
		ufo::Vec3f v(0.0f, 0.0f, 0.0f);
		ufo::Vec3f result = round(v);
		REQUIRE(result.x == Catch::Approx(0.0f));
		REQUIRE(result.y == Catch::Approx(0.0f));
		REQUIRE(result.z == Catch::Approx(0.0f));
	}

	SECTION("Rounding of positive components")
	{
		ufo::Vec3f v(1.5f, 2.7f, 3.1f);
		ufo::Vec3f result = round(v);
		REQUIRE(result.x == Catch::Approx(2.0f));
		REQUIRE(result.y == Catch::Approx(3.0f));
		REQUIRE(result.z == Catch::Approx(3.0f));
	}

	SECTION("Rounding of negative components")
	{
		ufo::Vec3f v(-1.5f, -2.7f, -3.1f);
		ufo::Vec3f result = round(v);
		REQUIRE(result.x == Catch::Approx(-2.0f));
		REQUIRE(result.y == Catch::Approx(-3.0f));
		REQUIRE(result.z == Catch::Approx(-3.0f));
	}

	SECTION("Rounding of mixed components")
	{
		ufo::Vec3f v(1.2f, -3.8f, 2.5f);
		ufo::Vec3f result = round(v);
		REQUIRE(result.x == Catch::Approx(1.0f));
		REQUIRE(result.y == Catch::Approx(-4.0f));
		REQUIRE(result.z == Catch::Approx(3.0f));
	}

	SECTION("Rounding of mixed components (const)")
	{
		ufo::Vec3f const v(1.2f, -3.8f, 2.5f);
		ufo::Vec3f       result = round(v);
		REQUIRE(result.x == Catch::Approx(1.0f));
		REQUIRE(result.y == Catch::Approx(-4.0f));
		REQUIRE(result.z == Catch::Approx(3.0f));
	}
}

TEST_CASE("[Vec3f][abs]")
{
	SECTION("Absolute value of zero vector")
	{
		ufo::Vec3f v(0.0f, 0.0f, 0.0f);
		ufo::Vec3f result = abs(v);
		REQUIRE(result.x == Catch::Approx(0.0f));
		REQUIRE(result.y == Catch::Approx(0.0f));
		REQUIRE(result.z == Catch::Approx(0.0f));
	}

	SECTION("Absolute value of positive components")
	{
		ufo::Vec3f v(1.5f, 2.7f, 3.6f);
		ufo::Vec3f result = abs(v);
		REQUIRE(result.x == Catch::Approx(1.5f));
		REQUIRE(result.y == Catch::Approx(2.7f));
		REQUIRE(result.z == Catch::Approx(3.6f));
	}

	SECTION("Absolute value of negative components")
	{
		ufo::Vec3f v(-1.5f, -2.7f, -3.6f);
		ufo::Vec3f result = abs(v);
		REQUIRE(result.x == Catch::Approx(1.5f));
		REQUIRE(result.y == Catch::Approx(2.7f));
		REQUIRE(result.z == Catch::Approx(3.6f));
	}

	SECTION("Absolute value of mixed components")
	{
		ufo::Vec3f v(1.2f, -3.8f, 4.4f);
		ufo::Vec3f result = abs(v);
		REQUIRE(result.x == Catch::Approx(1.2f));
		REQUIRE(result.y == Catch::Approx(3.8f));
		REQUIRE(result.z == Catch::Approx(4.4f));
	}

	SECTION("Absolute value of mixed components (const)")
	{
		ufo::Vec3f const v(1.2f, -3.8f, 4.4f);
		ufo::Vec3f       result = abs(v);
		REQUIRE(result.x == Catch::Approx(1.2f));
		REQUIRE(result.y == Catch::Approx(3.8f));
		REQUIRE(result.z == Catch::Approx(4.4f));
	}
}

TEST_CASE("[Vec3f][clamp]")
{
	SECTION("Clamping of zero vector")
	{
		ufo::Vec3f v(0.0f, 0.0f, 0.0f);
		ufo::Vec3f min_val(-1.0f, -1.0f, -1.0f);
		ufo::Vec3f max_val(1.0f, 1.0f, 1.0f);
		ufo::Vec3f result = clamp(v, min_val, max_val);
		REQUIRE(result.x == Catch::Approx(0.0f));
		REQUIRE(result.y == Catch::Approx(0.0f));
		REQUIRE(result.z == Catch::Approx(0.0f));
	}

	SECTION("Clamping of vector within range")
	{
		ufo::Vec3f v(0.5f, -0.5f, 0.5f);
		ufo::Vec3f min_val(-1.0f, -1.0f, -1.0f);
		ufo::Vec3f max_val(1.0f, 1.0f, 1.0f);
		ufo::Vec3f result = clamp(v, min_val, max_val);
		REQUIRE(result.x == Catch::Approx(0.5f));
		REQUIRE(result.y == Catch::Approx(-0.5f));
		REQUIRE(result.z == Catch::Approx(0.5f));
	}

	SECTION("Clamping of vector with components above maximum")
	{
		ufo::Vec3f v(1.5f, 2.5f, 3.5f);
		ufo::Vec3f min_val(-1.0f, -1.0f, -1.0f);
		ufo::Vec3f max_val(1.0f, 1.0f, 1.0f);
		ufo::Vec3f result = clamp(v, min_val, max_val);
		REQUIRE(result.x == Catch::Approx(1.0f));
		REQUIRE(result.y == Catch::Approx(1.0f));
		REQUIRE(result.z == Catch::Approx(1.0f));
	}

	SECTION("Clamping of vector with components below minimum")
	{
		ufo::Vec3f v(-1.5f, -2.5f, -3.5f);
		ufo::Vec3f min_val(-1.0f, -1.0f, -1.0f);
		ufo::Vec3f max_val(1.0f, 1.0f, 1.0f);
		ufo::Vec3f result = clamp(v, min_val, max_val);
		REQUIRE(result.x == Catch::Approx(-1.0f));
		REQUIRE(result.y == Catch::Approx(-1.0f));
		REQUIRE(result.z == Catch::Approx(-1.0f));
	}

	SECTION("Clamping of vector with components below minimum (const)")
	{
		ufo::Vec3f const v(-1.5f, -2.5f, -3.5f);
		ufo::Vec3f const min_val(-1.0f, -1.0f, -1.0f);
		ufo::Vec3f const max_val(1.0f, 1.0f, 1.0f);
		ufo::Vec3f       result = clamp(v, min_val, max_val);
		REQUIRE(result.x == Catch::Approx(-1.0f));
		REQUIRE(result.y == Catch::Approx(-1.0f));
		REQUIRE(result.z == Catch::Approx(-1.0f));
	}
}

TEST_CASE("[Vec3f][cross]")
{
	SECTION("Cross product of perpendicular vectors")
	{
		ufo::Vec3f v1(1.0f, 0.0f, 0.0f);
		ufo::Vec3f v2(0.0f, 1.0f, 0.0f);
		ufo::Vec3f result = cross(v1, v2);
		REQUIRE(result.x == Catch::Approx(0.0f));
		REQUIRE(result.y == Catch::Approx(0.0f));
		REQUIRE(result.z == Catch::Approx(1.0f));
	}

	SECTION("Cross product of collinear vectors")
	{
		ufo::Vec3f v1(1.0f, 2.0f, 3.0f);
		ufo::Vec3f v2(2.0f, 4.0f, 6.0f);  // Scalar multiple of v1
		ufo::Vec3f result = cross(v1, v2);
		// Cross product of collinear vectors is zero
		REQUIRE(result.x == Catch::Approx(0.0f));
		REQUIRE(result.y == Catch::Approx(0.0f));
		REQUIRE(result.z == Catch::Approx(0.0f));
	}

	SECTION("Cross product of arbitrary vectors")
	{
		ufo::Vec3f v1(1.0f, 2.0f, 3.0f);
		ufo::Vec3f v2(4.0f, 5.0f, 6.0f);
		ufo::Vec3f result = cross(v1, v2);
		// Cross product result should be orthogonal to both input vectors
		float dot_v1_result = dot(v1, result);
		float dot_v2_result = dot(v2, result);
		REQUIRE(dot_v1_result == Catch::Approx(0.0f));
		REQUIRE(dot_v2_result == Catch::Approx(0.0f));
	}
}