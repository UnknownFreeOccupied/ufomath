// UFO
#include <iostream>
#include <ufo/math/vec2.hpp>

// Catch2
#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("[Vec2f] [operator==] Equality operator")
{
	ufo::Vec2f vec1(1.5f, 2.0f);
	ufo::Vec2f vec2(1.5f, 2.0f);
	REQUIRE(vec1 == vec2);
}

TEST_CASE("[Vec2f] [operator!=] Inequality operator")
{
	ufo::Vec2f vec1(1.5f, 3.0f);
	ufo::Vec2f vec2(1.5f, 2.0f);
	REQUIRE(vec1 != vec2);
}

TEST_CASE("[Vec2f] [operator+] Addition operator")
{
	ufo::Vec2f vec1(1.0f, 2.0f);
	ufo::Vec2f vec2(3.0f, 4.0f);
	float      scalar = 2.0f;

	SECTION("Addition (+) operator with Vec2f and Vec2f")
	{
		ufo::Vec2f result = vec1 + vec2;
		REQUIRE(result.x == 4.0f);
		REQUIRE(result.y == 6.0f);
	}

	SECTION("Addition (+) operator with Vec2f and scalar from left")
	{
		ufo::Vec2f result = vec1 + scalar;
		REQUIRE(result.x == 3.0f);
		REQUIRE(result.y == 4.0f);
	}

	SECTION("Addition (+) operator with Vec2f and scalar from right")
	{
		ufo::Vec2f result = scalar + vec1;
		REQUIRE(result.x == 3.0f);
		REQUIRE(result.y == 4.0f);
	}
}

TEST_CASE("[Vec2f] [operator-] Subtraction operator")
{
	ufo::Vec2f vec1(1.0f, 2.0f);
	ufo::Vec2f vec2(3.0f, 4.0f);
	float      scalar = 2.0f;

	SECTION("Subtraction (-) operator with Vec2f and Vec2f")
	{
		ufo::Vec2f result = vec1 - vec2;
		REQUIRE(result.x == -2.0f);
		REQUIRE(result.y == -2.0f);
	}

	SECTION("Subtraction (-) operator with Vec2f and scalar from left")
	{
		ufo::Vec2f result = vec1 - scalar;
		REQUIRE(result.x == -1.0f);
		REQUIRE(result.y == 0.0f);
	}

	SECTION("Subtraction (-) operator with scalar and Vec2f from right")
	{
		ufo::Vec2f result = scalar - vec1;
		REQUIRE(result.x == 1.0f);
		REQUIRE(result.y == 0.0f);
	}

	SECTION("Unary negation")
	{
		ufo::Vec2f result = -vec1;
		REQUIRE(result.x == -1.0f);
		REQUIRE(result.y == -2.0f);
	}
}

TEST_CASE("[Vec2f] [operator*] Multiplication operator")
{
	ufo::Vec2f vec(1.0f, 2.0f);
	float      scalar = 2.0f;

	SECTION("Multiplication (*) operator with scalar from left")
	{
		ufo::Vec2f result = vec * scalar;
		REQUIRE(result.x == 2.0f);
		REQUIRE(result.y == 4.0f);
	}

	SECTION("Multiplication of zero vector with scalar from left")
	{
		ufo::Vec2f zero_vec(0.0f, 0.0f);
		ufo::Vec2f result = zero_vec * scalar;
		REQUIRE(result.x == 0.0f);
		REQUIRE(result.y == 0.0f);
	}

	SECTION("Multiplication of negative scalar with Vec2f from left")
	{
		float      negative_scalar = -2.0f;
		ufo::Vec2f result          = vec * negative_scalar;
		REQUIRE(result.x == -2.0f);
		REQUIRE(result.y == -4.0f);
	}

	SECTION("Multiplication (*) operator with scalar from right")
	{
		ufo::Vec2f result = scalar * vec;
		REQUIRE(result.x == 2.0f);
		REQUIRE(result.y == 4.0f);
	}

	SECTION("Multiplication of zero scalar with Vec2f from right")
	{
		float      zero_scalar = 0.0f;
		ufo::Vec2f result      = zero_scalar * vec;
		REQUIRE(result.x == 0.0f);
		REQUIRE(result.y == 0.0f);
	}

	SECTION("Multiplication of negative scalar with Vec2f from right")
	{
		float      negative_scalar = -2.0f;
		ufo::Vec2f result          = negative_scalar * vec;
		REQUIRE(result.x == -2.0f);
		REQUIRE(result.y == -4.0f);
	}

	SECTION("Multiplication with Vec2f")
	{
		ufo::Vec2f v1(-2.5f, 3.1f);
		ufo::Vec2f v2(2.0f, 3.0f);
		ufo::Vec2f result = v1 * v2;
		REQUIRE(result.x == Catch::Approx(-5.0f));
		REQUIRE(result.y == Catch::Approx(9.3f));
	}
}

