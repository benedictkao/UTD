#pragma once

#include <stdexcept>

namespace utd
{
	template <typename T, int size>
	class array
	{
	private:
		T innerArray[size];

	public:
		void set(int index, T value)
		{
			if (index < 0 || index >= size)
				throw std::out_of_range("Index out of bounds");
			innerArray[index] = value;
		}

		T get(int index)
		{
			if (index < 0 || index >= size)
				throw std::out_of_range("Index out of bounds");
			return innerArray[index];
		}
	};
}