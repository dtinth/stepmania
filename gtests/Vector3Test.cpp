#include <gtest/gtest.h>

#include "Rage/Vector3.hpp"

using namespace Rage;

class Vector3Test: public ::testing::Test {
public:
	Vector3Test() {}
};

TEST_F(Vector3Test, AddTest)
{
	Vector3 a(1, 2, 3);
	Vector3 b(a);

	Vector3 expect(2, 4, 6);

	ASSERT_EQ(expect, a + b);
}