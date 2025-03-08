#pragma once

#include <glm/glm.hpp>
#include <algorithm>
#include "rzml/Ray.h"


namespace rzml
{

	class AABB
	{
	public:
		AABB() : m_min(0, 0, 0), m_max(0, 0, 0) {}
		AABB(const glm::fvec3& min, const glm::fvec3& max) : m_min(min), m_max(max) {}
		AABB(const AABB& other) : AABB(other.m_min, other.m_max) {}

		bool Intersects(const rzml::Ray& ray) const
		{
			float tmin = (m_min.x - ray.origin.x) / ray.direction.x;
			float tmax = (m_max.x - ray.origin.x) / ray.direction.x;

			if (tmin > tmax)
			{
				std::swap(tmin, tmax);
			}

			float tymin = (m_min.y - ray.origin.y) / ray.direction.y;
			float tymax = (m_max.y - ray.origin.y) / ray.direction.y;

			if (tymin > tymax)
			{
				std::swap(tymin, tymax);
			}

			if ((tmin > tymax) || (tymin > tmax))
			{
				return false;
			}

			if (tymin > tmin)
			{
				tmin = tymin;
			}

			if (tymax < tmax)
			{
				tmax = tymax;
			}

			float tzmin = (m_min.z - ray.origin.z) / ray.direction.z;
			float tzmax = (m_max.z - ray.origin.z) / ray.direction.z;

			if (tzmin > tzmax)
			{
				std::swap(tzmin, tzmax);
			}

			if ((tmin > tzmax) || (tzmin > tmax))
			{
				return false;
			}

			return true;
		}

		bool Intersects(const Ray& ray, glm::fvec3& outIntersectionPoint) const
		{
			float tmin = (m_min.x - ray.origin.x) / ray.direction.x;
			float tmax = (m_max.x - ray.origin.x) / ray.direction.x;

			if (tmin > tmax)
			{
				std::swap(tmin, tmax);
			}

			float tymin = (m_min.y - ray.origin.y) / ray.direction.y;
			float tymax = (m_max.y - ray.origin.y) / ray.direction.y;

			if (tymin > tymax)
			{
				std::swap(tymin, tymax);
			}

			if ((tmin > tymax) || (tymin > tmax))
			{
				return false;
			}

			if (tymin > tmin)
			{
				tmin = tymin;
			}

			if (tymax < tmax)
			{
				tmax = tymax;
			}

			float tzmin = (m_min.z - ray.origin.z) / ray.direction.z;
			float tzmax = (m_max.z - ray.origin.z) / ray.direction.z;

			if (tzmin > tzmax)
			{
				std::swap(tzmin, tzmax);
			}

			if ((tmin > tzmax) || (tzmin > tmax))
			{
				return false;
			}

			outIntersectionPoint = ray.origin + ray.direction * tmin;
			return true;
		}

		bool Intersects(const Ray& ray, glm::fvec3& outIntersectionPoint, glm::fvec3& normal) const
		{
			float tmin = (m_min.x - ray.origin.x) / ray.direction.x;
			float tmax = (m_max.x - ray.origin.x) / ray.direction.x;

			if (tmin > tmax)
			{
				std::swap(tmin, tmax);
			}

			float tymin = (m_min.y - ray.origin.y) / ray.direction.y;
			float tymax = (m_max.y - ray.origin.y) / ray.direction.y;

			if (tymin > tymax)
			{
				std::swap(tymin, tymax);
			}

			if ((tmin > tymax) || (tymin > tmax))
			{
				return false;
			}

			if (tymin > tmin)
			{
				tmin = tymin;
			}

			if (tymax < tmax)
			{
				tmax = tymax;
			}

			float tzmin = (m_min.z - ray.origin.z) / ray.direction.z;
			float tzmax = (m_max.z - ray.origin.z) / ray.direction.z;

			if (tzmin > tzmax)
			{
				std::swap(tzmin, tzmax);
			}

			if ((tmin > tzmax) || (tzmin > tmax))
			{
				return false;
			}

			tmin = std::max(tmin, tzmin);
			tmax = std::min(tmax, tzmax);

			outIntersectionPoint = ray.origin + ray.direction * tmin;

			// Calculate the normal at the intersection point
			if (outIntersectionPoint.x == m_min.x)
				normal = glm::fvec3(-1, 0, 0);
			else if (outIntersectionPoint.x == m_max.x)
				normal = glm::fvec3(1, 0, 0);
			else if (outIntersectionPoint.y == m_min.y)
				normal = glm::fvec3(0, -1, 0);
			else if (outIntersectionPoint.y == m_max.y)
				normal = glm::fvec3(0, 1, 0);
			else if (outIntersectionPoint.z == m_min.z)
				normal = glm::fvec3(0, 0, -1);
			else if (outIntersectionPoint.z == m_max.z)
				normal = glm::fvec3(0, 0, 1);

			return true;
		}


