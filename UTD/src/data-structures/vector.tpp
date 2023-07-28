#pragma once

#include "../utils/math.h"
#include <cstddef>
#include <cstring>

// TODO: can this be a util method and take in iterator start and end?
// Can be reused for set and map
template <typename T>
void utd::vector<T>::fill(const T& val, size_t start, size_t end) {
  for (int i = start; i < end; i++)
    _inner_array[i] = val;
}


// Destructors
template <typename T>
utd::vector<T>::~vector() {
  delete[] _inner_array;
}

// Constructors
template <typename T>
utd::vector<T>::vector()
    : _size(0), _capacity(DEFAULT_VECTOR_CAPACITY), _inner_array(nullptr) {}

template <typename T>
utd::vector<T>::vector(size_t size)
    : _size(size), _capacity(size), _inner_array(new T[size]()) {}

template <typename T>
utd::vector<T>::vector(size_t size, const T& val)
    : _size(size), _capacity(size), _inner_array(new T[size]) {
  fill(val, 0, size);
}

// copy constructor
template <typename T>
utd::vector<T>::vector(const utd::vector<T>& target_vector)
    : _size(target_vector._size)
    , _capacity(target_vector._capacity)
    , _inner_array(new T[target_vector._capacity]) {
  for (int i = 0; i < _capacity; i++)
    _inner_array[i] = target_vector._inner_array[i];
};

// move constructor
template <typename T>
utd::vector<T>::vector(utd::vector<T>&& target_vector) noexcept
    : _size(target_vector._size)
    , _capacity(target_vector._capacity)
    , _inner_array(target_vector._inner_array) {
  target_vector._size        = 0;
  target_vector._capacity    = 0;
  target_vector._inner_array = nullptr;
};

// copy assignment
template <typename T>
utd::vector<T>& utd::vector<T>::operator=(const utd::vector<T>& target_vector) {
  delete[] _inner_array;
  _size     = target_vector._size;
  _capacity = target_vector._capacity;

  for (int i = 0; i < _size; i++)
    _inner_array[i] = target_vector._inner_array[i];
  return *this;
}

// move assignment
template <typename T>
utd::vector<T>& utd::vector<T>::operator=(utd::vector<T>&& target_vector) {
  delete[] _inner_array;
  _size        = target_vector._size;
  _capacity    = target_vector._capacity;
  _inner_array = target_vector._inner_array;

  target_vector._size        = 0;
  target_vector._capacity    = 0;
  target_vector._inner_array = nullptr;
  return *this;
}

// Methods
template <typename T>
void utd::vector<T>::push_back(const T& new_item) {
  if (_size == _capacity) {
    reserve(utd::max(_capacity, 1) *
            CAPACITY_RESIZE_RATE); // TODO: fix having to call max
  }

  _inner_array[_size] = new_item;
  _size++;
};

template <typename T>
void utd::vector<T>::push_back(T&& new_item) {
  if (_size == _capacity) {
    reserve(utd::max(_capacity, 1) *
            CAPACITY_RESIZE_RATE); // TODO: fix having to call max
  }

  _inner_array[_size] = new_item;
  _size++;
};

template <typename T>
size_t utd::vector<T>::size() const noexcept {
  return _size;
};

template <typename T>
T* utd::vector<T>::begin() {
  return _inner_array;
}

template <typename T>
T* utd::vector<T>::end() {
  return _size > 0 ? _inner_array + _size - 1 : _inner_array;
}

// This isn't in std lib
template <typename T>
void utd::vector<T>::pop() {
  if (_size == 0)
    throw VectorEmptyErr();

  T* new_inner_array = new T[_capacity];

  _size--;
  memcpy(new_inner_array, _inner_array + 1, sizeof(T) * _size);

  delete[] _inner_array;

  _inner_array = new_inner_array;
}

template <typename T>
void utd::vector<T>::pop_back() {
  if (_size == 0)
    throw VectorEmptyErr();

  _size--;
}


template <typename T>
T utd::vector<T>::at(size_t idx) {
  if (idx < 0 || idx >= _size) {
    throw IdxOutOfRange();
  }

  return _inner_array[idx];
}

/*
 * Does not change the capacity
 */
template <typename T>
void utd::vector<T>::clear() {
  _size = 0;
}

template <typename T>
void utd::vector<T>::reserve(size_t new_capacity) {
  if (new_capacity <= _capacity)
    return;

  T* new_inner_array = new T[new_capacity];

  memcpy(new_inner_array, _inner_array, sizeof(T) * _size);

  delete[] _inner_array;

  _inner_array = new_inner_array;
  _capacity    = new_capacity;
}

template <typename T>
void utd::vector<T>::resize(size_t new_capacity) {
  T default_value = T();
  resize(new_capacity, default_value);
}

template <typename T>
void utd::vector<T>::resize(size_t new_size, const T& value) {
  if (new_size == _size == _capacity) {
    return;
  }

  const size_t num_existing = utd::min(_size, new_size);

  T* new_inner_array = new T[new_size];
  memcpy(new_inner_array, _inner_array, sizeof(T) * num_existing);
  delete[] _inner_array;
  _size        = new_size;
  _capacity    = new_size;
  _inner_array = new_inner_array;

  fill(value, num_existing, new_size);
}

// operators
template <typename T>
T utd::vector<T>::operator[](size_t index) {
  if (index >= _size || index < 0)
    throw IdxOutOfRange();

  return _inner_array[index];
};
