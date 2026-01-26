#pragma once
#include <iostream>
#include <cmath>

namespace DragonUtilities
{
	template <class T>
	class Vector4
	{
	public:
		T x = 0;
		T y = 0;
		T z = 0;
		T w = 0;
		//Creates a null-vector
		Vector4<T>();
		//Creates a vector (aX, aY, aZ, aW)
		Vector4<T>(const T& aX, const T& aY, const T& aZ, const T& aW);
		//Copy constructor (compiler generated)
		Vector4<T>(const Vector4<T>& aVector) = default;
		//Assignment operator (compiler generated)
		Vector4<T>& operator=(const Vector4<T>& aVector4) = default;
		//Destructor (compiler generated)
		~Vector4<T>() = default;
		//Returns the squared length of the vector
		T LengthSqr() const;
		//Returns the length of the vector
		T Length() const;
		//Returns a normalized copy of this
		Vector4<T> GetNormalized() const;
		//Normalizes the vector
		void Normalize();
		//Returns the dot product of this and aVector
		T Dot(const Vector4<T>& aVector) const;
	};
	//Returns the vector sum of aVector0 and aVector1
	template <class T> Vector4<T> operator+(const Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		T x = aVector0.x + aVector1.x;
		T y = aVector0.y + aVector1.y;
		T z = aVector0.z + aVector1.z;
		T w = aVector0.w + aVector1.w;

		return Vector4<T>(x, y, z, w);
	}
	//Returns the vector difference of aVector0 and aVector1
	template <class T> Vector4<T> operator-(const Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		T x = aVector0.x - aVector1.x;
		T y = aVector0.y - aVector1.y;
		T z = aVector0.z - aVector1.z;
		T w = aVector0.w - aVector1.w;

		return Vector4<T>(x, y, z, w);
	}
	//Returns the vector aVector multiplied by the scalar aScalar
	template <class T> Vector4<T> operator*(const Vector4<T>& aVector, const T& aScalar)
	{
		T x = aVector.x * aScalar;
		T y = aVector.y * aScalar;
		T z = aVector.z * aScalar;
		T w = aVector.w * aScalar;

		return Vector4<T>(x, y, z, w);
	}
	//Returns the vector aVector multiplied by the scalar aScalar
	template <class T> Vector4<T> operator*(const T& aScalar, const Vector4<T>& aVector)
	{
		T x = aVector.x * aScalar;
		T y = aVector.y * aScalar;
		T z = aVector.z * aScalar;
		T w = aVector.w * aScalar;

		return Vector4<T>(x, y, z, w);
	}
	//Returns the vector aVector divided by the scalar aScalar (equivalent to aVectormultiplied by 1 / aScalar)
	template <class T> Vector4<T> operator/(const Vector4<T>& aVector, const T& aScalar)
	{
		if (aScalar != 0)
		{
			T x = aVector.x / aScalar;
			T y = aVector.y / aScalar;
			T z = aVector.z / aScalar;
			T w = aVector.w / aScalar;

			return Vector4<T>(x, y, z, w);
		}
		else
		{
			return aVector;
		}
	}
	//Equivalent to setting aVector0 to (aVector0 + aVector1)
	template <class T> void operator+=(Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		aVector0.x = aVector0.x + aVector1.x;
		aVector0.y = aVector0.y + aVector1.y;
		aVector0.z = aVector0.z + aVector1.z;
		aVector0.w = aVector0.w + aVector1.w;
	}
	//Equivalent to setting aVector0 to (aVector0 - aVector1)
	template <class T> void operator-=(Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		aVector0.x = aVector0.x - aVector1.x;
		aVector0.y = aVector0.y - aVector1.y;
		aVector0.z = aVector0.z - aVector1.z;
		aVector0.w = aVector0.w - aVector1.w;
	}
	//Equivalent to setting aVector to (aVector * aScalar)
	template <class T> void operator*=(Vector4<T>& aVector, const T& aScalar)
	{
		aVector.x = aVector.x * aScalar;
		aVector.y = aVector.y * aScalar;
		aVector.z = aVector.z * aScalar;
		aVector.w = aVector.w * aScalar;
	}
	//Equivalent to setting aVector to (aVector / aScalar)
	template <class T> void operator/=(Vector4<T>& aVector, const T& aScalar)
	{
		if (aScalar != 0)
		{
			aVector.x = aVector.x / aScalar;
			aVector.y = aVector.y / aScalar;
			aVector.z = aVector.z / aScalar;
			aVector.w = aVector.w / aScalar;
		}
		else
		{
			aVector.x = aVector.x;
			aVector.y = aVector.y;
			aVector.z = aVector.z;
			aVector.w = aVector.w;
		}
	}
	template<class T>
	inline Vector4<T>::Vector4()
	{
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	}
	template<class T>
	inline Vector4<T>::Vector4(const T& aX, const T& aY, const T& aZ, const T& aW)
	{
		x = aX;
		y = aY;
		z = aZ;
		w = aW;
	}
	template<class T>
	inline T Vector4<T>::LengthSqr() const
	{
		return ((x * x) + (y * y) + (z * z) + (w * w));
	}
	template<class T>
	inline T Vector4<T>::Length() const
	{
		return std::sqrt((x * x) + (y * y) + (z * z) + (w * w));
	}
	template<class T>
	inline Vector4<T> Vector4<T>::GetNormalized() const
	{
		T length = std::sqrt((x * x) + (y * y) + (z * z) + (w * w));

		if (length != 0)
		{
			return Vector4<T>(x / length, y / length, z / length, w/length);
		}
		else
		{
			return Vector4<T>(x, y, z, w);
		}
	}
	template<class T>
	inline void Vector4<T>::Normalize()
	{
		T length = std::sqrt((x * x) + (y * y) + (z * z) + (w * w));
		if (length != 0)
		{
			x = x / length;
			y = y / length;
			z = z / length;
			w = w / length;
		}
		else
		{
			x = x;
			y = y;
			z = z;
			w = w;
		}
	}
	template<class T>
	inline T Vector4<T>::Dot(const Vector4<T>& aVector) const
	{
		T dot = ((x * aVector.x) + (y * aVector.y) + (z * aVector.z) + (w * aVector.w));
		return dot;
	}
}