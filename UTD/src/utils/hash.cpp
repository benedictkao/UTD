#include "hash.h"

template <>
size_t utd::hash<int>(const int& obj) {
  // works because sizeof(int) <= sizeof(size_t)
  return static_cast<size_t>(obj);
}

template <>
size_t utd::hash<unsigned int>(const unsigned int& obj) {
  // works because sizeof(int) <= sizeof(size_t)
  return static_cast<size_t>(obj);
}

template <>
size_t utd::hash<char>(const char& obj) {
  return static_cast<size_t>(obj);
}

template <>
size_t utd::hash<unsigned char>(const unsigned char& obj) {
  return static_cast<size_t>(obj);
}

template <>
size_t utd::hash<bool>(const bool& obj) {
  return static_cast<size_t>(obj);
}

template <>
size_t utd::hash<float>(const float& obj) {
  // works because sizeof(int) <= sizeof(size_t)
  return static_cast<size_t>(obj);
}