#pragma once
#include <cmath>
#include <cassert >
#include <type_traits>

namespace DragonEngine
{
	template <class T>
	class Vector3
	{
	public:
		T x = 0;
		T y = 0;
		T z = 0;
		//Creates a null-vector
		Vector3<T>() = default;
		//Creates a vector (aX, aY, aZ)
		Vector3<T>(T aX, T aY, T aZ);
		//Copy constructor (compiler generated)
		Vector3<T>(const Vector3<T>& aVector) = default;
		//Assignment operator (compiler generated)
		Vector3<T>& operator=(const Vector3<T>& aVector3) = default;
		//Destructor (compiler generated)
		~Vector3<T>() = default;
		//Returns the squared length of the vector
		T LengthSqr() const;
		//Returns the length of the vector
		T Length() const;
		//Returns a normalized copy of this
		Vector3<T> GetNormalized() const;
		//Normalizes the vector
		void Normalize();
		//Returns the dot product of this and aVector
		T Dot(const Vector3<T>& aVector) const;
		//Returns the cross product of this and aVector
		Vector3<T> Cross(const Vector3<T>& aVector) const;
	};
	//Returns the vector sum of aVector0 and aVector1
	template <class T> Vector3<T> operator+(const Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		return Vector3<T>(aVector0.x + aVector1.x, aVector0.y + aVector1.y, aVector0.z + aVector1.z);
	}
	//Returns the negation of aVector
	template <class T> Vector3<T> operator-(const Vector3<T>& aVector)
	{
		return Vector3<T>(-aVector.x, -aVector.y, -aVector.z);
	}
	//Returns the vector difference of aVector0 and aVector1
	template <class T> Vector3<T> operator-(const Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		return Vector3<T>(aVector0.x - aVector1.x, aVector0.y - aVector1.y, aVector0.z - aVector1.z);
	}
	//Returns the vector aVector multiplied by the scalar aScalar
	template <class T> Vector3<T> operator*(const Vector3<T>& aVector, const T& aScalar)
	{
		return Vector3<T>(aVector.x * aScalar, aVector.y * aScalar, aVector.z * aScalar);
	}
	//Returns the vector aVector multiplied by the scalar aScalar
	template <class T> Vector3<T> operator*(const T& aScalar, const Vector3<T>& aVector)
	{
		return Vector3<T>(aVector.x * aScalar, aVector.y * aScalar, aVector.z * aScalar);
	}
	//Returns the vector aVector divided by the scalar aScalar (equivalent to aVectormultiplied by 1 / aScalar)
	template <class T> Vector3<T> operator/(const Vector3<T>& aVector, const T& aScalar)
	{
		return Vector3<T>((aVector.x / aScalar), (aVector.y / aScalar), (aVector.z / aScalar));
	}
	//Equivalent to setting aVector0 to (aVector0 + aVector1)
	template <class T>
	Vector3<T>& operator+=(Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		aVector0.x += aVector1.x;
		aVector0.y += aVector1.y;
		aVector0.z += aVector1.z;
		return aVector0;
	}
	//Equivalent to setting aVector0 to (aVector0 - aVector1)
	template <class T>
	Vector3<T>& operator-=(Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		aVector0.x -= aVector1.x;
		aVector0.y -= aVector1.y;
		aVector0.z -= aVector1.z;
		return aVector0;
	}
	//Equivalent to setting aVector to (aVector * aScalar)
	template <class T>
	Vector3<T>& operator*=(Vector3<T>& aVector, const T& aScalar)
	{
		aVector.x *= aScalar;
		aVector.y *= aScalar;
		aVector.z *= aScalar;
		return aVector;
	}
	//Equivalent to setting aVector to (aVector / aScalar)
	template <class T>
	Vector3<T>& operator/=(Vector3<T>& aVector, const T& aScalar)
	{
		aVector.x /= aScalar;
		aVector.y /= aScalar;
		aVector.z /= aScalar;
		return aVector;
	}
	template<class T>
	inline Vector3<T>::Vector3(T aX, T aY, T aZ)
	{
		x = aX;
		y = aY;
		z = aZ;
	}
	template<class T>
	inline T Vector3<T>::LengthSqr() const
	{
		return (x * x) + (y * y) + (z * z);
	}
	template<class T>
	inline T Vector3<T>::Length() const
	{
		return std::sqrt(LengthSqr());
	}
	template<class T>
	inline Vector3<T> Vector3<T>::GetNormalized() const
	{
		static_assert(std::is_floating_point_v<T>, "GetNormalized() requires floating point type");

		T tempLength = Length();
		assert(tempLength != 0);

		return (*this) / tempLength;
	}
	template<class T>
	inline void Vector3<T>::Normalize()
	{
		static_assert(std::is_floating_point_v<T>, "Normalize() requires floating point type");
		T tempLength = Length();
		assert(tempLength != 0);

		(*this) /= tempLength;
	}
	template<class T>
	inline T Vector3<T>::Dot(const Vector3<T>& aVector) const
	{
		return (x * aVector.x) + (y * aVector.y) + (z * aVector.z);
	}
	template<class T>
	inline Vector3<T> Vector3<T>::Cross(const Vector3<T>& aVector) const
	{
		T tempX = (y * aVector.z) - (z * aVector.y);
		T tempY = (z * aVector.x) - (x * aVector.z);
		T tempZ = (x * aVector.y) - (y * aVector.x);

		return Vector3<T>(tempX, tempY, tempZ);
	}

	using Vector3f = Vector3<float>;
	using Vector3d = Vector3<double>;
}

namespace DE = DragonEngine;