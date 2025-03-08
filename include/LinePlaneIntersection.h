#pragma once

#include <glm/glm.hpp>

namespace aether::math
{

	bool LinePlaneIntersection(const glm::fvec3& planeNormal, const glm::fvec3& planePoint, const glm::fvec3& lineOrigin, const glm::fvec3& lineDirection, glm::fvec3& outIntersection);

}
