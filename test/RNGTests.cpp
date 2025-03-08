#include <gtest/gtest.h>
#include "rzml/RNG.h"
#include <vector>
#include <string>
#include <algorithm>

using namespace rzml;

TEST(RNGTest, Lerp) {
	EXPECT_FLOAT_EQ(lerp(0.0f, 10.0f, 0.0f), 0.0f);
	EXPECT_FLOAT_EQ(lerp(0.0f, 10.0f, 1.0f), 10.0f);
	EXPECT_FLOAT_EQ(lerp(0.0f, 10.0f, 0.5f), 5.0f);
	EXPECT_FLOAT_EQ(lerp(-10.0f, 10.0f, 0.5f), 0.0f);
}

TEST(RNGTest, RandiWithMax) {
	for (int i = 0; i < 100; ++i) {
		int result = randi(10);
		EXPECT_GE(result, 0);
		EXPECT_LT(result, 10);
	}
}

TEST(RNGTest, RandiWithMinMax) {
	for (int i = 0; i < 100; ++i) {
		int result = randi(5, 15);
		EXPECT_GE(result, 5);
		EXPECT_LT(result, 15);
	}
}

TEST(RNGTest, Split) {
	std::vector<std::string> result;
	EXPECT_EQ(split("a,b,c", result, ','), 3);
	EXPECT_EQ(result.size(), 3);
	EXPECT_EQ(result[0], "a");
	EXPECT_EQ(result[1], "b");
	EXPECT_EQ(result[2], "c");

	EXPECT_EQ(split("a,,c", result, ','), 3);
	EXPECT_EQ(result.size(), 3);
	EXPECT_EQ(result[0], "a");
	EXPECT_EQ(result[1], "");
	EXPECT_EQ(result[2], "c");

	EXPECT_EQ(split("", result, ','), 1);
	EXPECT_EQ(result.size(), 1);
	EXPECT_EQ(result[0], "");
}

TEST(WeightedRandomGeneratorTest, DefaultConstructor) {
	WeightedRandomGenerator generator;
	EXPECT_EQ(generator.GetRandomIndex(), 0);
}

TEST(WeightedRandomGeneratorTest, AddWeight) {
	WeightedRandomGenerator generator;
	generator.AddWeight(0, 10);
	generator.AddWeight(1, 20);
	generator.AddWeight(2, 30);

	std::vector<int> counts(3, 0);
	for (int i = 0; i < 10000; ++i) {
		int index = generator.GetRandomIndex();
		counts[index]++;
	}

	EXPECT_NEAR(counts[0], 10000 * 10 / 60, 1000);
	EXPECT_NEAR(counts[1], 10000 * 20 / 60, 1000);
	EXPECT_NEAR(counts[2], 10000 * 30 / 60, 1000);
}

TEST(WeightedRandomGeneratorTest, AddWeightOutOfOrder) {
	WeightedRandomGenerator generator;
	generator.AddWeight(2, 30);
	generator.AddWeight(0, 10);
	generator.AddWeight(1, 20);

	std::vector<int> counts(3, 0);
	for (int i = 0; i < 10000; ++i) {
		int index = generator.GetRandomIndex();
		counts[index]++;
	}

	EXPECT_NEAR(counts[0], 10000 * 10 / 60, 1000);
	EXPECT_NEAR(counts[1], 10000 * 20 / 60, 1000);
	EXPECT_NEAR(counts[2], 10000 * 30 / 60, 1000);
}
