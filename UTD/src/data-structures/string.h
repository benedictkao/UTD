#pragma once

#include <cstddef>
#include <cstring> // should this be removed?
#include <iostream>

namespace utd
{
	class string
	{
	private:
		char* inner_array = nullptr;
		size_t arr_size = 0;
		size_t str_size = 0;

	public:

		string() = default;

		string(const char* s);

		string(const string& s);

		string(string&& s) noexcept;

		string& operator=(const string& s);

		string& operator=(string&& s) noexcept;

		~string();

		char& operator [](size_t index);

		const char& operator [](size_t index) const;

		size_t size() const;

		const char* c_str() const;

		void reserve(size_t new_size);

		string substr(size_t start, size_t len);

		string operator+(const string& rhs) const;

		string& operator+=(const string& rhs);

		string operator+(const char& rhs) const;

		string& operator+=(const char& rhs);

		friend bool operator==(const string& lhs, const string& rhs);

		friend std::ostream& operator<<(std::ostream& os, const string& s);
	};
}

#include "string.cpp"
