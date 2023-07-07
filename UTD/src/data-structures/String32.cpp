#include "String32.h"

#include <cstring>

using StrType = utd::string32::STRING_TYPE;

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
static constexpr uint8_t SMALL_STRING_MAX_LENGTH{ 15 };

// Private Methods

uint8_t& utd::string32::getStringTypeFlag()
{
	return *((uint8_t*)(&_capacity) + SMALL_STRING_MAX_LENGTH);	// TODO: consider using reinterpret_cast
}

uint8_t& utd::string32::getStringTypeFlag() const
{
	return *((uint8_t*)(&_capacity) + SMALL_STRING_MAX_LENGTH);	// TODO: consider using reinterpret_cast with const_cast
}

bool utd::string32::isLargeString() const
{
        return getStringTypeFlag() & StrType::LARGE;
}

void utd::string32::setType(StrType type) {
	getStringTypeFlag() = type;
}


// Constructors

utd::string32::string32()
{
	// TODO: can we improve this by using a global variable for the empty string?
	_size = 0;
	_capacity = 0;
	_data = (char*)&_capacity;
}

utd::string32::string32(const char* s)
{
	_size = strlen(s);
	if (_size > SMALL_STRING_MAX_LENGTH) 
	{
		_capacity = _size + 1;
		_data = new char[_capacity];
                setType(StrType::LARGE);
	}
	else 
	{
		_data = (char*) &_capacity;
	}
	strcpy(_data, s);
}

utd::string32::string32(const string32& s)
{ 
	_size = s._size;
	_capacity = s._capacity;
	if (_size > SMALL_STRING_MAX_LENGTH)
	{
		_data = new char[_capacity];
	}
	else
	{
		_data = (char*)&_capacity;
	}
    strcpy(_data, s._data);
}

utd::string32::string32(string32&& s) noexcept
{
	_size = s._size;
    _capacity = s._capacity;
    if (_size > SMALL_STRING_MAX_LENGTH)
	{
		_data = s._data;
    }
	else
	{
		_data = (char*)&_capacity;
        strcpy(_data, s._data);
    }

    s._data = nullptr;
	s._size = 0;
    s._capacity = 0;
}

utd::string32& utd::string32::operator=(const string32& s) 
{
    if (_size > SMALL_STRING_MAX_LENGTH)
	{
        delete[] _data;
    }
    _size = s._size;
    _capacity = s._capacity;

	if (_size > SMALL_STRING_MAX_LENGTH)
	{
        _data = new char[_capacity];
    }
	else
	{
        _data = (char*)&_capacity;
    }
    strcpy(_data, s._data);
    return *this;
}

utd::string32& utd::string32::operator=(string32&& s) noexcept 
{
    if (_size > SMALL_STRING_MAX_LENGTH)
	{
        delete[] _data;
    }
    _size = s._size;
    _capacity = s._capacity;
    if (_size > SMALL_STRING_MAX_LENGTH)
	{
        _data = s._data;
    }
	else
	{
        _data = (char*)&_capacity;
        strcpy(_data, s._data);
    }

    s._data = nullptr;
    s._size = 0;
    s._capacity = 0;
    return *this;
}


utd::string32::~string32()
{
	if (isLargeString())
	{
		delete[] _data;
	}
}

// Public Methods

uint64_t utd::string32::size() const
{
	return _size;
}

uint64_t utd::string32::capacity() const
{
	if (isLargeString())
	{
		return _capacity;
	}
	else
	{
		return SMALL_STRING_MAX_LENGTH + 1;
	}
}

const char* utd::string32::c_str() const
{
    return _data;
}

/*
 * Will reserve space for a n-size string. Means that at least n+1 memory space will be allocated to include the null terminator.
 */
void utd::string32::reserve(uint64_t n)
{
	if (n <= SMALL_STRING_MAX_LENGTH) return;

	char* new_data = new char[n + 1];

	if (n < _size) _size = n;
	memcpy(new_data, _data, _size + 1);
	if (isLargeString()) delete[] _data;
	_capacity = n + 1;

	_data = new_data;
	*(_data + _size) = 0;	// regenerate the null terminator

	setType(StrType::LARGE);
}

// Operators

char& utd::string32::operator[](uint64_t index)
{
	return _data[index];
}

const char& utd::string32::operator[](uint64_t index) const {
        return _data[index];
}

utd::string32 utd::string32::operator+(const utd::string32& rhs) const
{
	utd::string32 lhs;
	lhs._size = this->_size + rhs._size;

	if (lhs._size > SMALL_STRING_MAX_LENGTH)
	{
		lhs._capacity = lhs._size + 1;
		lhs._data = new char[_capacity];
                lhs.setType(StrType::LARGE);
	}
	else
	{
		lhs._data = (char*)&lhs._capacity;
	}
	strcpy(lhs._data, this->_data);
	strcpy(lhs._data + this->_size, rhs._data);
	return lhs;
}

utd::string32& utd::string32::operator+=(const utd::string32& rhs) {
        const uint64_t new_size = _size + rhs._size;
        if (isLargeString()) {
                if (new_size >= _capacity) {
                  _capacity = new_size + 1;
                  char* new_data = new char[_capacity];
                  strcpy(new_data, _data);
                  delete[] _data;
                  _data = new_data;
                }
        } else if (new_size > SMALL_STRING_MAX_LENGTH) {
                const uint64_t new_capacity = new_size + 1;
                char*          new_data     = new char[new_capacity];
                strcpy(new_data, _data);
                _data     = new_data;
                _capacity = new_capacity;
                setType(StrType::LARGE);
        }
        strcpy(_data + _size, rhs._data);
        _size = new_size;
		return *this;
}

utd::string32 utd::string32::operator+(const char& rhs) const
{
	utd::string32 lhs;
	lhs._size = this->_size + 1;

	if (lhs._size > SMALL_STRING_MAX_LENGTH)
	{
		lhs._capacity = lhs._size + 1;
		lhs._data = new char[_capacity];
                lhs.setType(StrType::LARGE);
	}
	else
	{
		lhs._data = (char*)&lhs._capacity;
	}
	strcpy(lhs._data, this->_data);
	*(lhs._data + this->_size) = rhs;			// replace null termination with rhs char
	*(lhs._data + this->_size + 1) = 0;			// add back null termination
	return lhs;
}

utd::string32& utd::string32::operator+=(const char& rhs) {
        _size++;
        if (isLargeString()) {
                if (_size == _capacity) {
                  _capacity++;
                  char* new_data = new char[_capacity];
                  strcpy(new_data, _data);
                  delete[] _data;
                  _data = new_data;
                }
        } else if (_size > SMALL_STRING_MAX_LENGTH) {
                const uint64_t new_capacity = _size + 1;
                char*          new_data     = new char[new_capacity];
                strcpy(new_data, _data);
                _data     = new_data;
                _capacity = new_capacity;
                setType(StrType::LARGE);
        }
        *(_data + this->_size) = rhs;			// replace null termination with rhs char
        *(_data + this->_size + 1) = 0;			// add back null termination
        return *this;
}

bool utd::operator==(const string32& lhs, const string32& rhs)
{
	if (lhs._size != rhs._size) return false;

	for (int i = 0; i < lhs._size; i++)
		if (lhs[i] != rhs[i]) return false;

	return true;
}

// Output Stream

std::ostream& utd::operator<<(std::ostream& os, const utd::string32& s) {
    os << s._data;
    return os;
}