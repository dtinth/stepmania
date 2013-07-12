#include <gtest/gtest.h>

#include "Rage/Matrix.hpp"

using namespace Rage;

class MatrixTest: public ::testing::Test {
public:
	MatrixTest() {}
};

TEST_F(MatrixTest, SimpleAdd)
{
	Matrix a(1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4);
	Matrix b(a);

	Matrix expect(2, 4, 6, 8, 2, 4, 6, 8, 2, 4, 6, 8, 2, 4, 6, 8);

	ASSERT_EQ(expect, a + b);
}

TEST_F(MatrixTest, MultiplyTest)
{
	Matrix a(1, 2, 3, 4, 2, 4, 7, 11, 3, 7, 14, 25, 4, 11, 25, 50);

	Matrix b(1, 2, 3, 4, 2, 4, 6, 8, 3, 6, 9, 12, 4, 8, 12, 16);

	Matrix expect(30, 75, 159, 301, 60, 150, 318, 602, 90, 225, 477, 903, 120, 300, 636, 1204);
	//Matrix expect(30, 60, 90, 120, 75, 150, 225, 300, 159, 318, 477, 636, 301, 602, 903, 1204);

	ASSERT_EQ(expect, a * b);
}