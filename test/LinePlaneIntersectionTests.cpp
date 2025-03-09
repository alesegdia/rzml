#include <gtest/gtest.h>
#include "rzml/LinePlaneIntersection.h"
#include <glm/glm.hpp>

using namespace rzml;

TEST(LinePlaneIntersectionTest, IntersectionExists)
{
	glm::fvec3 planeNormal(0.0f, 1.0f, 0.0f);
	glm::fvec3 planePoint(0.0f, 0.0f, 0.0f);
	glm::fvec3 lineOrigin(0.0f, -1.0f, 0.0f);
	glm::fvec3 lineDirection(0.0f, 1.0f, 0.0f);
	glm::fvec3 outIntersection;

	bool result = Line3DPlaneIntersection(planeNormal, planePoint, lineOrigin, lineDirection, outIntersection);

	EXPECT_TRUE(result);
	EXPECT_FLOAT_EQ(outIntersection.x, 0.0f);
	EXPECT_FLOAT_EQ(outIntersection.y, 0.0f);
	EXPECT_FLOAT_EQ(outIntersection.z, 0.0f);
}

TEST(LinePlaneIntersectionTest, NoIntersection)
{
	glm::fvec3 planeNormal(0.0f, 1.0f, 0.0f);
	glm::fvec3 planePoint(0.0f, 0.0f, 0.0f);
	glm::fvec3 lineOrigin(0.0f, 1.0f, 0.0f);
	glm::fvec3 lineDirection(0.0f, 1.0f, 0.0f);
	glm::fvec3 outIntersection;

	bool result = Line3DPlaneIntersection(planeNormal, planePoint, lineOrigin, lineDirection, outIntersection);

	EXPECT_FALSE(result);
}

TEST(LinePlaneIntersectionTest, IntersectionAtDifferentPoint)
{
	glm::fvec3 planeNormal(0.0f, 1.0f, 0.0f);
	glm::fvec3 planePoint(0.0f, 5.0f, 0.0f);
	glm::fvec3 lineOrigin(0.0f, 0.0f, 0.0f);
	glm::fvec3 lineDirection(0.0f, 1.0f, 0.0f);
	glm::fvec3 outIntersection;

	bool result = Line3DPlaneIntersection(planeNormal, planePoint, lineOrigin, lineDirection, outIntersection);

	EXPECT_TRUE(result);
	EXPECT_FLOAT_EQ(outIntersection.x, 0.0f);
	EXPECT_FLOAT_EQ(outIntersection.y, 5.0f);
	EXPECT_FLOAT_EQ(outIntersection.z, 0.0f);
}

TEST(LinePlaneIntersectionTest, IntersectionWithNonAxisAlignedPlane)
{
	glm::fvec3 planeNormal(1.0f, 1.0f, 0.0f);
	glm::fvec3 planePoint(1.0f, 1.0f, 0.0f);
	glm::fvec3 lineOrigin(0.0f, 0.0f, 0.0f);
	glm::fvec3 lineDirection(1.0f, 1.0f, 0.0f);
	glm::fvec3 outIntersection;

	bool result = Line3DPlaneIntersection(planeNormal, planePoint, lineOrigin, lineDirection, outIntersection);

	EXPECT_TRUE(result);
	EXPECT_FLOAT_EQ(outIntersection.x, 1.0f);
	EXPECT_FLOAT_EQ(outIntersection.y, 1.0f);
	EXPECT_FLOAT_EQ(outIntersection.z, 0.0f);
}

TEST(LinePlaneIntersectionTest, Line2DCircleIntersectionExists)
{
	glm::fvec2 circleCenter(0.0f, 0.0f);
	float circleRadius = 1.0f;
	glm::fvec2 lineStart(-2.0f, 0.0f);
	glm::fvec2 lineEnd(2.0f, 0.0f);
	glm::fvec2 outIntersection;

	bool result = Line2DCircleIntersection(circleCenter, circleRadius, lineStart, lineEnd, outIntersection);

	EXPECT_TRUE(result);
	EXPECT_FLOAT_EQ(outIntersection.x, 0.0f);
	EXPECT_FLOAT_EQ(outIntersection.y, 0.0f);
}

TEST(LinePlaneIntersectionTest, Line2DCircleIntersectionNoIntersection)
{
	glm::fvec2 circleCenter(0.0f, 0.0f);
	float circleRadius = 1.0f;
	glm::fvec2 lineStart(2.0f, 2.0f);
	glm::fvec2 lineEnd(3.0f, 3.0f);
	glm::fvec2 outIntersection;

	bool result = Line2DCircleIntersection(circleCenter, circleRadius, lineStart, lineEnd, outIntersection);

	EXPECT_FALSE(result);
}

