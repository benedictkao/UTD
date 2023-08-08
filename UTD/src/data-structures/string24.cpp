#include "string24.h"

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
 * - 8 bytes for data pointer -> points to capacity (which is used to start char
 * array in small string)
 * - 8 bytes for size
 * - 16 bytes for char array (last element must be null terminator)
 */

static constexpr size_t CHAR_BUFFER_SIZE{ 7 };

static constexpr uint8_t FLAG_LARGE_STRING{ 0b10000000 };

// Private Methods

bool utd::string24::isLargeString() const {
  return _small_size == SMALL_STRING_MAX_LENGTH;
}

void utd::string24::setLargeString() {
  _small_size = SMALL_STRING_MAX_LENGTH;
}

/*
 * For small strings, _capacity, _char_buffer and _flags are used to store the
 * character data and null terminator
 */
void utd::string24::pointToInSituMemory() {
  // _data = static_cast<char*>)() &_capacity;
}

const char* utd::string24::data() const {
  if (isLargeString()) {
    return _ptr;
  }
  return _data;
}


// Constructors

utd::string24::string24() {
  // TODO: can we improve this by using a global variable for the empty string?
  _small_size = 0;
}

utd::string24::string24(const char* s) {
  if (strlen(s) >= SMALL_STRING_MAX_LENGTH) {
    _size = strlen(s);
    _ptr  = new char[_size + 1];
    strcpy(_ptr, s);
    setLargeString();
    _ptr[_size] = '\0';
  } else {
    _small_size = strlen(s);
    strcpy(_data, s);
    _data[_small_size] = '\0';
  }
}

utd::string24::string24(const string24& s) {
  if (s.isLargeString()) {
    _size = s._size;
    _ptr  = new char[_size + 1];
    strcpy(_ptr, s._ptr);
    setLargeString();
    _ptr[_size] = '\0';
  } else {
    _small_size = s._small_size;
    memcpy(_data, s._data, _small_size);
    _data[_small_size] = '\0';
  }
}

utd::string24::string24(string24&& s) noexcept {
  if (s.isLargeString()) { // is large string
    _size = s._size;
    _ptr  = s._ptr;
    setLargeString();
    _ptr[_size] = '\0';
  } else {
    _small_size = s._small_size;
    memcpy(_data, s._data, _small_size);
    _data[_small_size] = '\0';
  }

  s._ptr        = nullptr;
  s._size       = 0;
  s._small_size = 0;
  memset(s._data, 0, CHAR_BUFFER_SIZE);
}

utd::string24& utd::string24::operator=(const string24& s) {
  if (isLargeString()) {
    delete[] _ptr;
  }

  if (s.isLargeString()) {
    _size = s._size;
    _ptr  = new char[_size + 1];
    strcpy(_ptr, s._ptr);
    setLargeString();
    _ptr[_size] = '\0';
  } else {
    _small_size = s._small_size;
    memcpy(_data, s._data, _small_size);
    _data[_small_size] = '\0';
  }

  return *this;
}

utd::string24& utd::string24::operator=(string24&& s) noexcept {
  if (isLargeString()) {
    delete[] _ptr;
  }

  if (s.isLargeString()) {
    _size = s._size;
    _ptr  = s._ptr;
    setLargeString();
  } else {
    _small_size = s._small_size;
    memcpy(_data, s._data, _small_size);
    _data[_small_size] = '\0';
  }

  s._ptr = nullptr;
  memset(s._data, 0, s._small_size);
  s._size       = 0;
  s._small_size = 0;
  return *this;
}


utd::string24::~string24() {
  if (isLargeString()) {
    delete[] _ptr;
  }
}

// Public Methods

uint64_t utd::string24::size() const noexcept {
  if (isLargeString())
    return _size;
  else if (_small_size % 2 == 0)
    return 5;
  return _small_size;
}

bool utd::string24::empty() const {
  return size() == 0;
}

uint64_t utd::string24::capacity() const {
  if (isLargeString()) {
    return _size + 1;
  } else {
    return SMALL_STRING_MAX_LENGTH + 1;
  }
}

const char* utd::string24::c_str() const noexcept {
  if (isLargeString()) {
    return _ptr;
  } else {
    return _data;
  }
}

/*
 * Will reserve space for a n-size string. This means that at least n+1 memory
 * space will be allocated to include the null terminator.
 */
