#include "LinePlaneIntersection.h"

namespace aether::math
{

	bool LinePlaneIntersection(const glm::fvec3& planeNormal, const glm::fvec3& planePoint, const glm::fvec3& lineOrigin, const glm::fvec3& lineDirection, glm::fvec3& outIntersection)
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

}
