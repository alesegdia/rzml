#include "rzml/LinePlaneIntersection.h"

#include <algorithm>

namespace rzml
{

	bool Line3DPlaneIntersection(const glm::fvec3& planeNormal, const glm::fvec3& planePoint, const glm::fvec3& lineOrigin, const glm::fvec3& lineDirection, glm::fvec3& outIntersection)
	{
		float d = glm::dot(planeNormal, planePoint);
		float t = (d - glm::dot(planeNormal, lineOrigin)) / glm::dot(planeNormal, lineDirection);
		if (t < 0)
		{
			return false;
		}
		outIntersection = lineOrigin + lineDirection * t;
		return true;
	}


	bool Line2DCircleIntersection(const glm::fvec2& circleCenter, float circleRadius, const glm::fvec2& lineStart, const glm::fvec2& lineEnd, glm::fvec2& outIntersection)
	{
		glm::fvec2 lineDirection = glm::normalize(lineEnd - lineStart);
		glm::fvec2 lineToCircle = circleCenter - lineStart;
		float projection = glm::dot(lineToCircle, lineDirection);
		if (projection < 0)
		{
			outIntersection = lineStart;
			return glm::length(lineToCircle) <= circleRadius;
		}
		if (projection > glm::length(lineEnd - lineStart))
		{
			outIntersection = lineEnd;
			return glm::length(circleCenter - lineEnd) <= circleRadius;
		}
		outIntersection = lineStart + lineDirection * projection;
		return glm::length(outIntersection - circleCenter) <= circleRadius;
	}

	bool Line3DSphereIntersection(const glm::fvec3& sphereCenter, float sphereRadius, const glm::fvec3& lineOrigin, const glm::fvec3& lineDirection, glm::fvec3& outIntersection)
	{
		glm::fvec3 lineToSphere = sphereCenter - lineOrigin;
		float projection = glm::dot(lineToSphere, lineDirection);
		if (projection < 0)
		{
			outIntersection = lineOrigin;
			return glm::length(lineToSphere) <= sphereRadius;
		}
		outIntersection = lineOrigin + lineDirection * projection;
		return glm::length(outIntersection - sphereCenter) <= sphereRadius;
	}


	bool AABB3DIntersection(const glm::fvec3& aMin, const glm::fvec3& aMax, const glm::fvec3& bMin, const glm::fvec3& bMax)
	{
		return aMin.x <= bMax.x && aMax.x >= bMin.x &&
			aMin.y <= bMax.y && aMax.y >= bMin.y &&
			aMin.z <= bMax.z && aMax.z >= bMin.z;
	}

	bool LineLineIntersection(const glm::fvec2& p1, const glm::fvec2& p2, const glm::fvec2& p3, const glm::fvec2& p4, glm::fvec2& outIntersection)
	{
		float x1 = p1.x, y1 = p1.y;
		float x2 = p2.x, y2 = p2.y;
		float x3 = p3.x, y3 = p3.y;
		float x4 = p4.x, y4 = p4.y;

		float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
		if (d == 0)
		{
			return false;
		}

		float pre = x1 * y2 - y1 * x2;
		float post = x3 * y4 - y3 * x4;
		float x = (pre * (x3 - x4) - (x1 - x2) * post) / d;
		float y = (pre * (y3 - y4) - (y1 - y2) * post) / d;

		if (x < std::min(x1, x2) || x > std::max(x1, x2) ||
			x < std::min(x3, x4) || x > std::max(x3, x4))
		{
			return false;
		}
		if (y < std::min(y1, y2) || y > std::max(y1, y2) ||
			y < std::min(y3, y4) || y > std::max(y3, y4))
		{
			return false;
		}

		outIntersection.x = x;
		outIntersection.y = y;
		return true;
	}

}
