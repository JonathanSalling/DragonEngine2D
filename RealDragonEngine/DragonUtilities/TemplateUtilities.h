#pragma once
#include <cassert>

namespace DragonUtilities
{
	template <typename T> // returns the larger of two values
	T Max(const T aFirstValue, const T aSecondValue)
	{
		if (aFirstValue > aSecondValue)
			return aFirstValue;
		else if (aSecondValue > aFirstValue)
			return aSecondValue;
		else if (aFirstValue == aSecondValue)
			return aFirstValue;
	}

	template <typename T> // returns the smaller of two values
	T Min(const T aFirstValue, const T aSecondValue)
	{
		if (aFirstValue < aSecondValue)
			return aFirstValue;
		else if (aSecondValue < aFirstValue)
			return aSecondValue;
		else if (aFirstValue == aSecondValue)
			return aFirstValue;
	}

	template <typename T> // returns the absolute value
	T Abs(const T aValue)
	{
		if (aValue >= 0)
			return aValue;
		else if (aValue < 0)
			return aValue * -1;
	}

	template <typename T> // clamps a value between a minimum and maximum
	T Clamp(const T aMin, const T aMax, const T aValue)
	{
		assert(aMin < aMax && "Minimum value can't be larger than the maximum!");

		if (aValue >= aMax)
			return aMax;
		else if (aValue <= aMin)
			return aMin;
		else
			return aValue;

	}

	template <typename T> // linear interpolation between two values
	T Lerp(const T aFirstValue, const T aSecondValue, float aLerpValue) // interpret lerp value as a percentage
	{
			return aFirstValue + (aSecondValue - aFirstValue) * aLerpValue;
	}

	template <typename T>
	void Swap(T& aFirstData, T& aSecondData) // swaps two values
	{
		T temp = aSecondData;

		aSecondData = aFirstData;

		aFirstData = temp;
	}
}