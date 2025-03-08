#pragma once

#include <glm/glm.hpp>


namespace aether::math
{
	struct Ray
	{
		glm::fvec3 origin;
		glm::fvec3 destination;
		glm::fvec3 direction;
	};
}