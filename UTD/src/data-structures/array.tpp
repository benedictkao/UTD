
template <typename T, size_t _Size>
utd::array<T, _Size>::array() = default;

template <typename T, size_t _Size>
utd::array<T, _Size>::array(const std::initializer_list<T>& list) {
  iterator it = begin();
  for (const T& item : list)
    *it++ = item;

  const_iterator last = end();
  while (it != last)
    *it++ = T();
}

template <typename T, size_t _Size>
int utd::array<T, _Size>::size() const noexcept {
  return _Size;
}

template <typename T, size_t _Size>
T& utd::array<T, _Size>::operator[](size_t index) {
  return _inner_array[index];
}

template <typename T, size_t _Size>
const T& utd::array<T, _Size>::operator[](size_t index) const {
  return _inner_array[index];
}

template <typename T, size_t _Size>
typename utd::array<T, _Size>::iterator utd::array<T, _Size>::begin() noexcept {
  return _inner_array;
}

template <typename T, size_t _Size>
typename utd::array<T, _Size>::iterator utd::array<T, _Size>::end() noexcept {
  return _inner_array + _Size;
}

template <typename T, size_t _Size>
typename utd::array<T, _Size>::const_iterator
utd::array<T, _Size>::begin() const noexcept {
  return _inner_array;
}

template <typename T, size_t _Size>
typename utd::array<T, _Size>::const_iterator
utd::array<T, _Size>::end() const noexcept {
  return _inner_array + _Size;
}