TEST_CASE("[Vec2f] [operator/] Division operator")
{
	ufo::Vec2f vec1(4.0f, 6.0f);
	ufo::Vec2f vec2(2.0f, 3.0f);
	float      scalar = 2.0f;

	SECTION("Division (/) operator with Vec2f and Vec2f")
	{
		ufo::Vec2f result = vec1 / vec2;
		REQUIRE(result.x == 2.0f);
		REQUIRE(result.y == 2.0f);
	}

	SECTION("Division (/) operator with Vec2f and scalar from left")
	{
		ufo::Vec2f result = vec1 / scalar;
		REQUIRE(result.x == 2.0f);
		REQUIRE(result.y == 3.0f);
	}

	SECTION("Division (/) operator with Vec2f and zero from left")
	{
		float      zero_scalar = 0.0f;
		ufo::Vec2f result      = vec1 / zero_scalar;
		REQUIRE(std::isinf(result.x));  // Division by zero results in Inf
		REQUIRE(std::isinf(result.y));  // Division by zero results in Inf
	}

	SECTION("Division (/) operator with scalar and Vec2f from right")
	{
		ufo::Vec2f result = scalar / vec1;
		REQUIRE(result.x == 2.0f / 4.0f);
		REQUIRE(result.y == 2.0f / 6.0f);
	}

	SECTION("Division (/) operator with division by zero")
	{
		ufo::Vec2f zeroVec(0.0f, 0.0f);
		ufo::Vec2f result = scalar / zeroVec;

		REQUIRE(std::isinf(result.x));  // Division by zero results in Inf
		REQUIRE(std::isinf(result.y));  // Division by zero results in Inf
	}
}

TEST_CASE("[Vec2f] [operator+=] Compound Addition operator")
{
	ufo::Vec2f vec(1.0f, 2.0f);
	ufo::Vec2f otherVec(3.0f, 4.0f);
	float      scalar = 2.0f;

	SECTION("Compound addition (+=) operator with Vec2f")
	{
		vec += otherVec;
		REQUIRE(vec.x == 4.0f);
		REQUIRE(vec.y == 6.0f);
	}

	SECTION("Compound addition (+=) operator with scalar")
	{
		vec += scalar;
		REQUIRE(vec.x == 3.0f);
		REQUIRE(vec.y == 4.0f);
	}
}

TEST_CASE("[Vec2f] [operator-=] Compound Subtraction operator")
{
	ufo::Vec2f vec(1.0f, 5.0f);
	ufo::Vec2f otherVec(3.0f, 4.0f);
	float      scalar = 2.0f;

	SECTION("Compound subtraction (-=) operator with Vec2f")
	{
		vec -= otherVec;
		REQUIRE(vec.x == -2.0f);
		REQUIRE(vec.y == 1.0f);
	}

	SECTION("Compound subtraction (-=) operator with scalar")
	{
		vec -= scalar;
		REQUIRE(vec.x == -1.0f);
		REQUIRE(vec.y == 3.0f);
	}
}

