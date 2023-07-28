#pragma once

#include <initializer_list>

namespace utd {

  /*
   * Improvements:
   * 1. Return T& instead of T to avoid copying the object each time it is
   * accessed (also allows objects in the array to get mutated)
   * 2. Get is a const function and returns const reference so that it can be
   * used in other const functions
   * 3. Use size_t instead of int for better consistency
   */
  template <typename T, size_t _Size>
  class array {
  public:
    typedef T*       iterator;
    typedef const T* const_iterator;

  private:
    T _inner_array[_Size];

  public:
    array();

    array(const std::initializer_list<T>&);

    int size() const noexcept;

    /*
     * Return mutable reference for both set and get
     */
    T& operator[](size_t index);

    /*
     * Return immutable reference for get operations only. Useful for
     * const functions
     */
    const T& operator[](size_t index) const;

    iterator begin() noexcept;

    iterator end() noexcept;

    const_iterator begin() const noexcept;

    const_iterator end() const noexcept;
  };
} // namespace utd

#include "array.tpp"