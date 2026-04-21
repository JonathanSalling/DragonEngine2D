#pragma once
#include "Vector3.hpp"

namespace DragonEngine
{
	template <class T>
	class Sphere
	{
	public:
		Sphere();
		Sphere(const Sphere<T>& aSphere);
		Sphere(const Vector3<T>& aCenter, T aRadius);
		bool IsInside(const Vector3<T>& aPosition) const;
		Vector3<T> GetCenter() const;
		T GetRadius() const;
	private:
		Vector3<T> myCenter;
		T myRadius;
	};

	template <class T>
	Sphere<T>::Sphere()
	{
		myCenter = { 0, 0, 0 };
		myRadius = 0;
	}

	template <class T>
	Sphere<T>::Sphere(const Sphere<T>& aSphere)
	{
		myCenter = aSphere.myCenter;
		myRadius = aSphere.myRadius;
	}

	template <class T>
	Sphere<T>::Sphere(const Vector3<T>& aCenter, T aRadius)
	{
		myCenter = aCenter;
		myRadius = aRadius;
	}

	/*template <class T>
	Sphere<T>::Sphere(const Vector3<T>& aCenter, T aRadius)
	{
		myCenter = aCenter;
		myRadius = aRadius;
	}*/

	template <class T>
	bool Sphere<T>::IsInside(const Vector3<T>& aPosition) const
	{
		Vector3<T> distance = aPosition - myCenter;
		return distance.LengthSqr() <= (myRadius * myRadius);
	}

	template <class T>
	T Sphere<T>::GetRadius() const
	{
		return myRadius;
	}

	template <class T>
	Vector3<T> Sphere<T>::GetCenter() const
	{
		return myCenter;
	}
}