		const glm::fvec3& GetMin() const
		{
			return m_min;
		}

		float GetSizeX() const
		{
			return m_max.x - m_min.x;
		}

		float GetSizeY() const
		{
			return m_max.y - m_min.y;
		}

		float GetSizeZ() const
		{
			return m_max.z - m_min.z;
		}

		const glm::fvec3& GetMax() const
		{
			return m_max;
		}

		void SetMin(const glm::fvec3& min)
		{
			m_min = min;
		}

		glm::fvec3 GetCenter() const
		{
			return (m_min + m_max) * 0.5f;
		}

		void SetMax(const glm::fvec3& max)
		{
			m_max = max;
		}

		void Set(const glm::fvec3& min, const glm::fvec3& max)
		{
			m_min = min;
			m_max = max;
		}

		void Set(float x, float y, float z, float w, float h, float d)
		{
			m_min = { x, y, z };
			m_max = { x + w, y + h, z + d };
		}

		void Set(const AABB& other)
		{
			m_min = other.GetMin();
			m_max = other.GetMax();
		}

		void Translate(const glm::fvec3& other)
		{
			m_min += other;
			m_max += other;
		}

		void Transform(const glm::fmat4& matrix)
		{
			glm::fvec4 min(m_min, 1);
			glm::fvec4 max(m_max, 1);

			min = matrix * min;
			max = matrix * max;

			m_min = glm::fvec3(min);
			m_max = glm::fvec3(max);
		}

		void Scale(const glm::fvec3& other)
		{
			m_min *= other;
			m_max *= other;
		}

		void Scale(float scalar)
		{
			m_min *= scalar;
			m_max *= scalar;
		}

		void Expand(const glm::fvec3& other)
		{
			m_min -= other;
			m_max += other;
		}

		void Expand(float scalar)
		{
			m_min -= scalar;
			m_max += scalar;
		}

		static AABB Union(const AABB& a, const AABB& b)
		{
			glm::fvec3 min, max;
			min.x = std::min(a.GetMin().x, b.GetMin().x);
			min.y = std::min(a.GetMin().y, b.GetMin().y);
			min.z = std::min(a.GetMin().z, b.GetMin().z);

			max.x = std::max(a.GetMax().x, b.GetMax().x);
			max.y = std::max(a.GetMax().y, b.GetMax().y);
			max.z = std::max(a.GetMax().z, b.GetMax().z);
			return AABB(min, max);
		}

		bool Contains(const glm::fvec3& point) const
		{
			return point.x >= m_min.x && point.x <= m_max.x &&
				   point.y >= m_min.y && point.y <= m_max.y &&
				   point.z >= m_min.z && point.z <= m_max.z;
		}

		bool Contains(const AABB& other) const
		{
			return other.GetMin().x >= m_min.x && other.GetMax().x <= m_max.x &&
				   other.GetMin().y >= m_min.y && other.GetMax().y <= m_max.y &&
				   other.GetMin().z >= m_min.z && other.GetMax().z <= m_max.z;

		}

	private:
		glm::fvec3 m_min;
		glm::fvec3 m_max;

	};

}