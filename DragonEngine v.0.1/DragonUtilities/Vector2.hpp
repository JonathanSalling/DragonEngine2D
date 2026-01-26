#pragma once

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

	}
	//Returns the vector difference of aVector0 and aVector1
	template <class T> Vector2<T> operator-(const Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{

	}
	//Returns the vector aVector multiplied by the scalar aScalar
	template <class T> Vector2<T> operator*(const Vector2<T>& aVector, const T& aScalar)
	{
		aVector; aScalar;
		return Vector2<T>();
	}
	//Returns the vector aVector multiplied by the scalar aScalar
	template <class T> Vector2<T> operator*(const T& aScalar, const Vector2<T>& aVector)
	{

	}
	//Returns the vector aVector divided by the scalar aScalar (equivalent to aVectormultiplied by 1 / aScalar)
	template <class T> Vector2<T> operator/(const Vector2<T>& aVector, const T& aScalar)
	{

	}
	//Equivalent to setting aVector0 to (aVector0 + aVector1)
	template <class T> void operator+=(Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		aVector0; aVector1;
	}
	//Equivalent to setting aVector0 to (aVector0 - aVector1)
	template <class T> void operator-=(Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{

	}
	//Equivalent to setting aVector to (aVector * aScalar)
	template <class T> void operator*=(Vector2<T>& aVector, const T& aScalar)
	{

	}
	//Equivalent to setting aVector to (aVector / aScalar)
	template <class T> void operator/=(Vector2<T>& aVector, const T& aScalar)
	{

	}
	template<class T>
	inline Vector2<T>::Vector2()
	{

	}
	template<class T>
	inline Vector2<T>::Vector2(const T& aX, const T& aY)
	{
		aX; aY;
	}
	template<class T>
	inline T Vector2<T>::LengthSqr() const
	{

	}
	template<class T>
	inline T Vector2<T>::Length() const
	{

	}
	template<class T>
	inline Vector2<T> Vector2<T>::GetNormalized() const
	{

	}
	template<class T>
	inline void Vector2<T>::Normalize()
	{

	}
	template<class T>
	inline T Vector2<T>::Dot(const Vector2<T>& aVector) const // not 2 vectors??
	{

	}
}