TEST_CASE("[Vec2f] [operator*=] Compound Multiplication operator")
{
	ufo::Vec2f vec(1.0f, 5.0f);
	ufo::Vec2f otherVec(3.0f, 4.0f);
	float      scalar = 2.0f;

	SECTION("Compound multiplication (*=) operator with Vec2f")
	{
		vec *= otherVec;
		REQUIRE(vec.x == 3.0f);
		REQUIRE(vec.y == 20.0f);
	}

	SECTION("Compound multiplication (*=) operator with scalar")
	{
		vec *= scalar;
		REQUIRE(vec.x == 2.0f);
		REQUIRE(vec.y == 10.0f);
	}
}

TEST_CASE("[Vec2f] [operator/=] Compound division operator")
{
	ufo::Vec2f vec(6.0f, 10.0f);
	ufo::Vec2f otherVec(3.0f, 2.0f);
	float      scalar = 2.0f;

	SECTION("Compound division (/=) operator with Vec2f")
	{
		vec /= otherVec;
		REQUIRE(vec.x == 2.0f);
		REQUIRE(vec.y == 5.0f);
	}

	SECTION("Compound division (/=) operator with scalar")
	{
		vec /= scalar;
		REQUIRE(vec.x == 3.0f);
		REQUIRE(vec.y == 5.0f);
	}
}

TEST_CASE("[Vec2f] [dot] Dot product")
{
	SECTION("Dot product of zero vectors")
	{
		ufo::Vec2f v1(0.0f, 0.0f);
		ufo::Vec2f v2(0.0f, 0.0f);
		REQUIRE(v1.dot(v2) == Catch::Approx(0.0f));
	}

	SECTION("Dot product with one zero vector")
	{
		ufo::Vec2f v1(1.0f, 2.0f);
		ufo::Vec2f v2(0.0f, 0.0f);
		REQUIRE(v1.dot(v2) == Catch::Approx(0.0f));
	}

	SECTION("Dot product of orthogonal vectors")
	{
		ufo::Vec2f v1(1.0f, 0.0f);
		ufo::Vec2f v2(0.0f, 1.0f);
		REQUIRE(v1.dot(v2) == Catch::Approx(0.0f));
	}

	SECTION("Dot product of parallel vectors")
	{
		ufo::Vec2f v1(1.0f, 1.0f);
		ufo::Vec2f v2(2.0f, 2.0f);
		REQUIRE(v1.dot(v2) == Catch::Approx(4.0f));
	}

	SECTION("Dot product with negative components")
	{
		ufo::Vec2f v1(1.0f, -1.0f);
		ufo::Vec2f v2(-1.0f, 1.0f);
		REQUIRE(v1.dot(v2) == Catch::Approx(-2.0f));
	}

	SECTION("Dot product of arbitrary vectors")
	{
		ufo::Vec2f v1(3.0f, 4.0f);
		ufo::Vec2f v2(1.0f, 2.0f);
		REQUIRE(v1.dot(v2) == Catch::Approx(11.0f));
	}
}

TEST_CASE("[Vec2f] [operator()]")
{
	ufo::Vec2f v(1.5f, 4.3f);
	REQUIRE(v(0) == Catch::Approx(1.5f));
	REQUIRE(v(1) == Catch::Approx(4.3f));

	ufo::Vec2f const cv(2.3f, 0.1f);
	REQUIRE(cv(0) == Catch::Approx(2.3f));
	REQUIRE(cv(1) == Catch::Approx(0.1f));
}

TEST_CASE("[Vec2f] [operator[]]")
{
	ufo::Vec2f v(1.5f, 4.3f);
	REQUIRE(v[0] == Catch::Approx(1.5f));
	REQUIRE(v[1] == Catch::Approx(4.3f));

	ufo::Vec2f const cv(2.3f, 0.1f);
	REQUIRE(cv[0] == Catch::Approx(2.3f));
	REQUIRE(cv[1] == Catch::Approx(0.1f));
}

