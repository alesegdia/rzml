#pragma once

#include <glm/glm.hpp>

namespace rzml {

/**
 * @brief Checks if two 3D axis-aligned bounding boxes (AABBs) intersect.
 *
 * @param aMin Minimum corner of the first AABB.
 * @param aMax Maximum corner of the first AABB.
 * @param bMin Minimum corner of the second AABB.
 * @param bMax Maximum corner of the second AABB.
 * @return true if the AABBs intersect, false otherwise.
 */
bool AABB3DIntersection(const glm::fvec3& aMin, const glm::fvec3& aMax, const glm::fvec3& bMin, const glm::fvec3& bMax);

/**
 * @brief Computes the intersection point between a 3D line and a plane.
 *
 * @param planeNormal Normal vector of the plane.
 * @param planePoint A point on the plane.
 * @param lineOrigin Origin point of the line.
 * @param lineDirection Direction vector of the line.
 * @param outIntersection Output parameter for the intersection point.
 * @return true if the line intersects the plane, false otherwise.
 */
bool Line3DPlaneIntersection(const glm::fvec3& planeNormal, const glm::fvec3& planePoint, const glm::fvec3& lineOrigin, const glm::fvec3& lineDirection, glm::fvec3& outIntersection);

/**
 * @brief Computes the intersection point between a 3D line and a sphere.
 *
 * @param sphereCenter Center of the sphere.
 * @param sphereRadius Radius of the sphere.
 * @param lineOrigin Origin point of the line.
 * @param lineDirection Direction vector of the line.
 * @param outIntersection Output parameter for the intersection point.
 * @return true if the line intersects the sphere, false otherwise.
 */
bool Line3DSphereIntersection(const glm::fvec3& sphereCenter, float sphereRadius, const glm::fvec3& lineOrigin, const glm::fvec3& lineDirection, glm::fvec3& outIntersection);

/**
 * @brief Computes the intersection point between a 2D line segment and a circle.
 *
 * @param circleCenter Center of the circle.
 * @param circleRadius Radius of the circle.
 * @param lineStart Start point of the line segment.
 * @param lineEnd End point of the line segment.
 * @param outIntersection Output parameter for the intersection point.
 * @return true if the line segment intersects the circle, false otherwise.
 */
bool Line2DCircleIntersection(const glm::fvec2& circleCenter, float circleRadius, const glm::fvec2& lineStart, const glm::fvec2& lineEnd, glm::fvec2& outIntersection);

/**
 * @brief Computes the intersection point between two 2D lines.
 *
 * @param p1 First point of the first line.
 * @param p2 Second point of the first line.
 * @param p3 First point of the second line.
 * @param p4 Second point of the second line.
 * @param outIntersection Output parameter for the intersection point.
 * @return true if the lines intersect, false otherwise.
 */
bool LineLineIntersection(const glm::fvec2& p1, const glm::fvec2& p2, const glm::fvec2& p3, const glm::fvec2& p4, glm::fvec2& outIntersection);


bool InfiniteLineInfiniteLineIntersection(const glm::fvec2& p1, const glm::fvec2& p2, const glm::fvec2& p3, const glm::fvec2& p4, glm::fvec2& outIntersection);

}