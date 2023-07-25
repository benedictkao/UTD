#pragma once

/*
 * TODO: added this dependency to fix ubuntu compilation. Can it be removed?
 * Maybe we can have our own constants/typedef header file instead
 */
#include <cstddef>

namespace utd {

  /*
   * Only declare template function here, don't provide definition, because we
   * will only allow full explicit specialisation. If the hash function for the
   * class is not found, it should throw a compiler error
   */
  template <typename T>
  size_t hash(const T&);
} // namespace utd