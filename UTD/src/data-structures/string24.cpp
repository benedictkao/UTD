#include "string24.h"
#include <cstring>

void utd::string24::small_string::init(c_string c_str, size_t len) {
  // TODO: there are uninitialised bytes in the middle if len is not size 23
  strcpy(_data, c_str);
  size(len);
}

void utd::string24::small_string::init(const small_string* lhs,
                                       const small_string* rhs) {
  // TODO: there are uninitialised bytes in the middle if len is not size 23
  strcpy(_data, lhs->_data);
  strcpy(_data + lhs->size(), rhs->_data);
  size(lhs->size() + rhs->size());
}

void utd::string24::small_string::init(const small_string* lhs, char rhs) {
  // TODO: there are uninitialised bytes in the middle if len is not size 23
  strcpy(_data, lhs->_data);
  _data[lhs->size()]     = rhs;
  _data[lhs->size() + 1] = 0;
  size(lhs->size() + 1);
}

size_t utd::string24::small_string::size() const noexcept {
  return static_cast<size_t>(_last_byte);
}

void utd::string24::small_string::size(size_t size) {
  _last_byte = static_cast<uint8_t>(size);
}

utd::string24::c_string utd::string24::small_string::c_str() const noexcept {
  return _data;
}

utd::string24::char_ref utd::string24::small_string::charAt(size_t index) {
  return _data[index];
}

utd::string24::const_char_ref
utd::string24::small_string::charAt(size_t index) const noexcept {
  return _data[index];
}

utd::string24::string24() : _data(0), _size(0), _capacity(0) {}

utd::string24::string24(c_string c_str) {
  size_t len = strlen(c_str);

  if (len < SMALL_STRING_CAPACITY) {
    toSmall()->init(c_str, len);
  } else {
    _size     = static_cast<uint32_t>(len);
    _capacity = _size;

    _data = new char[_capacity + 1];
    strcpy(_data, c_str);
    setLarge();
  }
}

utd::string24::string24(const_string_ref s)
    : _size(s._size), _capacity(s._capacity) {
  if (s.isLarge()) {
    size_t arr_size = static_cast<size_t>(s._capacity ^ LARGE_STRING_FLAG) + 1;
    _data           = new char[arr_size];
    strcpy(_data, s._data);
  } else {
    _data = s._data;
  }
}

utd::string24::string24(string_r_value s) noexcept
    : _data(s._data), _size(s._size), _capacity(s._capacity) {
  s._data     = 0;
  s._size     = 0;
  s._capacity = 0;
}

utd::string24& utd::string24::operator=(const_string_ref s) {
  if (isLarge())
    delete[] _data;

  if (s.isLarge()) {
    size_t arr_size = static_cast<size_t>(s._capacity ^ LARGE_STRING_FLAG) + 1;
    _data           = new char[arr_size];
    strcpy(_data, s._data);
  } else {
    _data = s._data;
  }

  _size     = s._size;
  _capacity = s._capacity;
  return *this;
}

utd::string24& utd::string24::operator=(string_r_value s) noexcept {
  if (isLarge())
    delete[] _data;

  _size       = s._size;
  _capacity   = s._capacity;
  s._data     = 0;
  s._size     = 0;
  s._capacity = 0;
  return *this;
}

utd::string24::~string24() {
  if (isLarge())
    delete[] _data;
}

size_t utd::string24::size() const noexcept {
  if (isLarge())
    return static_cast<size_t>(_size);
  else
    return toSmall()->size();
}

size_t utd::string24::capacity() const noexcept {
  if (isLarge())
    return static_cast<size_t>(_capacity ^ LARGE_STRING_FLAG);
  else
    return SMALL_STRING_CAPACITY;
}

utd::string24::c_string utd::string24::c_str() const noexcept {
  if (isLarge())
    return _data;
  else
    return toSmall()->c_str();
}

bool utd::string24::isLarge() const noexcept {
  return _capacity & LARGE_STRING_FLAG;
}

void utd::string24::setLarge() noexcept {
  _capacity |= LARGE_STRING_FLAG;
}

inline utd::string24::small_string* utd::string24::toSmall() noexcept {
  return reinterpret_cast<small_string*>(this);
}

inline const utd::string24::small_string*
utd::string24::toSmall() const noexcept {
  return reinterpret_cast<const small_string*>(this);
}

utd::string24::char_ref utd::string24::operator[](size_t index) {
  if (isLarge())
    return _data[index];
  else
    return toSmall()->charAt(index);
}