TEST_CASE("[Vec2f] [norm]")
{
	SECTION("Norm of a zero vector")
	{
		ufo::Vec2f v(0.0f, 0.0f);
		REQUIRE(v.norm() == Catch::Approx(0.0f));
	}

	SECTION("Norm of a unit vector along x-axis")
	{
		ufo::Vec2f v(1.0f, 0.0f);
		REQUIRE(v.norm() == Catch::Approx(1.0f));
	}

	SECTION("Norm of a unit vector along y-axis")
	{
		ufo::Vec2f v(0.0f, 1.0f);
		REQUIRE(v.norm() == Catch::Approx(1.0f));
	}

	SECTION("Norm of a vector with equal components")
	{
		ufo::Vec2f v(1.0f, 1.0f);
		REQUIRE(v.norm() == Catch::Approx(std::sqrt(2.0f)));
	}

	SECTION("Norm of a vector with negative components")
	{
		ufo::Vec2f v(-3.0f, -4.0f);
		REQUIRE(v.norm() == Catch::Approx(5.0f));
	}

	SECTION("Norm of an arbitrary vector")
	{
		ufo::Vec2f v(3.0f, 4.0f);
		REQUIRE(v.norm() == Catch::Approx(5.0f));
	}
}

TEST_CASE("[Vec2f] [normalize]")
{
	SECTION("Normalize zero vector")
	{
		ufo::Vec2f v(0.0f, 0.0f);
		auto       v1 = v.normalize();
		// TODO what should happen when normalizing zero vector
	}

	SECTION("Normalize unit vector along x-axis")
	{
		ufo::Vec2f v(1.0f, 0.0f);
		v.normalize();
		REQUIRE(v.x == Catch::Approx(1.0f));
		REQUIRE(v.y == Catch::Approx(0.0f));
	}

	SECTION("Normalize unit vector along y-axis")
	{
		ufo::Vec2f v(0.0f, 1.0f);
		v.normalize();
		REQUIRE(v.x == Catch::Approx(0.0f));
		REQUIRE(v.y == Catch::Approx(1.0f));
	}

	SECTION("Normalize arbitrary vector")
	{
		ufo::Vec2f v(3.0f, 4.0f);
		auto       v1     = v.normalize();
		float      length = std::sqrt(3.0f * 3.0f + 4.0f * 4.0f);
		REQUIRE(v.x == Catch::Approx(3.0f / length));
		REQUIRE(v.y == Catch::Approx(4.0f / length));
		REQUIRE(v1.x == Catch::Approx(3.0f / length));
		REQUIRE(v1.y == Catch::Approx(4.0f / length));
	}
}

TEST_CASE("[Vec2f] [normalized]")
{
	ufo::Vec2f v(3.0f, 4.0f);
	auto       v1     = v.normalized();
	float      length = std::sqrt(3.0f * 3.0f + 4.0f * 4.0f);
	REQUIRE(v.x == Catch::Approx(3.0f));
	REQUIRE(v.y == Catch::Approx(4.0f));
	REQUIRE(v1.x == Catch::Approx(3.0f / length));
	REQUIRE(v1.y == Catch::Approx(4.0f / length));
}

TEST_CASE("[Vec2f] [angleTo]")
{
	SECTION("Angle between parallel vectors")
	{
		ufo::Vec2f v1(1.0f, 0.0f);
		ufo::Vec2f v2(2.0f, 0.0f);
		REQUIRE(v1.angleTo(v2) == Catch::Approx(0.0f));
	}

	SECTION("Angle between perpendicular vectors")
	{
		ufo::Vec2f v1(1.0f, 0.0f);
		ufo::Vec2f v2(0.0f, 1.0f);
		REQUIRE(v1.angleTo(v2) == Catch::Approx(M_PI / 2));
	}

	SECTION("Angle between anti-parallel vectors")
	{
		ufo::Vec2f v1(1.0f, 0.0f);
		ufo::Vec2f v2(-1.0f, 0.0f);
		REQUIRE(v1.angleTo(v2) == Catch::Approx(M_PI));
	}

	SECTION("Angle between arbitrary vectors")
	{
		ufo::Vec2f v1(1.0f, 1.0f);
		ufo::Vec2f v2(-1.0f, 1.0f);
		REQUIRE(v1.angleTo(v2) == Catch::Approx(M_PI / 2));
	}

	SECTION("Angle between arbitrary vectors")
	{
		ufo::Vec2f v1(1.0f, 0.f);
		ufo::Vec2f v2(-1.0f, 1.0f);
		REQUIRE(v1.angleTo(v2) == Catch::Approx(M_PI * 3.0f / 4.0f));
	}
}

