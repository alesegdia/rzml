#include <gtest/gtest.h>
#include "rzml/Matrix3D.h"

using namespace rzml;

TEST(Matrix3DTest, DefaultConstructor) {
	Matrix3D<float> matrix;
	EXPECT_EQ(matrix.GetWidth(), 0);
	EXPECT_EQ(matrix.GetHeight(), 0);
	EXPECT_EQ(matrix.GetDepth(), 0);
}

TEST(Matrix3DTest, ParameterizedConstructor) {
	Matrix3D<float> matrix(2, 3, 4);
	EXPECT_EQ(matrix.GetWidth(), 2);
	EXPECT_EQ(matrix.GetHeight(), 3);
	EXPECT_EQ(matrix.GetDepth(), 4);
	for (int z = 0; z < 4; ++z) {
		for (int y = 0; y < 3; ++y) {
			for (int x = 0; x < 2; ++x) {
				EXPECT_EQ(matrix.Get(x, y, z), 0.0f);
			}
		}
	}
}

TEST(Matrix3DTest, ParameterizedConstructorWithInitVal) {
	Matrix3D<float> matrix(1.0f, 2, 3, 4);
	EXPECT_EQ(matrix.GetWidth(), 2);
	EXPECT_EQ(matrix.GetHeight(), 3);
	EXPECT_EQ(matrix.GetDepth(), 4);
	for (int z = 0; z < 4; ++z) {
		for (int y = 0; y < 3; ++y) {
			for (int x = 0; x < 2; ++x) {
				EXPECT_EQ(matrix.Get(x, y, z), 1.0f);
			}
		}
	}
}

TEST(Matrix3DTest, ParameterizedConstructorWithData) {
	std::vector<float> data(24, 1.0f);
	Matrix3D<float> matrix(data, 2, 3, 4);
	EXPECT_EQ(matrix.GetWidth(), 2);
	EXPECT_EQ(matrix.GetHeight(), 3);
	EXPECT_EQ(matrix.GetDepth(), 4);
	for (int z = 0; z < 4; ++z) {
		for (int y = 0; y < 3; ++y) {
			for (int x = 0; x < 2; ++x) {
				EXPECT_EQ(matrix.Get(x, y, z), 1.0f);
			}
		}
	}
}

TEST(Matrix3DTest, SetAndGet) {
	Matrix3D<float> matrix(2, 3, 4);
	matrix.Set(1, 1, 1, 5.0f);
	EXPECT_EQ(matrix.Get(1, 1, 1), 5.0f);
}

TEST(Matrix3DTest, Clear) {
	Matrix3D<float> matrix(2, 3, 4);
	matrix.Set(1, 1, 1, 5.0f);
	matrix.Clear();
	for (int z = 0; z < 4; ++z) {
		for (int y = 0; y < 3; ++y) {
			for (int x = 0; x < 2; ++x) {
				EXPECT_EQ(matrix.Get(x, y, z), 0.0f);
			}
		}
	}
}

TEST(Matrix3DTest, ClearWithValue) {
	Matrix3D<float> matrix(2, 3, 4);
	matrix.Set(1, 1, 1, 5.0f);
	matrix.Clear(2.0f);
	for (int z = 0; z < 4; ++z) {
		for (int y = 0; y < 3; ++y) {
			for (int x = 0; x < 2; ++x) {
				EXPECT_EQ(matrix.Get(x, y, z), 2.0f);
			}
		}
	}
}

TEST(Matrix3DTest, OutOfBounds) {
	Matrix3D<float> matrix(2, 3, 4);
	EXPECT_THROW(matrix.Get(2, 3, 4), std::out_of_range);
	EXPECT_THROW(matrix.Set(2, 3, 4, 1.0f), std::out_of_range);
}

TEST(Matrix3DTest, Addition) {
	std::vector<float> data1(24, 1.0f);
	std::vector<float> data2(24, 2.0f);
	Matrix3D<float> matrix1(data1, 2, 3, 4);
	Matrix3D<float> matrix2(data2, 2, 3, 4);
	Matrix3D<float> result = matrix1 + matrix2;
	for (int z = 0; z < 4; ++z) {
		for (int y = 0; y < 3; ++y) {
			for (int x = 0; x < 2; ++x) {
				EXPECT_EQ(result.Get(x, y, z), 3.0f);
			}
		}
	}
}

TEST(Matrix3DTest, Subtraction) {
	std::vector<float> data1(24, 3.0f);
	std::vector<float> data2(24, 2.0f);
	Matrix3D<float> matrix1(data1, 2, 3, 4);
	Matrix3D<float> matrix2(data2, 2, 3, 4);
	Matrix3D<float> result = matrix1 - matrix2;
	for (int z = 0; z < 4; ++z) {
		for (int y = 0; y < 3; ++y) {
			for (int x = 0; x < 2; ++x) {
				EXPECT_EQ(result.Get(x, y, z), 1.0f);
			}
		}
	}
}

TEST(Matrix3DTest, Multiplication) {
	std::vector<float> data1(24, 2.0f);
	std::vector<float> data2(24, 3.0f);
	Matrix3D<float> matrix1(data1, 2, 3, 4);
	Matrix3D<float> matrix2(data2, 2, 3, 4);
	Matrix3D<float> result = matrix1 * matrix2;
	for (int z = 0; z < 4; ++z) {
		for (int y = 0; y < 3; ++y) {
			for (int x = 0; x < 2; ++x) {
				EXPECT_EQ(result.Get(x, y, z), 6.0f);
			}
		}
	}
}

TEST(Matrix3DTest, Division) {
	std::vector<float> data1(24, 6.0f);
	std::vector<float> data2(24, 2.0f);
	Matrix3D<float> matrix1(data1, 2, 3, 4);
	Matrix3D<float> matrix2(data2, 2, 3, 4);
	Matrix3D<float> result = matrix1 / matrix2;
	for (int z = 0; z < 4; ++z) {
		for (int y = 0; y < 3; ++y) {
			for (int x = 0; x < 2; ++x) {
				EXPECT_EQ(result.Get(x, y, z), 3.0f);
			}
		}
	}
}

TEST(Matrix3DTest, DivisionByZero) {
	std::vector<float> data1(24, 6.0f);
	std::vector<float> data2(24, 0.0f);
	Matrix3D<float> matrix1(data1, 2, 3, 4);
	Matrix3D<float> matrix2(data2, 2, 3, 4);
	EXPECT_THROW(matrix1 / matrix2, std::invalid_argument);
}