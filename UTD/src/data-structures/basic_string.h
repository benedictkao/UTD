#pragma once

#include <cstddef>
#include <cstring> // should this be removed?
#include <iostream>

namespace utd {
  class basic_string {
  private:
    char*  _data;
    size_t _capacity;
    size_t _size;

  public:
    basic_string() = default;

    basic_string(const char* s);

    basic_string(const basic_string& s);

    basic_string(basic_string&& s) noexcept;

    basic_string& operator=(const basic_string& s);

    basic_string& operator=(basic_string&& s) noexcept;

    ~basic_string();

    char& operator[](size_t index);

    const char& operator[](size_t index) const;

    size_t size() const;

    const char* c_str() const;

    void reserve(size_t new_size);

    basic_string substr(size_t start, size_t len);

    basic_string operator+(const basic_string& rhs) const;

    basic_string& operator+=(const basic_string& rhs);

    basic_string operator+(const char& rhs) const;

    basic_string& operator+=(const char& rhs);

    friend bool operator==(const basic_string& lhs, const basic_string& rhs);

    friend std::ostream& operator<<(std::ostream& os, const basic_string& s);
  };
} // namespace utd

#include "basic_string.cpp"
