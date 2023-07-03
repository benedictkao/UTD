#include "String32.h"

#include <cstring>

/*
* Size of string is 32:
* 
* Large string:
* - 8 bytes for data pointer -> points to heap memory
* - 8 bytes for size
* - 8 bytes for capacity
* - 8 bytes spare space
* 
* Small string:
* - 8 bytes for data pointer -> points to capacity (which is used to start char array in small string)
* - 8 bytes for size
* - 16 bytes for char array (last element must be null terminator)
*/
constexpr uint8_t SMALL_STRING_MAX_LENGTH = 15;

uint8_t& utd::string32::getStringTypeFlag()
{
	return *((uint8_t*)(&_capacity) + SMALL_STRING_MAX_LENGTH);
}

uint8_t& utd::string32::getStringTypeFlag() const
{
	return *((uint8_t*)(&_capacity) + SMALL_STRING_MAX_LENGTH);
}

bool utd::string32::isLargeString() const
{
	return getStringTypeFlag() & STRING_TYPE::LARGE;
}

void utd::string32::setType(utd::string32::STRING_TYPE type)
{
	getStringTypeFlag() = type;
}

utd::string32::string32(const char* s)
{
	_size = strlen(s);
	if (_size > SMALL_STRING_MAX_LENGTH) 
	{
		_capacity = _size + 1;
		_data = new char[_capacity];
		setType(utd::string32::STRING_TYPE::LARGE);
	}
	else 
	{
		_data = (char*) &_capacity;
	}
	strcpy(_data, s);
}

utd::string32::~string32()
{
	if (isLargeString())
	{
		delete[] _data;
	}
}

uint64_t utd::string32::size() const
{
	return _size;
}
