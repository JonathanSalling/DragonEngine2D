#pragma once
#include <array>
#include <cassert>

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

	private:
		std::array<Type, size> myArray;
		CountType myCount = 1;

	};
	template<typename Type, int size, typename CountType>
	inline VectorOnStack<Type, size, CountType>::VectorOnStack()
	{
		// TODO: Initialize start values
		myCount = 0;
		myArray.fill(Type{});
	}

	template<typename Type, int size, typename CountType>
	inline VectorOnStack<Type, size, CountType>::VectorOnStack(const VectorOnStack& aVectorOnStack)
	{
		// TODO: Initialize start values using the sent in VectorOnStack
		
		if (aVectorOnStack.myCount == 0)
		{
			myCount = 0;
		}
		else
		{
			for (CountType i = 0; i < aVectorOnStack.myCount; i++)
			{
				// this copies every member variable 1 by 1, though it is limited by copying from and into arrays with identical sizes

				myCount = aVectorOnStack.myCount;
				myArray[i] = aVectorOnStack[i];

			}
		}

	}
	template<typename Type, int size, typename CountType>
	inline VectorOnStack<Type, size, CountType>::~VectorOnStack()
	{
		// TODO: Clean up member variables

		// symbolic count reduction, does its job either way
		Clear();
	}

	template<typename Type, int size, typename CountType>
	inline VectorOnStack<Type, size, CountType>& VectorOnStack<Type, size, CountType>::operator=(const VectorOnStack& aVectorOnStack)
	{
		// TODO: Add what should happen when this VectorOnStack is set equal to another VectorOnStack
		// Returning a VectorOnStack reference (&), keyword (this) can be used to get pointer to this VectorOnStack object

		if (this != &aVectorOnStack) // if the arrays are not already equal
		{
			myCount = aVectorOnStack.myCount; // adjust the count to be the same

			for (int i = 0; i < myCount; i++) // for every index up to the count (which is always 1 higher than the max possible index)
			{
				myArray[i] = aVectorOnStack.myArray[i]; // copy the stored object over
			}
		}
		return *this; // returns a dereferenced, "this" because... it has to?
	}

	template<typename Type, int size, typename CountType>
	inline const Type& VectorOnStack<Type, size, CountType>::operator[](const CountType aIndex) const
	{
		// TODO: Return element at index
		// Make sure the index is valid

		assert(0 <= aIndex < myArray.max_size()); // as long as the index is valid
		return myArray[aIndex]; // return the member at that index

	}

	template<typename Type, int size, typename CountType>
	inline Type& VectorOnStack<Type, size, CountType>::operator[](const CountType aIndex)
	{
		// TODO: Return the element at index
		// Make sure the index is valid

		assert(0 <= aIndex < myArray.max_size()); // as long as the index is valid
		return myArray[aIndex]; // return the member at that index

		// same as above but no const? What's the difference?
	}

	template<typename Type, int size, typename CountType>
	inline void VectorOnStack<Type, size, CountType>::Add(const Type& aObject)
	{
		// TODO: Add an element at the end of the VectorOnStack

		assert(myCount < myArray.max_size()); // as long as the count of stored members does not exceed the maximum

		myArray[myCount] = aObject; // adds the object

		myCount++; // increases the count
	}
	template<typename Type, int size, typename CountType>
	inline void VectorOnStack<Type, size, CountType>::Insert(const CountType aIndex, const Type& aObject)
	{
		// TODO: Insert a element at index in the VectorOnStack

		assert(0 <= aIndex < myArray.max_size()); // as long as the index is of one of the existing members already
		assert(myCount < myArray.max_size());
		
		for (CountType i = myCount; i > aIndex; i--) // iterating from the last member of current array (+1! To accomodate the increase) down to the one before the given index
		{
			myArray[i] = myArray[i - 1]; // copies members from the index before, into the index after
		}
		myArray[aIndex] = aObject; // after the copying is donw, places the new object where it was meant to go
		myCount += 1; // increasing the count

	}
	template<typename Type, int size, typename CountType>
	inline void VectorOnStack<Type, size, CountType>::RemoveCyclic(const Type& aObject)
	{
		// TODO: Remove first element matching aObject
		// TODO: Adjust other elements to fill the gap

		for (CountType i = 0; i < myCount; i++) // iterates through all the stored members
		{
			if (myArray[i] == aObject) // as soon as one matches the value that was sent in
			{
				RemoveCyclicAtIndex(i); // the index was found, so this function can be used, as it removes at index, and "scoots" the other members backwards
			}
		}
	}
	template<typename Type, int size, typename CountType>
	inline void VectorOnStack<Type, size, CountType>::RemoveCyclicAtIndex(const CountType aIndex)
	{
		// TODO: Remove first element at index
		// TODO: Adjust other elements to fill the gap

		assert(myCount != 0);
		assert(0 <= aIndex < myArray.max_size());

		myArray[aIndex] = myArray[myCount - 1]; // the array member at given index is simply replaced by the member at last index
		myCount -= 1; // the number of members (count) goes down
	}
	template<typename Type, int size, typename CountType>
	inline void VectorOnStack<Type, size, CountType>::Clear()
	{
		// TODO: Clear the VectorOnStack

		myCount = 0; // reduces the count to 0, making it so the array is not storing anything
	}
	template<typename Type, int size, typename CountType>
	inline CountType VectorOnStack<Type, size, CountType>::Size() const
	{
		// TODO: Return the size of the VectorOnStack

		return myCount; // the size of this array would equate to how many "slots" are filled, which is what myCount keeps track of.
	}
}