#include "Math.h"

size_t util::min(size_t a, size_t b) {
  if (a < b)
    return a;
  return b;
}

size_t util::max(size_t a, size_t b) {
  if (a > b)
    return a;
  return b;
}