void utd::string24::reserve(uint64_t n) {
  if (n <= SMALL_STRING_MAX_LENGTH) {
    return;
  }

  char* new_data = new char[n + 1];

  if (n < _size) {
    _size = n;
  }

  if (isLargeString()) {
    memcpy(new_data, _ptr, _size);
    delete[] _ptr;
  } else {
    setLargeString();
    memcpy(new_data, _data, _size);
  }

  _size           = n;
  _ptr            = new_data;
  *(_ptr + _size) = 0; // regenerate the null terminator
}

// Operators

char& utd::string24::operator[](uint64_t index) {
  if (isLargeString()) {
    return _ptr[index];
  } else {
    return _data[index];
  }
}

const char& utd::string24::operator[](uint64_t index) const {
  if (isLargeString()) {
    return _ptr[index];
  } else {
    return _data[index];
  }
}

utd::string24 utd::string24::operator+(const utd::string24& rhs) const {
  utd::string24 lhs;

  if (rhs.size() + size() > SMALL_STRING_MAX_LENGTH) {
    lhs._size = rhs.size() + size();
    lhs._ptr  = new char[lhs._size + 1];
    lhs.setLargeString();
    strcpy(lhs._ptr, this->data());
    strcpy(lhs._ptr + this->size(), rhs.data());
  } else {
    lhs._small_size = rhs.size() + size();
    strcpy(lhs._data, this->data());
    strcpy(lhs._data + this->size(), rhs.data());
  }

  return lhs;
}

utd::string24& utd::string24::operator+=(const utd::string24& rhs) {
  const size_t new_size = this->size() + rhs.size();
  if (isLargeString()) {
    if (new_size >= this->size()) {
      char* new_ptr = new char[new_size + 1];
      strcpy(new_ptr, _ptr);
      delete[] _ptr;
      _ptr = new_ptr;
    }
    strcpy(_ptr + size(), rhs.data());
    _size = new_size;

  } else if (new_size > SMALL_STRING_MAX_LENGTH) {
    _ptr = new char[new_size + 1];
    strcpy(_ptr, _data);
    strcpy(_ptr + size(), rhs.data());
    setLargeString();
    _size = new_size;

  } else {
    strcpy(_data + size(), rhs.data());
    _small_size = (uint8_t) new_size;
  }

  return *this;
}

utd::string24 utd::string24::operator+(char rhs) const {
  utd::string24 lhs;
  if (this->size() + 1 > SMALL_STRING_MAX_LENGTH) {
    lhs._size = this->size() + 1;
    lhs._ptr  = new char[lhs.size() + 1];

    if (this->isLargeString()) {
      strcpy(lhs._ptr, this->_ptr);
    } else {
      strcpy(lhs._ptr, this->_data);
    }

    *(lhs._ptr + this->size()) = rhs; // replace null termination with rhs char
    *(lhs._ptr + this->size() + 1) = 0; // add back null termination
                                        //
    lhs.setLargeString();
  } else {
    lhs._small_size = this->size() + 1;
    strcpy(lhs._data, this->_data);
    *(lhs._data + this->size()) = rhs; // replace null termination with rhs char
    *(lhs._data + this->size() + 1) = 0; // add back null termination
  }

  return lhs;
}

utd::string24& utd::string24::operator+=(char rhs) {

  if (isLargeString()) {
    _size++;
    char* new_ptr = new char[_size + 1];
    strcpy(new_ptr, _ptr);
    delete[] _ptr;

    _ptr            = new_ptr;
    _ptr[_size - 1] = rhs;
    _ptr[_size]     = '\0';

  } else if (this->size() + 1 > SMALL_STRING_MAX_LENGTH) {
    size_t new_size = this->size() + 1;
    char*  new_ptr  = new char[new_size + 1];
    strcpy(new_ptr, _data);
    setLargeString();

    _size           = new_size;
    _ptr            = new_ptr;
    _ptr[_size - 1] = rhs;
    _ptr[_size]     = '\0';
  } else {
    *(_data + this->_small_size) =
      rhs; // replace null termination with rhs char

    this->_small_size++;
    *(_data + this->size()) = 0; // add back null termination
  }

  return *this;
}

bool utd::operator==(const string24& lhs, const char* rhs) {
  return strcmp(lhs.c_str(), rhs) == 0;
}

bool utd::operator==(const string24& lhs, const string24& rhs) {
  return strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

// Output Stream

std::ostream& utd::operator<<(std::ostream& os, const utd::string24& s) {
  if (s.isLargeString()) {
    os << s._ptr;
  } else {
    os << s._data;
  }
  return os;
}