TEST_CASE("[Vec2f][distance]")
{
	SECTION("Distance between identical vectors")
	{
		ufo::Vec2f v1(1.0f, 2.0f);
		ufo::Vec2f v2(1.0f, 2.0f);
		REQUIRE(v1.distance(v2) == Catch::Approx(0.0f));
	}

	SECTION("Distance between zero vectors")
	{
		ufo::Vec2f v1(0.0f, 0.0f);
		ufo::Vec2f v2(0.0f, 0.0f);
		REQUIRE(v1.distance(v2) == Catch::Approx(0.0f));
	}

	SECTION("Distance between vectors with one zero component")
	{
		ufo::Vec2f v1(1.0f, 0.0f);
		ufo::Vec2f v2(0.0f, 1.0f);
		REQUIRE(v1.distance(v2) == Catch::Approx(std::sqrt(2.0f)));
	}

	SECTION("Distance between arbitrary vectors")
	{
		ufo::Vec2f v1(1.0f, 2.0f);
		ufo::Vec2f v2(4.0f, 6.0f);
		REQUIRE(v1.distance(v2) == Catch::Approx(5.0f));
	}
}

TEST_CASE("[Vec2f] [size]")
{
	ufo::Vec2f v(1, 2);
	REQUIRE(v.size() == 2);
}

TEST_CASE("[Vec2f][min]")
{
	SECTION("Minimum of zero vector")
	{
		ufo::Vec2f v(0.0f, 0.0f);
		auto       result = v.min();
		REQUIRE(result == Catch::Approx(0.0f));
	}

	SECTION("Minimum of vector with equal components")
	{
		ufo::Vec2f v(2.0f, 2.0f);
		auto       result = v.min();
		REQUIRE(result == Catch::Approx(2.0f));
	}

	SECTION("Minimum of arbitrary vector")
	{
		ufo::Vec2f v(3.0f, 1.5f);
		auto       result = v.min();
		REQUIRE(result == Catch::Approx(1.5f));
	}

	SECTION("Minimum of vector with negative components")
	{
		ufo::Vec2f v(-2.0f, -4.0f);
		auto       result = v.min();
		REQUIRE(result == Catch::Approx(-4.0f));
	}
}

TEST_CASE("[Vec2f][max]")
{
	SECTION("Maximum of zero vector")
	{
		ufo::Vec2f v(0.0f, 0.0f);
		auto       result = v.max();
		REQUIRE(result == Catch::Approx(0.0f));
	}

	SECTION("Maximum of vector with equal components")
	{
		ufo::Vec2f v(2.0f, 2.0f);
		auto       result = v.max();
		REQUIRE(result == Catch::Approx(2.0f));
	}

	SECTION("Maximum of arbitrary vector")
	{
		ufo::Vec2f v(3.0f, 1.5f);
		auto       result = v.max();
		REQUIRE(result == Catch::Approx(3.0f));
	}

	SECTION("Maximum of vector with negative components")
	{
		ufo::Vec2f v(-2.0f, -4.0f);
		auto       result = v.max();
		REQUIRE(result == Catch::Approx(-2.0f));
	}
}

TEST_CASE("[Vec2f][minElementIndex]")
{
	SECTION("Minimum element index of zero vector")
	{
		ufo::Vec2f v(0.0f, 0.0f);
		auto       result = v.minElementIndex();
		REQUIRE(result == 0);
	}

	SECTION("Minimum element index of vector with equal components")
	{
		ufo::Vec2f v(2.0f, 2.0f);
		auto       result = v.minElementIndex();
		REQUIRE(result == 0);
	}

	SECTION("Minimum element index of arbitrary vector")
	{
		ufo::Vec2f v(3.0f, 1.5f);
		auto       result = v.minElementIndex();
		REQUIRE(result == 1);
	}

	SECTION("Minimum element index of vector with negative components")
	{
		ufo::Vec2f v(-2.0f, -4.0f);
		auto       result = v.minElementIndex();
		REQUIRE(result == 1);
	}
}

