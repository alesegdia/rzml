#include <gtest/gtest.h>
#include "rzml/LinePlaneIntersection.h"
#include <glm/glm.hpp>

using namespace rzml;

TEST(LinePlaneIntersectionTest, IntersectionExists) {
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

TEST(LinePlaneIntersectionTest, NoIntersection) {
	glm::fvec3 planeNormal(0.0f, 1.0f, 0.0f);
	glm::fvec3 planePoint(0.0f, 0.0f, 0.0f);
	glm::fvec3 lineOrigin(0.0f, 1.0f, 0.0f);
	glm::fvec3 lineDirection(0.0f, 1.0f, 0.0f);
	glm::fvec3 outIntersection;

	bool result = Line3DPlaneIntersection(planeNormal, planePoint, lineOrigin, lineDirection, outIntersection);

	EXPECT_FALSE(result);
}

TEST(LinePlaneIntersectionTest, IntersectionAtDifferentPoint) {
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

TEST(LinePlaneIntersectionTest, IntersectionWithNonAxisAlignedPlane) {
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