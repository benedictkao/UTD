#include "string24.h"
#include <cstring>

void utd::string24::small_string::initEmpty() {
  memset(_data, 0, SMALL_STRING_MAX_SIZE);
  size(0);
}

void utd::string24::small_string::init(c_string c_str, size_t len) {
  // TODO: there are uninitialised bytes in the middle if len is not size 23
  strcpy(_data, c_str);
  size(len);
}

size_t utd::string24::small_string::size() const noexcept {
  return static_cast<size_t>(SMALL_STRING_MAX_SIZE - remainingCapacity());
}

void utd::string24::small_string::size(uint8_t size) {
  _data[SMALL_STRING_MAX_SIZE] = SMALL_STRING_MAX_SIZE - size;
}

utd::string24::c_string utd::string24::small_string::c_str() const noexcept {
  return _data;
}

uint8_t utd::string24::small_string::remainingCapacity() const noexcept {
  return _data[SMALL_STRING_MAX_SIZE] & REMAINING_CAPACITY_BIT_MASK;
}

utd::string24::char_ref utd::string24::small_string::charAt(size_t index) {
  return _data[index];
}

utd::string24::const_char_ref utd::string24::small_string::charAt(size_t index) const noexcept {
  return _data[index];
}

utd::string24::string24() {
  toSmall()->initEmpty();
}

utd::string24::string24(c_string c_str) {
  size_t len = strlen(c_str);

  if (len <= SMALL_STRING_MAX_SIZE) {
    toSmall()->init(c_str, len);
  } else {
    _data = new char[len + 1];
    strcpy(_data, c_str);
    _size     = static_cast<uint32_t>(len);
    _capacity = _size + 1;
    setLarge();
  }
}

size_t utd::string24::size() const noexcept {
  if (isLarge())
    return static_cast<size_t>(_size);
  else
    return toSmall()->size();
}

utd::string24::c_string utd::string24::c_str() const noexcept {
  if (isLarge())
    return _data;
  else
    return toSmall()->c_str();
}

bool utd::string24::isLarge() const noexcept {
  return _flags & LARGE_STRING_FLAG;
}

void utd::string24::setLarge() noexcept {
  _flags |= LARGE_STRING_FLAG;
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

std::ostream& utd::operator<<(std::ostream& os, const string24& s) {
  os << s.c_str();
  return os;
}
