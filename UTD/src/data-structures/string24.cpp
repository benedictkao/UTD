#include "string24.h"
#include <cstring>

void utd::string24::small_string::init(const_char_ptr c_str, size_t len) {
  strcpy(_data, c_str);
  _large_flag   = false;
  _rem_capacity = SMALL_STRING_MAX_SIZE - len;
}

size_t utd::string24::small_string::size() const noexcept {
  return static_cast<size_t>(SMALL_STRING_MAX_SIZE - _rem_capacity);
}

utd::string24::const_char_ptr utd::string24::small_string::c_str() const noexcept {
  return _data;
}

utd::string24::string24(const_char_ptr c_str) {
  size_t len = strlen(c_str);

  if (len <= SMALL_STRING_MAX_SIZE) {
    toSmall()->init(c_str, len);
  } else {
    _data = new char[len + 1];
    strcpy(_data, c_str);
    _size       = static_cast<uint32_t>(len);
    _capacity   = _size + 1;
    _large_flag = true;
  }
}

size_t utd::string24::size() const noexcept {
  if (_large_flag)
    return static_cast<size_t>(_size);
  else
    return toSmall()->size();
}

utd::string24::const_char_ptr utd::string24::c_str() const noexcept {
  if (_large_flag)
    return _data;
  return toSmall()->c_str();
}

inline utd::string24::small_string* utd::string24::toSmall() noexcept {
  return reinterpret_cast<small_string*>(this);
}

inline const utd::string24::small_string* utd::string24::toSmall() const noexcept {
  return reinterpret_cast<const small_string*>(this);
}

std::ostream& utd::operator<<(std::ostream& os, const string24& s) {
  os << s.c_str();
  return os;
}
