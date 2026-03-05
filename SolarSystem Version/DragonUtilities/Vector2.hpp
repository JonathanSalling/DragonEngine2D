#pragma once
#include <cmath>
#include <assert.h>

namespace DragonUtilities
{
	template <class T>
	class Vector2
	{
	public:
		T x, y;
		//Creates a null-vector
		Vector2<T>() = default;
		//Creates a vector (aX, aY)
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
		return Vector2<T>(aVector0.x + aVector1.x, aVector0.y + aVector1.y);
	}
	//Returns the vector difference of aVector0 and aVector1
	template <class T> Vector2<T> operator-(const Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		return Vector2<T>(aVector0.x - aVector1.x, aVector0.y - aVector1.y);
	}
	//Returns the vector aVector multiplied by the scalar aScalar
	template <class T> Vector2<T> operator*(const Vector2<T>& aVector, const T& aScalar)
	{
		return Vector2<T>(aVector.x * aScalar, aVector.y * aScalar);
	}
	//Returns the vector aVector multiplied by the scalar aScalar
	template <class T> Vector2<T> operator*(const T& aScalar, const Vector2<T>& aVector)
	{
		return Vector2<T>(aVector.x * aScalar, aVector.y * aScalar);
	}
	//Returns the vector aVector divided by the scalar aScalar (equivalent to aVectormultiplied by 1 / aScalar)
	template <class T> Vector2<T> operator/(const Vector2<T>& aVector, const T& aScalar)
	{
		return Vector2<T>((aVector.x / aScalar), (aVector.y / aScalar));
	}
	//Equivalent to setting aVector0 to (aVector0 + aVector1)
	template <class T>
	Vector2<T>& operator+=(Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		aVector0.x += aVector1.x;
		aVector0.y += aVector1.y;
		return aVector0;
	}
	//Equivalent to setting aVector0 to (aVector0 - aVector1)
	template <class T>
	Vector2<T>& operator-=(Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		aVector0.x -= aVector1.x;
		aVector0.y -= aVector1.y;
		return aVector0;
	}
	//Equivalent to setting aVector to (aVector * aScalar)
	template <class T>
	Vector2<T>& operator*=(Vector2<T>& aVector, const T& aScalar)
	{
		aVector.x *= aScalar;
		aVector.y *= aScalar;
		return aVector;
	}
	//Equivalent to setting aVector to (aVector / aScalar)
	template <class T>
	Vector2<T>& operator/=(Vector2<T>& aVector, const T& aScalar)
	{
		aVector.x /= aScalar;
		aVector.y /= aScalar;
		return aVector;
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
		return T((x * x) + (y * y));
	}
	template<class T>
	inline T Vector2<T>::Length() const
	{
		return T(std::sqrt(Length()));
	}
	template<class T>
	inline Vector2<T> Vector2<T>::GetNormalized() const
	{
		static_assert(std::is_floating_point_v<T>, "GetNormalized() requires floating point type");

		T tempLength = Length();
		assert(tempLength != 0);

		return (*this) / tempLength;
	}
	template<class T>
	inline void Vector2<T>::Normalize()
	{
		static_assert(std::is_floating_point_v<T>, "Normalize() requires floating point type");
		T tempLength = Length();
		assert(tempLength != 0);

		(*this) /= tempLength;
	}
	template<class T>
	inline T Vector2<T>::Dot(const Vector2<T>& aVector) const
	{
		return T((x * aVector.x) + (y * aVector.y));
	}

	using Vector2f = Vector2<float>;
	using Vector2d = Vector2<double>;
}

namespace DU = DragonUtilities;