TEST_CASE("[Vec2f][maxElementIndex]")
{
	SECTION("Maximum element index of zero vector")
	{
		ufo::Vec2f v(0.0f, 0.0f);
		auto       result = v.maxElementIndex();
		REQUIRE(result == 0);
	}

	SECTION("Maximum element index of vector with equal components")
	{
		ufo::Vec2f v(2.0f, 2.0f);
		auto       result = v.maxElementIndex();
		REQUIRE(result == 0);
	}

	SECTION("Maximum element index of arbitrary vector")
	{
		ufo::Vec2f v(3.0f, 4.5f);
		auto       result = v.maxElementIndex();
		REQUIRE(result == 1);
	}

	SECTION("Maximum of vector with negative components")
	{
		ufo::Vec2f v(-2.0f, -4.0f);
		auto       result = v.maxElementIndex();
		REQUIRE(result == 0);
	}
}

TEST_CASE("[Vec2f][ceil]")
{
	SECTION("Ceiling of zero vector")
	{
		ufo::Vec2f v(0.0f, 0.0f);
		ufo::Vec2f result = v.ceil();
		REQUIRE(result.x == Catch::Approx(0.0f));
		REQUIRE(result.y == Catch::Approx(0.0f));
	}

	SECTION("Ceiling of positive components")
	{
		ufo::Vec2f v(1.5f, 2.7f);
		ufo::Vec2f result = v.ceil();
		REQUIRE(result.x == Catch::Approx(2.0f));
		REQUIRE(result.y == Catch::Approx(3.0f));
	}

	SECTION("Ceiling of negative components")
	{
		ufo::Vec2f v(-1.5f, -2.7f);
		ufo::Vec2f result = v.ceil();
		REQUIRE(result.x == Catch::Approx(-1.0f));
		REQUIRE(result.y == Catch::Approx(-2.0f));
	}

	SECTION("Ceiling of mixed components")
	{
		ufo::Vec2f v(1.2f, -3.8f);
		ufo::Vec2f result = v.ceil();
		REQUIRE(result.x == Catch::Approx(2.0f));
		REQUIRE(result.y == Catch::Approx(-3.0f));
	}

	SECTION("Ceiling of mixed components")
	{
		ufo::Vec2f const v(1.2f, -3.8f);
		ufo::Vec2f       result = v.ceil();
		REQUIRE(result.x == Catch::Approx(2.0f));
		REQUIRE(result.y == Catch::Approx(-3.0f));
	}
}

TEST_CASE("[Vec2f][floor]")
{
	SECTION("Floor of zero vector")
	{
		ufo::Vec2f v(0.0f, 0.0f);
		ufo::Vec2f result = v.floor();
		REQUIRE(result.x == Catch::Approx(0.0f));
		REQUIRE(result.y == Catch::Approx(0.0f));
	}

	SECTION("Floor of positive components")
	{
		ufo::Vec2f v(1.5f, 2.7f);
		ufo::Vec2f result = v.floor();
		REQUIRE(result.x == Catch::Approx(1.0f));
		REQUIRE(result.y == Catch::Approx(2.0f));
	}

	SECTION("Floor of negative components")
	{
		ufo::Vec2f v(-1.5f, -2.7f);
		ufo::Vec2f result = v.floor();
		REQUIRE(result.x == Catch::Approx(-2.0f));
		REQUIRE(result.y == Catch::Approx(-3.0f));
	}

	SECTION("Floor of mixed components")
	{
		ufo::Vec2f v(1.2f, -3.8f);
		ufo::Vec2f result = v.floor();
		REQUIRE(result.x == Catch::Approx(1.0f));
		REQUIRE(result.y == Catch::Approx(-4.0f));
	}

	SECTION("Floor of mixed components")
	{
		ufo::Vec2f const v(1.2f, -3.8f);
		ufo::Vec2f       result = v.floor();
		REQUIRE(result.x == Catch::Approx(1.0f));
		REQUIRE(result.y == Catch::Approx(-4.0f));
	}
}

