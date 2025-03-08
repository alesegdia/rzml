#pragma once

#include <vector>
#include <stdexcept>

namespace rzml
{

	template <typename T>
	class Matrix3D
	{
	public:
		Matrix3D()
			: m_width(0)
			, m_height(0)
			, m_depth(0)
		{
		}

		Matrix3D(int width, int height, int depth)
			: m_width(width)
			, m_height(height)
			, m_depth(depth)
		{
			m_data = std::vector<T>(width * height * depth, T());
		}

		Matrix3D(T initVal, int width, int height, int depth)
			: m_width(width)
			, m_height(height)
			, m_depth(depth)
		{
			m_data = std::vector<T>(width * height * depth, initVal);
		}

		Matrix3D(std::vector<T> data, int width, int height, int depth)
			: m_width(width)
			, m_height(height)
			, m_depth(depth)
			, m_data(data)
		{
			if (data.size() != width * height * depth)
			{
				throw std::invalid_argument("Matrix3D data size does not match dimensions");
			}
		}

		T& Get(int x, int y, int z)
		{
			CheckBounds(x, y, z);
			return m_data[z * m_width * m_height + y * m_width + x];
		}

		const T& Get(int x, int y, int z) const
		{
			CheckBounds(x, y, z);
			return m_data[z * m_width * m_height + y * m_width + x];
		}

		void Set(int x, int y, int z, const T& value)
		{
			CheckBounds(x, y, z);
			m_data[z * m_width * m_height + y * m_width + x] = value;
		}

		int GetWidth() const
		{
			return m_width;
		}

		int GetHeight() const
		{
			return m_height;
		}

		int GetDepth() const
		{
			return m_depth;
		}

		void Clear(const T& value = T())
		{
			std::fill(m_data.begin(), m_data.end(), value);
		}

		Matrix3D<T> operator+(const Matrix3D<T>& other) const
		{
			CheckDimensions(other);
			Matrix3D<T> result(m_width, m_height, m_depth);
			for (size_t i = 0; i < m_data.size(); ++i)
			{
				result.m_data[i] = m_data[i] + other.m_data[i];
			}
			return result;
		}

		Matrix3D<T> operator-(const Matrix3D<T>& other) const
		{
			CheckDimensions(other);
			Matrix3D<T> result(m_width, m_height, m_depth);
			for (size_t i = 0; i < m_data.size(); ++i)
			{
				result.m_data[i] = m_data[i] - other.m_data[i];
			}
			return result;
		}

		Matrix3D<T> operator*(const Matrix3D<T>& other) const
		{
			CheckDimensions(other);
			Matrix3D<T> result(m_width, m_height, m_depth);
			for (size_t i = 0; i < m_data.size(); ++i)
			{
				result.m_data[i] = m_data[i] * other.m_data[i];
			}
			return result;
		}

		Matrix3D<T> operator/(const Matrix3D<T>& other) const
		{
			CheckDimensions(other);
			Matrix3D<T> result(m_width, m_height, m_depth);
			for (size_t i = 0; i < m_data.size(); ++i)
			{
				if (other.m_data[i] == T())
				{
					throw std::invalid_argument("Division by zero in Matrix3D");
				}
				result.m_data[i] = m_data[i] / other.m_data[i];
			}
			return result;
		}

	private:
		void CheckBounds(int x, int y, int z) const
		{
			if (x < 0 || x >= m_width || y < 0 || y >= m_height || z < 0 || z >= m_depth)
			{
				throw std::out_of_range("Matrix3D index out of bounds");
			}
		}

		void CheckDimensions(const Matrix3D<T>& other) const
		{
			if (m_width != other.m_width || m_height != other.m_height || m_depth != other.m_depth)
			{
				throw std::invalid_argument("Matrix3D dimensions do not match");
			}
		}

		int m_width;
		int m_height;
		int m_depth;
		std::vector<T> m_data;
	};

}