#include "hash.h"

template <>
size_t utd::hash<int>(const int& obj) {
  // works because sizeof int is always smaller than size_t
  return static_cast<size_t>(obj);
}