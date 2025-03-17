#pragma once

#include "vec.h"

#include <algorithm>

namespace rzml {

	template <typename T>
	class Rect
	{
	public:
		Rect(T x, T y, T w, T h)
			: m_position(x, y),
			m_size(w, h)
		{
			computeCenter();
		}

		Rect(const Vec2<T> pos, const Vec2<T> size)
			: m_position(pos), m_size(size)
		{
			computeCenter();
		}

		Rect(const Rect<T>& other)
			: m_position(other.GetX(), other.GetY()), m_size(other.GetW(), other.GetH())
		{
			computeCenter();
		}

		Rect()
		{

		}

		Vec2<T> GetMin() const
		{
			return m_position;
		}

		Vec2<T> GetMax() const
		{
			return m_position + m_size;
		}

		void SetPosition(Vec2<T> new_pos)
		{
			m_position = new_pos;
			computeCenter();
		}

		void SetPosition(T x, T y)
		{
			m_position.Set(x, y);
			computeCenter();
		}

		void SetSize(T w, T h)
		{
			m_size.Set(w, h);
			computeCenter();
		}

		const Vec2<T>& GetPosition() const
		{
			return m_position;
		}

		const Vec2<T>& GetCenter() const
		{
			return m_center;
		}

		void SetX(T new_x)
		{
			m_position.SetX(new_x);
			computeCenter();
		}

		void SetY(T new_y)
		{
			m_position.SetY(new_y);
			computeCenter();
		}

		T GetX() const
		{
			return m_position.GetX();
		}

		T GetY() const
		{
			return m_position.GetY();
		}

		T GetW() const
		{
			return m_size.GetX();
		}

		T GetH() const
		{
			return m_size.GetY();
		}

		T GetX1() const
		{
			return GetX();
		}

		T GetX2() const
		{
			return GetX() + GetW();
		}

		T GetY1() const
		{
			return GetY();
		}

		T GetY2() const
		{
			return GetY() + GetH();
		}

		void Move(Vec2<T> delta)
		{
			m_position += delta;
			computeCenter();
		}

		void Move(T dx, T dy)
		{
			Move(Vec2<T>(dx, dy));
		}

		const Vec2<T>& GetSize() const
		{
			return m_size;
		}

	private:
		void computeCenter()
		{
			m_center.Set(GetX() + GetW() / 2, GetY() + GetH() / 2);
		}

		Vec2<T> m_position, m_size, m_center;
	};

	typedef Rect<float> Rectf;
	typedef Rect<int> Recti;

	template <typename T>
	bool Intersect(const Rect<T> a, const Rect<T> b)
	{
		return a.GetX1() < b.GetX2() && a.GetX2() > b.GetX1() &&
			a.GetY1() < b.GetY2() && a.GetY2() > b.GetY1();
	}

	template <typename T>
	bool Intersect(const Rect<T> a, const Vec2<T>& aOffset, const Rect<T> b, const Vec2<T>& bOffset)
	{
		return a.GetX1() + aOffset.GetX() < b.GetX2() + bOffset.GetX() && a.GetX2() + aOffset.GetX() > b.GetX1() + bOffset.GetX() &&
			a.GetY1() + aOffset.GetY() < b.GetY2() + bOffset.GetY() && a.GetY2() + aOffset.GetY() > b.GetY1() + bOffset.GetY();
	}

	template <typename T>
	bool Intersect(const Rect<T> a, const Vec2<T>& aOffset, const Rect<T> b)
	{
		return a.GetX1() + aOffset.GetX() < b.GetX2() && a.GetX2() + aOffset.GetX() > b.GetX1() &&
			a.GetY1() + aOffset.GetY() < b.GetY2() && a.GetY2() + aOffset.GetY() > b.GetY1();
	}

	template <typename T>
	bool Intersect(const Rect<T> a, const Rect<T> b, const Vec2<T>& bOffset)
	{
		return a.GetX1() < b.GetX2() + bOffset.GetX() && a.GetX2() > b.GetX1() + bOffset.GetX() &&
			a.GetY1() < b.GetY2() + bOffset.GetY() && a.GetY2() > b.GetY1() + bOffset.GetY();
	}

	template <typename T>
	float Clamp(T v, T min, T max)
	{
		return std::max(std::min(v, max), min);
	}

	template <typename T>
	Rect<T> Clamp(Rect<T> container, Rect<T> contained)
	{
		Rect<T> rect;
		rect.SetX(Clamp<T>(contained.GetX(), container.GetX(), container.GetX() + container.GetW()));
		rect.SetY(Clamp<T>(contained.GetY(), container.GetY(), container.GetY() + container.GetH()));
		return rect;
	}

}