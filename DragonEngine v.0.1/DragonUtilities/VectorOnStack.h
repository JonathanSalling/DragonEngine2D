#pragma once

namespace DragonUtilities
{
	template <typename Type, int size, typename CountType = unsigned short>

	class VectorOnStack
	{
	public:
		VectorOnStack();
		VectorOnStack(const VectorOnStack& aVectorOnStack);
		~VectorOnStack();
		inline void Add(const Type& aObject);
		inline void Insert(const CountType aIndex, const Type& aObject);

		VectorOnStack& operator=(const VectorOnStack& aVectorOnStack);

		inline const Type& operator[](const CountType aIndex) const;
		inline Type& operator[](const CountType aIndex);
		inline void RemoveCyclic(const Type& aObject);
		inline void RemoveCyclicAtIndex(const CountType aIndex);
		inline void Clear();
		inline CountType Size() const;
	};
	template<typename Type, int size, typename CountType>
	inline VectorOnStack<Type, size, CountType>::VectorOnStack()
	{

	}

	template<typename Type, int size, typename CountType>
	inline VectorOnStack<Type, size, CountType>::VectorOnStack(const VectorOnStack& aVectorOnStack)
	{

	}
	template<typename Type, int size, typename CountType>
	inline VectorOnStack<Type, size, CountType>::~VectorOnStack()
	{

	}

	template<typename Type, int size, typename CountType>
	inline VectorOnStack<Type, size, CountType>& VectorOnStack<Type, size, CountType>::operator=(const VectorOnStack& aVectorOnStack)
	{
		return *this;
	}

	template<typename Type, int size, typename CountType>
	inline const Type& VectorOnStack<Type, size, CountType>::operator[](const CountType aIndex) const
	{
		return Type();
	}

	template<typename Type, int size, typename CountType>
	inline Type& VectorOnStack<Type, size, CountType>::operator[](const CountType aIndex)
	{
		return Type();
	}

	template<typename Type, int size, typename CountType>
	inline void VectorOnStack<Type, size, CountType>::Add(const Type& aObject)
	{

	}
	template<typename Type, int size, typename CountType>
	inline void VectorOnStack<Type, size, CountType>::Insert(const CountType aIndex, const Type& aObject)
	{


	}
	template<typename Type, int size, typename CountType>
	inline void VectorOnStack<Type, size, CountType>::RemoveCyclic(const Type& aObject)
	{

	}
	template<typename Type, int size, typename CountType>
	inline void VectorOnStack<Type, size, CountType>::RemoveCyclicAtIndex(const CountType aIndex)
	{

	}
	template<typename Type, int size, typename CountType>
	inline void VectorOnStack<Type, size, CountType>::Clear()
	{

	}
	template<typename Type, int size, typename CountType>
	inline CountType VectorOnStack<Type, size, CountType>::Size() const
	{
		return 0;
	}
}