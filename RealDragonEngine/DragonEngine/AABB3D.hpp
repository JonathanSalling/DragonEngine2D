#pragma once
#include "Vector3.hpp"

namespace DragonEngine
{
	template <class T>
	class AABB3D
	{
	public:
		AABB3D();
		AABB3D(const AABB3D<T>& aAABB3D);
		AABB3D(const Vector3<T>& aMin, const Vector3<T>& aMax);
		void InitWithMinAndMax(const Vector3<T>& aMin, const Vector3<T>& aMax);
		bool IsInside(const Vector3<T>& aPosition) const;
	private:
		Vector3<T> myMin;
		Vector3<T> myMax;
	};

	template <class T>
	AABB3D<T>::AABB3D()
	{
		myMin = { 0,0,0 };
		myMax = { 0,0,0 };
	}

	template <class T>
	AABB3D<T>::AABB3D(const AABB3D<T>& aAABB3D)
	{
		myMin = aAABB3D.myMin;
		myMax = aAABB3D.myMax;
	}

	template <class T>
	AABB3D<T>::AABB3D(const Vector3<T>& aMin, const Vector3<T>& aMax)
	{
		myMin = aMin;
		myMax = aMax;
	}

	template <class T>
	void AABB3D<T>::InitWithMinAndMax(const Vector3<T>& aMin, const Vector3<T>& aMax)
	{
		myMin = aMin;
		myMax = aMax;
	}

	template <class T>
	bool AABB3D<T>::IsInside(const Vector3<T>& aPosition) const
	{
		if (myMin.x <= aPosition.x && myMax.x >= aPosition.x && myMin.z <= aPosition.y && myMax.y >= aPosition.y && myMin.z <= aPosition.z && myMax.z >= aPosition.z)
		{
			return true;
		}
		return false;
	}
}