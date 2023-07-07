#include "String.h"

#include <cstring>	// should this be removed?

utd::string::string(const char* s)
{
	str_size = strlen(s);
	arr_size = str_size + 1;
	inner_array = new char[arr_size];
	strcpy(inner_array, s);
}

utd::string::string(const utd::string& s)
{
	str_size = s.str_size;
	arr_size = s.arr_size;
	inner_array = new char[arr_size];
	strcpy(inner_array, s.inner_array);
}

utd::string::string(utd::string&& s) noexcept
{
	str_size = s.str_size;
	arr_size = s.arr_size;
	inner_array = s.inner_array;
	s.inner_array = nullptr;
	s.str_size = 0;
	s.arr_size = 0;
}

utd::string& utd::string::operator=(const utd::string& s)
{
	str_size = s.str_size;
	arr_size = s.arr_size;
    delete[] inner_array;
	inner_array = new char[arr_size];
	strcpy(inner_array, s.inner_array);
	return *this;
}

utd::string& utd::string::operator=(utd::string&& s) noexcept
{
	str_size = s.str_size;
	arr_size = s.arr_size;
    delete[] inner_array;
	inner_array = s.inner_array;
	s.inner_array = nullptr;
	s.str_size = 0;
	s.arr_size = 0;
	return *this;
}

utd::string::~string()
{
	delete[] inner_array;
}

char& utd::string::operator[](size_t index)
{
	return inner_array[index];	// TODO: what if index > str_size but < arr_size?
}

const char& utd::string::operator[](size_t index) const
{
	return inner_array[index];	// TODO: what if index > str_size but < arr_size?
}

size_t utd::string::size() const
{
	return str_size;
}

const char* utd::string::c_str() const
{
	return inner_array;
}

void utd::string::reserve(size_t new_size)
{
	if (new_size <= arr_size - 1)
	{
		return;
	}
	arr_size = new_size + 1;
	char* new_array = new char[arr_size];
	strcpy(new_array, inner_array);
	delete[] inner_array;
	inner_array = new_array;
}

utd::string utd::string::substr(size_t start, size_t len)
{
	utd::string sub;
	sub.str_size = len;
	sub.arr_size = len + 1;
	sub.inner_array = new char[sub.arr_size];
	memcpy(sub.inner_array, this->inner_array + start, len * sizeof(char));
	*(sub.inner_array + len) = 0;
	return sub;
}

utd::string utd::string::operator+(const utd::string& rhs) const
{
	utd::string lhs;
	lhs.str_size = str_size + rhs.str_size;
	lhs.arr_size = lhs.str_size + 1;

	lhs.inner_array = new char[lhs.arr_size];
	strcpy(lhs.inner_array, inner_array);
	strcpy(lhs.inner_array + str_size, rhs.inner_array);
	return lhs;
}

utd::string& utd::string::operator+=(const utd::string& rhs)
{
	size_t combined_str_size = str_size + rhs.str_size;
	reserve(combined_str_size);
	strcpy(inner_array + str_size, rhs.inner_array);
	str_size = combined_str_size;
	return *this;
}

utd::string utd::string::operator+(const char& rhs) const
{
	utd::string lhs;
	lhs.str_size = str_size + 1;
	lhs.arr_size = arr_size + 1;

	lhs.inner_array = new char[lhs.arr_size];
	strcpy(lhs.inner_array, inner_array);
	*(lhs.inner_array + str_size) = rhs;			// replace null termination with rhs char
	*(lhs.inner_array + str_size + 1) = 0;			// add back null termination
	return lhs;
}

utd::string& utd::string::operator+=(const char& rhs)
{
	reserve(str_size + 1);
	*(inner_array + str_size) = rhs;		// replace null termination with rhs char
	*(inner_array + str_size + 1) = 0;		// add back null termination
	str_size++;
	return *this;
}

bool utd::operator==(const string& lhs, const string& rhs)
{
	if (lhs.str_size != rhs.str_size) return false;

	for (int i = 0; i < lhs.str_size; i++)
		if (lhs[i] != rhs[i]) return false;

	return true;
}

std::ostream& utd::operator<<(std::ostream& os, const utd::string& s)
{
	os << s.inner_array;
	return os;
}
