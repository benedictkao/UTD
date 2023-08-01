#pragma once

#include <cstddef>
#include <cstring>

#include "../utils/math.h"

// TODO: can this be a util method and take in iterator start and end?
// Can be reused for set and map
template <typename T, class Alloc>
void utd::vector<T, Alloc>::fill(const T& val, size_t start, size_t end) {
  for (int i = start; i < end; i++)
    _inner_array[i] = val;
}

// Destructors
template <typename T, class Alloc>
utd::vector<T, Alloc>::~vector() {
  alloc.deallocate(_inner_array, sizeof(T) * _capacity);
}

// Constructors
template <class T, class Alloc>
utd::vector<T, Alloc>::vector()
    : _size(0), _capacity(DEFAULT_VECTOR_CAPACITY), _inner_array(nullptr) {}

template <typename T, class Alloc>
utd::vector<T, Alloc>::vector(size_t size)
    : _size(size)
    , _capacity(size)
    , _inner_array(alloc.allocate(sizeof(T) * size)) {}

template <typename T, class Alloc>
utd::vector<T, Alloc>::vector(size_t size, const T& val)
    : _size(size)
    , _capacity(size)
    , _inner_array(alloc.allocate(sizeof(T) * size)) {
  fill(val, 0, size);
}

// copy constructor
template <typename T, class Alloc>
utd::vector<T, Alloc>::vector(const utd::vector<T, Alloc>& target_vector)
    : _size(target_vector._size)
    , _capacity(target_vector._capacity)
    , _inner_array(alloc.allocate(sizeof(T) * target_vector._capacity)) {

  for (int i = 0; i < _capacity; i++)
    _inner_array[i] = target_vector._inner_array[i];
};

// move constructor
template <typename T, class Alloc>
utd::vector<T, Alloc>::vector(utd::vector<T, Alloc>&& target_vector) noexcept
    : _size(target_vector._size)
    , _capacity(target_vector._capacity)
    , _inner_array(target_vector._inner_array) {
  target_vector._size        = 0;
  target_vector._capacity    = 0;
  target_vector._inner_array = nullptr;
};

// copy assignment
template <typename T, class Alloc>
utd::vector<T, Alloc>&
utd::vector<T, Alloc>::operator=(const utd::vector<T, Alloc>& target_vector) {
  alloc.deallocate(_inner_array, sizeof(T) * _capacity);

  _size        = target_vector._size;
  _capacity    = target_vector._capacity;
  _inner_array = alloc.allocate(sizeof(T) * _capacity);

  for (int i = 0; i < _size; i++)
    _inner_array[i] = target_vector._inner_array[i];
  return *this;
}

// move assignment
template <typename T, class Alloc>
utd::vector<T, Alloc>&
utd::vector<T, Alloc>::operator=(utd::vector<T, Alloc>&& target_vector) {
  alloc.deallocate(_inner_array, sizeof(T) * _capacity);
  _size        = target_vector._size;
  _capacity    = target_vector._capacity;
  _inner_array = alloc.allocate(sizeof(T) * _capacity);
  _inner_array = target_vector._inner_array;

  target_vector._size        = 0;
  target_vector._capacity    = 0;
  target_vector._inner_array = nullptr;
  return *this;
}

// Methods
template <typename T, class Alloc>
void utd::vector<T, Alloc>::push_back(const T& new_item) {
  if (_size == _capacity) {
    reserve(utd::max(_capacity, 1) *
            CAPACITY_RESIZE_RATE); // TODO: fix having to call max
  }

  _inner_array[_size] = new_item;
  _size++;
};

template <typename T, class Alloc>
void utd::vector<T, Alloc>::push_back(T&& new_item) {
  if (_size == _capacity) {
    reserve(utd::max(_capacity, 1) *
            CAPACITY_RESIZE_RATE); // TODO: fix having to call max
  }

  _inner_array[_size] = new_item;
  _size++;
};

template <typename T, class Alloc>
size_t utd::vector<T, Alloc>::size() const noexcept {
  return _size;
};

template <typename T, class Alloc>
void utd::vector<T, Alloc>::pop_back() {
  if (_size == 0)
    throw VectorEmptyErr();

  _size--;
}

template <typename T, class Alloc>
T utd::vector<T, Alloc>::at(size_t idx) {
  if (idx < 0 || idx >= _size)
    throw IdxOutOfRange();

  return _inner_array[idx];
}

/*
 * Does not change the capacity
 */
template <typename T, class Alloc>
void utd::vector<T, Alloc>::clear() {
  _size = 0;
}

template <typename T, class Alloc>
void utd::vector<T, Alloc>::reserve(size_t new_capacity) {
  if (new_capacity <= _capacity)
    return;

  T* new_inner_array = alloc.allocate(sizeof(T) * new_capacity);
  memcpy(new_inner_array, _inner_array, sizeof(T) * _size);

  alloc.deallocate(_inner_array, sizeof(T) * _capacity);

  _inner_array = new_inner_array;
  _capacity    = new_capacity;
}

template <typename T, class Alloc>
void utd::vector<T, Alloc>::resize(size_t new_capacity) {
  T default_value = T();
  resize(new_capacity, default_value);
}

template <typename T, class Alloc>
void utd::vector<T, Alloc>::resize(size_t new_size, const T& value) {
  if (new_size == _size == _capacity) {
    return;
  }

  const size_t num_existing = utd::min(_size, new_size);

  T* new_inner_array = alloc.allocate(new_size * sizeof(T));
  memcpy(new_inner_array, _inner_array, sizeof(T) * num_existing);
  alloc.deallocate(_inner_array, sizeof(T) * _capacity);

  _size        = new_size;
  _capacity    = new_size;
  _inner_array = new_inner_array;


  fill(value, num_existing, new_size);
}

// operators
template <typename T, class Alloc>
T& utd::vector<T, Alloc>::operator[](size_t index) {
  if (index >= _size || index < 0)
    throw IdxOutOfRange();

  return _inner_array[index];
};

template <typename T, class Alloc>
const T& utd::vector<T, Alloc>::operator[](size_t index) const {
  if (index >= _size || index < 0)
    throw IdxOutOfRange();

  return _inner_array[index];
};

template <typename T, class Alloc>
typename utd::vector<T, Alloc>::iterator
utd::vector<T, Alloc>::begin() noexcept {
  return _inner_array;
};

template <typename T, class Alloc>
typename utd::vector<T, Alloc>::iterator utd::vector<T, Alloc>::end() noexcept {
  return _size > 0 ? _inner_array + _size - 1 : _inner_array;
};

template <typename T, class Alloc>
typename utd::vector<T, Alloc>::const_iterator
utd::vector<T, Alloc>::begin() const noexcept {
  return _inner_array;
};

template <typename T, class Alloc>
typename utd::vector<T, Alloc>::const_iterator
utd::vector<T, Alloc>::end() const noexcept {
  return _size > 0 ? _inner_array + _size - 1 : _inner_array;
};