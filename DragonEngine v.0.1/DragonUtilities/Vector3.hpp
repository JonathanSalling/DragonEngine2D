#pragma once

namespace DragonUtilities
{
	template <class T>
	class Vector3
	{
	public:
		T x = 0;
		T y = 0;
		T z = 0;
		//Creates a null-vector
		Vector3<T>();
		//Creates a vector (aX, aY, aZ)
		Vector3<T>(const T& aX, const T& aY, const T& aZ);
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

	}
	//Returns the vector difference of aVector0 and aVector1
	template <class T> Vector3<T> operator-(const Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{

	}
	//Returns the vector aVector multiplied by the scalar aScalar
	template <class T> Vector3<T> operator*(const Vector3<T>& aVector, const T& aScalar)
	{

	}
	//Returns the vector aVector multiplied by the scalar aScalar
	template <class T> Vector3<T> operator*(const T& aScalar, const Vector3<T>& aVector)
	{

	}
	//Returns the vector aVector divided by the scalar aScalar (equivalent to aVectormultiplied by 1 / aScalar)
	template <class T> Vector3<T> operator/(const Vector3<T>& aVector, const T& aScalar)
	{

	}
	//Equivalent to setting aVector0 to (aVector0 + aVector1)
	template <class T> void operator+=(Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{

	}
	//Equivalent to setting aVector0 to (aVector0 - aVector1)
	template <class T> void operator-=(Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{

	}
	//Equivalent to setting aVector to (aVector * aScalar)
	template <class T> void operator*=(Vector3<T>& aVector, const T& aScalar)
	{

	}
	//Equivalent to setting aVector to (aVector / aScalar)
	template <class T> void operator/=(Vector3<T>& aVector, const T& aScalar)
	{

	}
	template<class T>
	inline Vector3<T>::Vector3()
	{

	}
	template<class T>
	inline Vector3<T>::Vector3(const T& aX, const T& aY, const T& aZ)
	{

	}
	template<class T>
	inline T Vector3<T>::LengthSqr() const
	{

	}
	template<class T>
	inline T Vector3<T>::Length() const
	{

	}
	template<class T>
	inline Vector3<T> Vector3<T>::GetNormalized() const
	{

	}
	template<class T>
	inline void Vector3<T>::Normalize()
	{

	}
	template<class T>
	inline T Vector3<T>::Dot(const Vector3<T>& aVector) const
	{

	}
	template<class T>
	inline Vector3<T> Vector3<T>::Cross(const Vector3<T>& aVector) const
	{

	}
}