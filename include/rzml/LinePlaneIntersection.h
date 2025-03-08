#pragma once

#include <glm/glm.hpp>

namespace rzml
{
	bool AABB3DIntersection(const glm::fvec3& aMin, const glm::fvec3& aMax, const glm::fvec3& bMin, const glm::fvec3& bMax);
	bool Line3DPlaneIntersection(const glm::fvec3& planeNormal, const glm::fvec3& planePoint, const glm::fvec3& lineOrigin, const glm::fvec3& lineDirection, glm::fvec3& outIntersection);

	bool Line3DSphereIntersection(const glm::fvec3& sphereCenter, float sphereRadius, const glm::fvec3& lineOrigin, const glm::fvec3& lineDirection, glm::fvec3& outIntersection);
	bool Line2DCircleIntersection(const glm::fvec2& circleCenter, float circleRadius, const glm::fvec2& lineStart, const glm::fvec2& lineEnd, glm::fvec2& outIntersection);
	bool LineLineIntersection(const glm::fvec2& p1, const glm::fvec2& p2, const glm::fvec2& p3, const glm::fvec2& p4, glm::fvec2& outIntersection);
}