utd::string24::const_char_ref
utd::string24::operator[](size_t index) const noexcept {
  if (isLarge())
    return _data[index];
  else
    return toSmall()->charAt(index);
}

utd::string24 utd::string24::operator+(const_string_ref rhs) const {
  string24 lhs;
  size_t   sz   = size();
  lhs._capacity = lhs._size = sz + rhs.size();
  if (lhs._size > SMALL_STRING_CAPACITY) {
    lhs._data = new char[lhs._capacity + 1];
    strcpy(lhs._data, c_str());
    strcpy(lhs._data + sz, rhs.c_str());
    lhs.setLarge();
  } else {
    lhs.toSmall()->init(this->toSmall(), rhs.toSmall());
  }
  return lhs;
}

utd::string24& utd::string24::operator+=(const_string_ref rhs) {
  // TODO: reduce code duplication
  if (isLarge()) {
    size_t cap      = static_cast<size_t>(_capacity ^ LARGE_STRING_FLAG);
    size_t rhs_size = rhs.size();
    size_t tot_size = _size + rhs_size;
    if (tot_size > cap) {
      char* new_data = new char[tot_size + 1];
      strcpy(new_data, _data);
      strcpy(new_data + _size, rhs.c_str());
      delete[] _data;
      _data     = new_data;
      _size     = tot_size;
      _capacity = tot_size | LARGE_STRING_FLAG;
    } else {
      strcpy(_data + _size, rhs.c_str());
      _size = tot_size;
    }
  } else {
    small_string* lhs      = toSmall();
    size_t        lhs_size = lhs->size();
    size_t        rhs_size = rhs.size();
    size_t        tot_size = lhs_size + rhs_size;
    if (tot_size > SMALL_STRING_CAPACITY) {
      char* new_data = new char[tot_size + 1];
      strcpy(new_data, lhs->c_str());
      strcpy(new_data + lhs_size, rhs.c_str());
      _data     = new_data;
      _size     = tot_size;
      _capacity = tot_size | LARGE_STRING_FLAG;
    } else {
      strcpy(lhs->_data + lhs_size, rhs.c_str());
      lhs->size(tot_size);
    }
  }
  return *this;
}

utd::string24 utd::string24::operator+(char rhs) const {
  string24 lhs;
  size_t   sz   = size();
  lhs._capacity = lhs._size = sz + 1;
  if (lhs._size > SMALL_STRING_CAPACITY) {
    lhs._data = new char[lhs._capacity + 1];
    strcpy(lhs._data, c_str());
    char_ptr last = lhs._data + sz;
    *last         = rhs;
    ++last;
    *last = 0;
    lhs.setLarge();
  } else {
    lhs.toSmall()->init(this->toSmall(), rhs);
  }
  return lhs;
}

utd::string24& utd::string24::operator+=(char rhs) {
  // TODO: reduce code duplication
  if (isLarge()) {
    size_t cap      = static_cast<size_t>(_capacity ^ LARGE_STRING_FLAG);
    size_t tot_size = _size + 1;
    if (tot_size > cap) {
      char* new_data = new char[tot_size + 1];
      strcpy(new_data, _data);
      char_ptr ptr = new_data + _size;
      *ptr         = rhs;
      ++ptr;
      *ptr = 0;
      delete[] _data;
      _data     = new_data;
      _size     = tot_size;
      _capacity = tot_size | LARGE_STRING_FLAG;
    } else {
      char_ptr ptr = _data + _size;
      *ptr         = rhs;
      ++ptr;
      *ptr  = 0;
      _size = tot_size;
    }
  } else {
    small_string* lhs      = toSmall();
    size_t        lhs_size = lhs->size();
    size_t        tot_size = lhs_size + 1;
    if (tot_size > SMALL_STRING_CAPACITY) {
      char* new_data = new char[tot_size + 1];
      strcpy(new_data, lhs->c_str());
      char_ptr ptr = new_data + _size;
      *ptr         = rhs;
      ++ptr;
      *ptr      = 0;
      _data     = new_data;
      _size     = tot_size;
      _capacity = tot_size | LARGE_STRING_FLAG;
    } else {
      char_ptr ptr = lhs->_data + _size;
      *ptr         = rhs;
      ++ptr;
      *ptr = 0;
      lhs->size(tot_size);
    }
  }
  return *this;
}

std::ostream& utd::operator<<(std::ostream& os, const string24& s) {
  os << s.c_str();
  return os;
}