TEST(LinePlaneIntersectionTest, Line3DSphereIntersectionExists)
{
	glm::fvec3 sphereCenter(0.0f, 0.0f, 0.0f);
	float sphereRadius = 1.0f;
	glm::fvec3 lineOrigin(-2.0f, 0.0f, 0.0f);
	glm::fvec3 lineDirection(1.0f, 0.0f, 0.0f);
	glm::fvec3 outIntersection;

	bool result = Line3DSphereIntersection(sphereCenter, sphereRadius, lineOrigin, lineDirection, outIntersection);

	EXPECT_TRUE(result);
	EXPECT_FLOAT_EQ(outIntersection.x, -1.0f);
	EXPECT_FLOAT_EQ(outIntersection.y, 0.0f);
	EXPECT_FLOAT_EQ(outIntersection.z, 0.0f);
}

TEST(LinePlaneIntersectionTest, Line3DSphereIntersectionNoIntersection)
{
	glm::fvec3 sphereCenter(0.0f, 0.0f, 0.0f);
	float sphereRadius = 1.0f;
	glm::fvec3 lineOrigin(2.0f, 2.0f, 2.0f);
	glm::fvec3 lineDirection(1.0f, 1.0f, 1.0f);
	glm::fvec3 outIntersection;

	bool result = Line3DSphereIntersection(sphereCenter, sphereRadius, lineOrigin, lineDirection, outIntersection);

	EXPECT_FALSE(result);
}

TEST(LinePlaneIntersectionTest, AABB3DIntersectionExists)
{
	glm::fvec3 aMin(0.0f, 0.0f, 0.0f);
	glm::fvec3 aMax(1.0f, 1.0f, 1.0f);
	glm::fvec3 bMin(0.5f, 0.5f, 0.5f);
	glm::fvec3 bMax(1.5f, 1.5f, 1.5f);

	bool result = AABB3DIntersection(aMin, aMax, bMin, bMax);

	EXPECT_TRUE(result);
}

TEST(LinePlaneIntersectionTest, AABB3DIntersectionNoIntersection)
{
	glm::fvec3 aMin(0.0f, 0.0f, 0.0f);
	glm::fvec3 aMax(1.0f, 1.0f, 1.0f);
	glm::fvec3 bMin(2.0f, 2.0f, 2.0f);
	glm::fvec3 bMax(3.0f, 3.0f, 3.0f);

	bool result = AABB3DIntersection(aMin, aMax, bMin, bMax);

	EXPECT_FALSE(result);
}

TEST(LinePlaneIntersectionTest, LineLineIntersectionExists)
{
	glm::fvec2 p1(0.0f, 0.0f);
	glm::fvec2 p2(1.0f, 1.0f);
	glm::fvec2 p3(0.0f, 1.0f);
	glm::fvec2 p4(1.0f, 0.0f);
	glm::fvec2 outIntersection;

	bool result = LineLineIntersection(p1, p2, p3, p4, outIntersection);

	EXPECT_TRUE(result);
	EXPECT_FLOAT_EQ(outIntersection.x, 0.5f);
	EXPECT_FLOAT_EQ(outIntersection.y, 0.5f);
}

TEST(LinePlaneIntersectionTest, LineLineIntersectionNoIntersection)
{
	glm::fvec2 p1(0.0f, 0.0f);
	glm::fvec2 p2(1.0f, 1.0f);
	glm::fvec2 p3(2.0f, 2.0f);
	glm::fvec2 p4(3.0f, 3.0f);
	glm::fvec2 outIntersection;

	bool result = LineLineIntersection(p1, p2, p3, p4, outIntersection);

	EXPECT_FALSE(result);
}

TEST(LinePlaneIntersectionTest, InfiniteLineInfiniteLineIntersectionExists)
{
	glm::fvec2 p1(0.0f, 0.0f);
	glm::fvec2 p2(1.0f, 1.0f);
	glm::fvec2 p3(0.0f, 1.0f);
	glm::fvec2 p4(1.0f, 0.0f);
	glm::fvec2 outIntersection;

	bool result = InfiniteLineInfiniteLineIntersection(p1, p2, p3, p4, outIntersection);

	EXPECT_TRUE(result);
	EXPECT_FLOAT_EQ(outIntersection.x, 0.5f);
	EXPECT_FLOAT_EQ(outIntersection.y, 0.5f);
}

TEST(LinePlaneIntersectionTest, InfiniteLineInfiniteLineIntersectionNoIntersection)
{
	glm::fvec2 p1(0.0f, 0.0f);
	glm::fvec2 p2(1.0f, 1.0f);
	glm::fvec2 p3(2.0f, 2.0f);
	glm::fvec2 p4(3.0f, 3.0f);
	glm::fvec2 outIntersection;

	bool result = InfiniteLineInfiniteLineIntersection(p1, p2, p3, p4, outIntersection);

	EXPECT_FALSE(result);
}