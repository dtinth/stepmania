#include <gtest/gtest.h>

#include "Rage/Vector2.hpp"

using namespace Rage;

class Vector2Test: public ::testing::Test {
public:
	Vector2Test() {}
};

TEST_F(Vector2Test, Vector2BasicMath)
{
	Vector2 a(1, 2);
	Vector2 b(a);

	Vector2 expect(2, 4);

	ASSERT_EQ(expect, a + b);
}

TEST_F(Vector2Test, Vector2SubtractionTest)
{
	Vector2 a(3, 4);
	Vector2 b(1, 2);

	Vector2 expect(2, 2);

	ASSERT_EQ(expect, a - b);
}

TEST_F(Vector2Test, MultiplySingle)
{
	Vector2 v(2, 3.5);

	Vector2 expect(6, 10.5);

	ASSERT_EQ(expect, v * 3);
}