TEST_CASE("[Vec2f][trunc]")
{
	SECTION("Truncate of zero vector")
	{
		ufo::Vec2f v(0.0f, 0.0f);
		ufo::Vec2f result = v.trunc();
		REQUIRE(result.x == Catch::Approx(0.0f));
		REQUIRE(result.y == Catch::Approx(0.0f));
	}

	SECTION("Truncate of positive components")
	{
		ufo::Vec2f v(1.5f, 2.7f);
		ufo::Vec2f result = v.trunc();
		REQUIRE(result.x == Catch::Approx(1.0f));
		REQUIRE(result.y == Catch::Approx(2.0f));
	}

	SECTION("Truncate of negative components")
	{
		ufo::Vec2f v(-1.5f, -2.7f);
		ufo::Vec2f result = v.trunc();
		REQUIRE(result.x == Catch::Approx(-1.0f));
		REQUIRE(result.y == Catch::Approx(-2.0f));
	}

	SECTION("Truncate of mixed components")
	{
		ufo::Vec2f v(1.2f, -3.8f);
		ufo::Vec2f result = v.trunc();
		REQUIRE(result.x == Catch::Approx(1.0f));
		REQUIRE(result.y == Catch::Approx(-3.0f));
	}

	SECTION("Truncate of mixed components")
	{
		ufo::Vec2f const v(1.2f, -3.8f);
		ufo::Vec2f       result = v.trunc();
		REQUIRE(result.x == Catch::Approx(1.0f));
		REQUIRE(result.y == Catch::Approx(-3.0f));
	}
}

TEST_CASE("[Vec2f][round]")
{
	SECTION("Rounding of zero vector")
	{
		ufo::Vec2f v(0.0f, 0.0f);
		ufo::Vec2f result = v.round();
		REQUIRE(result.x == Catch::Approx(0.0f));
		REQUIRE(result.y == Catch::Approx(0.0f));
	}

	SECTION("Rounding of positive components")
	{
		ufo::Vec2f v(1.5f, 2.7f);
		ufo::Vec2f result = v.round();
		REQUIRE(result.x == Catch::Approx(2.0f));
		REQUIRE(result.y == Catch::Approx(3.0f));
	}

	SECTION("Rounding of negative components")
	{
		ufo::Vec2f v(-1.5f, -2.7f);
		ufo::Vec2f result = v.round();
		REQUIRE(result.x == Catch::Approx(-2.0f));
		REQUIRE(result.y == Catch::Approx(-3.0f));
	}

	SECTION("Rounding of mixed components")
	{
		ufo::Vec2f v(1.2f, -3.8f);
		ufo::Vec2f result = v.round();
		REQUIRE(result.x == Catch::Approx(1.0f));
		REQUIRE(result.y == Catch::Approx(-4.0f));
	}

	SECTION("Rounding of mixed components")
	{
		ufo::Vec2f const v(1.2f, -3.8f);
		ufo::Vec2f       result = v.round();
		REQUIRE(result.x == Catch::Approx(1.0f));
		REQUIRE(result.y == Catch::Approx(-4.0f));
	}
}

TEST_CASE("[Vec2f][abs]")
{
	SECTION("Absolute value of zero vector")
	{
		ufo::Vec2f v(0.0f, 0.0f);
		ufo::Vec2f result = v.abs();
		REQUIRE(result.x == Catch::Approx(0.0f));
		REQUIRE(result.y == Catch::Approx(0.0f));
	}

	SECTION("Absolute value of positive components")
	{
		ufo::Vec2f v(1.5f, 2.7f);
		ufo::Vec2f result = v.abs();
		REQUIRE(result.x == Catch::Approx(1.5f));
		REQUIRE(result.y == Catch::Approx(2.7f));
	}

	SECTION("Absolute value of negative components")
	{
		ufo::Vec2f v(-1.5f, -2.7f);
		ufo::Vec2f result = v.abs();
		REQUIRE(result.x == Catch::Approx(1.5f));
		REQUIRE(result.y == Catch::Approx(2.7f));
	}

	SECTION("Absolute value of mixed components")
	{
		ufo::Vec2f v(1.2f, -3.8f);
		ufo::Vec2f result = v.abs();
		REQUIRE(result.x == Catch::Approx(1.2f));
		REQUIRE(result.y == Catch::Approx(3.8f));
	}
	SECTION("Absolute value of mixed components")
	{
		ufo::Vec2f const v(1.2f, -3.8f);
		ufo::Vec2f       result = v.abs();
		REQUIRE(result.x == Catch::Approx(1.2f));
		REQUIRE(result.y == Catch::Approx(3.8f));
	}
}

