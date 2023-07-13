#include "math.h"

size_t utd::min(size_t a, size_t b) {
  if (a < b)
    return a;
  return b;
}

size_t utd::max(size_t a, size_t b) {
  if (a > b)
    return a;
  return b;
}
