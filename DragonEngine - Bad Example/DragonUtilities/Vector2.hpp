#pragma once
#include <iostream>
#include <cmath>

namespace DragonUtilities
{
	template <class T>
	class Vector2
	{
	public:
		T x = 0;
		T y = 0;
		//Creates a null-vector
		Vector2<T>();
		//Creates a vector (aX, aY, aZ)
		Vector2<T>(const T& aX, const T& aY);
		//Copy constructor (compiler generated)
		Vector2<T>(const Vector2<T>& aVector) = default;
		//Assignment operator (compiler generated)
		Vector2<T>& operator=(const Vector2<T>& aVector2) = default;
		//Destructor (compiler generated)
		~Vector2<T>() = default;
		//Returns the squared length of the vector
		T LengthSqr() const;
		//Returns the length of the vector
		T Length() const;
		//Returns a normalized copy of this
		Vector2<T> GetNormalized() const;
		//Normalizes the vector
		void Normalize();
		//Returns the dot product of this and aVector
		T Dot(const Vector2<T>& aVector) const;
	};
	//Returns the vector sum of aVector0 and aVector1
	template <class T> Vector2<T> operator+(const Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{	

		T x = aVector0.x + aVector1.x;
		T y = aVector0.y + aVector1.y;

		return Vector2<T>(x,y);
	}
	//Returns the vector difference of aVector0 and aVector1
	template <class T> Vector2<T> operator-(const Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		T x = aVector0.x - aVector1.x;
		T y = aVector0.y - aVector1.y;

		return Vector2<T>(x,y);
	}
	//Returns the vector aVector multiplied by the scalar aScalar
	template <class T> Vector2<T> operator*(const Vector2<T>& aVector, const T& aScalar)
	{
		T x = aVector.x * aScalar;
		T y = aVector.y * aScalar;

		return Vector2<T>(x,y);
	}
	//Returns the vector aVector multiplied by the scalar aScalar
	template <class T> Vector2<T> operator*(const T& aScalar, const Vector2<T>& aVector)
	{
		T x = aVector.x * aScalar;
		T y = aVector.y * aScalar;

		return Vector2<T>(x, y);
	}
	//Returns the vector aVector divided by the scalar aScalar (equivalent to aVectormultiplied by 1 / aScalar)
	template <class T> Vector2<T> operator/(const Vector2<T>& aVector, const T& aScalar)
	{
		if (aScalar != 0)
		{
			T x = aVector.x / aScalar;
			T y = aVector.y / aScalar;

			return Vector2<T>(x, y);
		}
		else
		{
			return aVector; // this seems like the most logical return if the scalar=0 to me, but idk if itll pass the unit test
		}
	
	}
	//Equivalent to setting aVector0 to (aVector0 + aVector1)
	template <class T> void operator+=(Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		aVector0.x = aVector0.x + aVector1.x;
		aVector0.y = aVector0.y + aVector1.y;
	}
	//Equivalent to setting aVector0 to (aVector0 - aVector1)
	template <class T> void operator-=(Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		aVector0.x = aVector0.x - aVector1.x;
		aVector0.y = aVector0.y - aVector1.y;
	}
	//Equivalent to setting aVector to (aVector * aScalar)
	template <class T> void operator*=(Vector2<T>& aVector, const T& aScalar)
	{
		aVector.x = aVector.x * aScalar;
		aVector.y = aVector.y * aScalar;
	}
	//Equivalent to setting aVector to (aVector / aScalar)
	template <class T> void operator/=(Vector2<T>& aVector, const T& aScalar)
	{
		if (aScalar != 0)
		{
			aVector.x = aVector.x / aScalar;
			aVector.y = aVector.y / aScalar;
		}
		else
		{
			aVector.x = aVector.x;
			aVector.y = aVector.y;
		}
	}
	template<class T>
	inline Vector2<T>::Vector2()
	{
		x = 0;
		y = 0;
	}
	template<class T>
	inline Vector2<T>::Vector2(const T& aX, const T& aY)
	{
		x = aX;
		y = aY;
	}
	template<class T>
	inline T Vector2<T>::LengthSqr() const
	{
		return ((x * x) + (y * y));
	}
	template<class T>
	inline T Vector2<T>::Length() const
	{
		return std::sqrt((x * x) + (y * y));
	}
	template<class T>
	inline Vector2<T> Vector2<T>::GetNormalized() const
	{
		T length = std::sqrt((x * x) + (y * y));
		if (length != 0)
		{
			return Vector2<T>(x/length,y/length);
		}
		else
		{
			return Vector2<T>(x,y);
		}
	}
	template<class T>
	inline void Vector2<T>::Normalize()
	{
		T length = std::sqrt((x * x) + (y * y));
		if (length != 0)
		{
			x = x / length;
			y = y / length;
		}
		else
		{
			x = x;
			y = y;
		}
	}
	template<class T>
	inline T Vector2<T>::Dot(const Vector2<T>& aVector) const // not 2 vectors??
	{
		T dot = ((x * aVector.x) + (y * aVector.y));
		return dot;
	}
}