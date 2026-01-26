#pragma once

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

	}
	//Returns the vector difference of aVector0 and aVector1
	template <class T> Vector4<T> operator-(const Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{

	}
	//Returns the vector aVector multiplied by the scalar aScalar
	template <class T> Vector4<T> operator*(const Vector4<T>& aVector, const T& aScalar)
	{

	}
	//Returns the vector aVector multiplied by the scalar aScalar
	template <class T> Vector4<T> operator*(const T& aScalar, const Vector4<T>& aVector)
	{

	}
	//Returns the vector aVector divided by the scalar aScalar (equivalent to aVectormultiplied by 1 / aScalar)
	template <class T> Vector4<T> operator/(const Vector4<T>& aVector, const T& aScalar)
	{

	}
	//Equivalent to setting aVector0 to (aVector0 + aVector1)
	template <class T> void operator+=(Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{

	}
	//Equivalent to setting aVector0 to (aVector0 - aVector1)
	template <class T> void operator-=(Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{

	}
	//Equivalent to setting aVector to (aVector * aScalar)
	template <class T> void operator*=(Vector4<T>& aVector, const T& aScalar)
	{

	}
	//Equivalent to setting aVector to (aVector / aScalar)
	template <class T> void operator/=(Vector4<T>& aVector, const T& aScalar)
	{

	}
	template<class T>
	inline Vector4<T>::Vector4()
	{

	}
	template<class T>
	inline Vector4<T>::Vector4(const T& aX, const T& aY, const T& aZ, const T& aW)
	{

	}
	template<class T>
	inline T Vector4<T>::LengthSqr() const
	{
		return T();
	}
	template<class T>
	inline T Vector4<T>::Length() const
	{
		return T();
	}
	template<class T>
	inline Vector4<T> Vector4<T>::GetNormalized() const
	{
		return Vector4<T>();
	}
	template<class T>
	inline void Vector4<T>::Normalize()
	{
		
	}
	template<class T>
	inline T Vector4<T>::Dot(const Vector4<T>& aVector) const
	{
		return T();
	}
}