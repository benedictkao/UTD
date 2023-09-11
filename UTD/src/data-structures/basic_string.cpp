// #include "basic_string.h"

utd::basic_string::basic_string(const char* s) {
  _size     = strlen(s);
  _capacity = _size + 1;
  _data     = new char[_capacity];
  strcpy(_data, s);
}

utd::basic_string::basic_string(const utd::basic_string& s) {
  _size     = s._size;
  _capacity = s._capacity;
  _data     = new char[_capacity];
  strcpy(_data, s._data);
}

utd::basic_string::basic_string(utd::basic_string&& s) noexcept {
  _size       = s._size;
  _capacity   = s._capacity;
  _data       = s._data;
  s._data     = nullptr;
  s._size     = 0;
  s._capacity = 0;
}

utd::basic_string& utd::basic_string::operator=(const utd::basic_string& s) {
  _size     = s._size;
  _capacity = s._capacity;
  delete[] _data;
  _data = new char[_capacity];
  strcpy(_data, s._data);
  return *this;
}

utd::basic_string& utd::basic_string::operator=(utd::basic_string&& s) noexcept {
  _size     = s._size;
  _capacity = s._capacity;
  delete[] _data;
  _data       = s._data;
  s._data     = nullptr;
  s._size     = 0;
  s._capacity = 0;
  return *this;
}

utd::basic_string::~basic_string() {
  delete[] _data;
}

char& utd::basic_string::operator[](size_t index) {
  return _data[index]; // TODO: what if index > _size but < _capacity?
}

const char& utd::basic_string::operator[](size_t index) const {
  return _data[index]; // TODO: what if index > _size but < _capacity?
}

size_t utd::basic_string::size() const {
  return _size;
}

const char* utd::basic_string::c_str() const {
  return _data;
}

void utd::basic_string::reserve(size_t new_size) {
  if (new_size <= _capacity - 1) {
    return;
  }
  _capacity       = new_size + 1;
  char* new_array = new char[_capacity];
  strcpy(new_array, _data);
  delete[] _data;
  _data = new_array;
}

utd::basic_string utd::basic_string::substr(size_t start, size_t len) {
  utd::basic_string sub;
  sub._size     = len;
  sub._capacity = len + 1;
  sub._data     = new char[sub._capacity];
  memcpy(sub._data, this->_data + start, len * sizeof(char));
  *(sub._data + len) = 0;
  return sub;
}

utd::basic_string utd::basic_string::operator+(const utd::basic_string& rhs) const {
  utd::basic_string lhs;
  lhs._size     = _size + rhs._size;
  lhs._capacity = lhs._size + 1;

  lhs._data = new char[lhs._capacity];
  strcpy(lhs._data, _data);
  strcpy(lhs._data + _size, rhs._data);
  return lhs;
}

utd::basic_string& utd::basic_string::operator+=(const utd::basic_string& rhs) {
  size_t combined_str_size = _size + rhs._size;
  reserve(combined_str_size);
  strcpy(_data + _size, rhs._data);
  _size = combined_str_size;
  return *this;
}

utd::basic_string utd::basic_string::operator+(const char& rhs) const {
  utd::basic_string lhs;
  lhs._size     = _size + 1;
  lhs._capacity = _capacity + 1;

  lhs._data = new char[lhs._capacity];
  strcpy(lhs._data, _data);
  *(lhs._data + _size)     = rhs; // replace null termination with rhs char
  *(lhs._data + _size + 1) = 0;   // add back null termination
  return lhs;
}

utd::basic_string& utd::basic_string::operator+=(const char& rhs) {
  reserve(_size + 1);
  *(_data + _size)     = rhs; // replace null termination with rhs char
  *(_data + _size + 1) = 0;   // add back null termination
  _size++;
  return *this;
}

bool utd::operator==(const basic_string& lhs, const basic_string& rhs) {
  if (lhs._size != rhs._size)
    return false;

  for (int i = 0; i < lhs._size; i++)
    if (lhs[i] != rhs[i])
      return false;

  return true;
}

std::ostream& utd::operator<<(std::ostream& os, const utd::basic_string& s) {
  os << s._data;
  return os;
}
