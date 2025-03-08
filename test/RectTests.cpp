#include <gtest/gtest.h>
#include "rzml/Rect.h"

using namespace rzml;

TEST(RectTest, ConstructorWithValues) {
	Rect<int> rect(10, 20, 30, 40);
	EXPECT_EQ(rect.GetX(), 10);
	EXPECT_EQ(rect.GetY(), 20);
	EXPECT_EQ(rect.GetW(), 30);
	EXPECT_EQ(rect.GetH(), 40);
	EXPECT_EQ(rect.GetCenter().GetX(), 25);
	EXPECT_EQ(rect.GetCenter().GetY(), 40);
}

TEST(RectTest, ConstructorWithVec2) {
	Vec2<int> pos(10, 20);
	Vec2<int> size(30, 40);
	Rect<int> rect(pos, size);
	EXPECT_EQ(rect.GetPosition(), pos);
	EXPECT_EQ(rect.GetSize(), size);
	EXPECT_EQ(rect.GetCenter().GetX(), 25);
	EXPECT_EQ(rect.GetCenter().GetY(), 40);
}

TEST(RectTest, CopyConstructor) {
	Rect<int> rect1(10, 20, 30, 40);
	Rect<int> rect2(rect1);
	EXPECT_EQ(rect2.GetX(), 10);
	EXPECT_EQ(rect2.GetY(), 20);
	EXPECT_EQ(rect2.GetW(), 30);
	EXPECT_EQ(rect2.GetH(), 40);
	EXPECT_EQ(rect2.GetCenter().GetX(), 25);
	EXPECT_EQ(rect2.GetCenter().GetY(), 40);
}

TEST(RectTest, DefaultConstructor) {
	Rect<int> rect;
	EXPECT_EQ(rect.GetX(), 0);
	EXPECT_EQ(rect.GetY(), 0);
	EXPECT_EQ(rect.GetW(), 0);
	EXPECT_EQ(rect.GetH(), 0);
}

TEST(RectTest, SetPosition) {
	Rect<int> rect(10, 20, 30, 40);
	rect.SetPosition(50, 60);
	EXPECT_EQ(rect.GetX(), 50);
	EXPECT_EQ(rect.GetY(), 60);
	EXPECT_EQ(rect.GetCenter().GetX(), 65);
	EXPECT_EQ(rect.GetCenter().GetY(), 80);
}

TEST(RectTest, SetSize) {
	Rect<int> rect(10, 20, 30, 40);
	rect.SetSize(50, 60);
	EXPECT_EQ(rect.GetW(), 50);
	EXPECT_EQ(rect.GetH(), 60);
	EXPECT_EQ(rect.GetCenter().GetX(), 35);
	EXPECT_EQ(rect.GetCenter().GetY(), 50);
}

TEST(RectTest, Move) {
	Rect<int> rect(10, 20, 30, 40);
	rect.Move(5, 10);
	EXPECT_EQ(rect.GetX(), 15);
	EXPECT_EQ(rect.GetY(), 30);
	EXPECT_EQ(rect.GetCenter().GetX(), 30);
	EXPECT_EQ(rect.GetCenter().GetY(), 50);
}

TEST(RectTest, MinMax) {
	Rect<int> rect(10, 20, 30, 40);
	EXPECT_EQ(rect.GetMin().GetX(), 10);
	EXPECT_EQ(rect.GetMin().GetY(), 20);
	EXPECT_EQ(rect.GetMax().GetX(), 40);
	EXPECT_EQ(rect.GetMax().GetY(), 60);
}

TEST(RectTest, SetX) {
	Rect<int> rect(10, 20, 30, 40);
	rect.SetX(50);
	EXPECT_EQ(rect.GetX(), 50);
	EXPECT_EQ(rect.GetCenter().GetX(), 65);
}

TEST(RectTest, SetY) {
	Rect<int> rect(10, 20, 30, 40);
	rect.SetY(60);
	EXPECT_EQ(rect.GetY(), 60);
	EXPECT_EQ(rect.GetCenter().GetY(), 80);
}

TEST(RectTest, Intersect) {
	Rect<int> rect1(10, 20, 30, 40);
	Rect<int> rect2(25, 35, 30, 40);
	EXPECT_TRUE(Intersect(rect1, rect2));

	Rect<int> rect3(50, 60, 30, 40);
	EXPECT_FALSE(Intersect(rect1, rect3));
}

TEST(RectTest, ClampValue) {
	EXPECT_EQ(Clamp(5, 1, 10), 5);
	EXPECT_EQ(Clamp(0, 1, 10), 1);
	EXPECT_EQ(Clamp(15, 1, 10), 10);
}

TEST(RectTest, ClampRect) {
	Rect<int> container(0, 0, 100, 100);
	Rect<int> contained(50, 50, 20, 20);
	Rect<int> result = Clamp(container, contained);
	EXPECT_EQ(result.GetX(), 50);
	EXPECT_EQ(result.GetY(), 50);

	Rect<int> contained2(150, 150, 20, 20);
	Rect<int> result2 = Clamp(container, contained2);
	EXPECT_EQ(result2.GetX(), 100);
	EXPECT_EQ(result2.GetY(), 100);
}