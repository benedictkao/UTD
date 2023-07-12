#pragma once

namespace utd
{

	/*
	* Improvements:
	* 1. Return T& instead of T to avoid copying the object each time it is accessed (also allows objects in the array to get mutated)
	* 2. Get is a const function and returns const reference so that it can be used in other const functions
	* 3. Use size_t instead of int for better consistency
	*/

	template <typename T, size_t array_size>
	class array
	{
	private:
		T innerArray[array_size];

	public:
		constexpr int size() { return array_size; }

		/*
		* Return mutable reference for both set and get
		*/
		T& operator [](size_t index)
		{
			return innerArray[index];
		}

		/*
		* Return immutable reference for get operations only. Useful for const functions
		*/
		const T& operator [](size_t index) const
		{
			return innerArray[index];
		}
	};
}