TEST_CASE("[Vec2f][clamp]")
{
	SECTION("Clamping of zero vector")
	{
		ufo::Vec2f v(0.0f, 0.0f);
		ufo::Vec2f minVal(-1.0f, -1.0f);
		ufo::Vec2f maxVal(1.0f, 1.0f);
		ufo::Vec2f result = v.clamp(minVal, maxVal);
		REQUIRE(result.x == Catch::Approx(0.0f));
		REQUIRE(result.y == Catch::Approx(0.0f));
	}

	SECTION("Clamping of vector within range")
	{
		ufo::Vec2f v(0.5f, -0.5f);
		ufo::Vec2f minVal(-1.0f, -1.0f);
		ufo::Vec2f maxVal(1.0f, 1.0f);
		ufo::Vec2f result = v.clamp(minVal, maxVal);
		REQUIRE(result.x == Catch::Approx(0.5f));
		REQUIRE(result.y == Catch::Approx(-0.5f));
	}

	SECTION("Clamping of vector with components above maximum")
	{
		ufo::Vec2f v(1.5f, 2.5f);
		ufo::Vec2f minVal(-1.0f, -1.0f);
		ufo::Vec2f maxVal(1.0f, 1.0f);
		ufo::Vec2f result = v.clamp(minVal, maxVal);
		REQUIRE(result.x == Catch::Approx(1.0f));
		REQUIRE(result.y == Catch::Approx(1.0f));
	}

	SECTION("Clamping of vector with components below minimum")
	{
		ufo::Vec2f v(-1.5f, -2.5f);
		ufo::Vec2f minVal(-1.0f, -1.0f);
		ufo::Vec2f maxVal(1.0f, 1.0f);
		ufo::Vec2f result = v.clamp(minVal, maxVal);
		REQUIRE(result.x == Catch::Approx(-1.0f));
		REQUIRE(result.y == Catch::Approx(-1.0f));
	}

	SECTION("Clamping of vector with components below minimum")
	{
		ufo::Vec2f const v(-1.5f, -2.5f);
		ufo::Vec2f const minVal(-1.0f, -1.0f);
		ufo::Vec2f const maxVal(1.0f, 1.0f);
		ufo::Vec2f       result = v.clamp(minVal, maxVal);
		REQUIRE(result.x == Catch::Approx(-1.0f));
		REQUIRE(result.y == Catch::Approx(-1.0f));
	}
}

TEST_CASE("[Vec2f] [2D Cross Product]")
{
	ufo::Vec2f u1(1.0f, 2.0f);
	ufo::Vec2f v1(3.0f, 4.0f);

	ufo::Vec2f u2(-1.0f, 2.0f);
	ufo::Vec2f v2(3.0f, -4.0f);

	ufo::Vec2f u3(0.0f, 0.0f);
	ufo::Vec2f v3(0.0f, 0.0f);

	ufo::Vec2f u4(1.0f, 0.0f);
	ufo::Vec2f v4(0.0f, 1.0f);

	SECTION("Non-collinear Vectors")
	{
		float result1 = u1.cross(v1);
		REQUIRE(result1 == Catch::Approx(-2.0f));

		float result2 = u2.cross(v2);
		REQUIRE(result2 == Catch::Approx(14.0f));
	}

	SECTION("Collinear Vectors")
	{
		float result3 = u3.cross(v3);
		REQUIRE(result3 == Catch::Approx(0.0f));
	}

	SECTION("Perpendicular Vectors")
	{
		float result4 = u4.cross(v4);
		REQUIRE(result4 == Catch::Approx(1.0f));
	}
}