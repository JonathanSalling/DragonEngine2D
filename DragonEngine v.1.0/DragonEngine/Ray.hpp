#pragma once
#include "Vector3.hpp"

namespace DragonEngine
{
	template <class T>
	class Ray
	{
	public:
		Ray();
		Ray(const Ray<T>& aRay);
		Ray(const Vector3<T>& aOrigin, const Vector3<T>& aPoint);
		void InitWith2Points(const Vector3<T>& aOrigin, const Vector3<T>& aPoint);
		void InitWithOriginAndDirection(const Vector3<T>& aOrigin, const Vector3<T>& aDirection);
		const Vector3<T> GetDirection() const;
		const Vector3<T> GetOrigin() const;
	private:
		Vector3<T> myOrigin;
		Vector3<T> myDirection;
	};

	template <class T>
	Ray<T>::Ray()
	{
		myOrigin = { 0,0,0 };
		myDirection = { 0,0,0 };
	}

	template <class T>
	Ray<T>::Ray(const Ray<T>& aRay)
	{
		myOrigin = aRay.myOrigin;
		myDirection = aRay.myDirection;
	}

	template <class T>
	Ray<T>::Ray(const Vector3<T>& aOrigin, const Vector3<T>& aPoint)
	{
		myOrigin = aOrigin;
		myDirection = aPoint - myOrigin;
		myDirection.Normalize();
	}

	template <class T>
	void Ray<T>::InitWith2Points(const Vector3<T>& aOrigin, const Vector3<T>& aPoint)
	{
		myOrigin = aOrigin;
		myDirection = aPoint - myOrigin;
		myDirection.Normalize();
	}

	template <class T>
	void Ray<T>::InitWithOriginAndDirection(const Vector3<T>& aOrigin, const Vector3<T>& aDirection)
	{
		myOrigin = aOrigin;
		myDirection = aDirection;
	}

	template <class T>
	const Vector3<T> Ray<T>::GetDirection() const
	{
		return myDirection;
	}

	template <class T>
	const Vector3<T> Ray<T>::GetOrigin() const
	{
		return myOrigin;
	}
}