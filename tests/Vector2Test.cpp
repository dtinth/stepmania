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