#pragma once
#include "Vector3.hpp"
namespace DragonEngine
{
	template<class T>
	class Plane
	{
	public:
		Plane();
		Plane(const Vector3<T>& aPoint0, const Vector3<T>& aPoint1, const Vector3<T>& aPoint2);
		Plane(const Vector3<T>& aPoint0, const Vector3<T>& aNormal);
		void InitWith3Points(const Vector3<T>& aPoint0, const Vector3<T>& aPoint1, const Vector3<T>& aPoint2);
		void InitWithPointAndNormal(const Vector3<T>& aPoint, const Vector3<T>& aNormal);
		bool IsInside(const Vector3<T>& aPosition) const;
		const Vector3<T>& GetNormal() const;
		const Vector3<T>& GetPoint() const;
	private:
		Vector3<T> myPoint;
		Vector3<T> myNormal;
	};

	template <class T>
	Plane<T>::Plane()
	{
		myPoint = Vector3<T>(0, 0, 0);
		myNormal = Vector3<T>(0, 1, 0);
	}

	template <class T>
	Plane<T>::Plane(const Vector3<T>& aPoint0, const Vector3<T>& aPoint1, const Vector3<T>& aPoint2)
	{
		InitWith3Points(aPoint0, aPoint1, aPoint2);
	}

	template <class T>
	Plane<T>::Plane(const Vector3<T>& aPoint0, const Vector3<T>& aNormal)
	{
		InitWithPointAndNormal(aPoint0, aNormal);
	}

	template <class T>
	void Plane<T>::InitWith3Points(const Vector3<T>& aPoint0, const Vector3<T>& aPoint1, const Vector3<T>& aPoint2)
	{
		myPoint = aPoint0;
		Vector3<T> dirA = aPoint1 - aPoint0;
		Vector3<T> dirB = aPoint2 - aPoint0;
		myNormal = dirA.Cross(dirB);
	}

	template <class T>
	void Plane<T>::InitWithPointAndNormal(const Vector3<T>& aPoint, const Vector3<T>& aNormal)
	{
		myPoint = aPoint;;
		myNormal = aNormal;
	}

	template <class T>
	bool Plane<T>::IsInside(const Vector3<T>& aPosition) const
	{
		const Vector3<T> myDirection = aPosition - myPoint;

		const T dotProduct = myDirection.Dot(GetNormal());

		if (dotProduct < 0)
		{
			return true;
		}
		else if (dotProduct > 0)
		{
			return false;
		}
		return true; // If the dot product is 0, the position is exactly on the plane, we consider it to be inside
	}

	template <class T>
	const Vector3<T>& Plane<T>::GetNormal() const
	{
		return myNormal;
	}

	template<class T>
	inline const Vector3<T>& Plane<T>::GetPoint() const
	{
		return myPoint;
	}

}