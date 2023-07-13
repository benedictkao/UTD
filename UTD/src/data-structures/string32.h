#pragma once

#include <cstring>
#include <iostream>
#include <stdint.h>

namespace utd {

  class string32 {
  public:
  private:
    /*
     * Since last character of a string is always null (0), the last byte is
     * guaranteed to either be unused or have value of zero. This leaves us with
     * one byte (8 bits) of memory to use for boolean flags. However, all flag
     * values have to be false when data is stored in-situ otherwise the last
     * byte cannot be used as a null terminator if the small string capacity is
     * full
     */
    struct str_flags {
    public:
      bool isLargeString = false;

    private:
      bool _unused_flags[7] = { false };

    public:
      void reset() { memset((void*) this, 0, 1); }
    };


    char*     _data;
    uint64_t  _size;
    uint64_t  _capacity;
    char      _char_buffer[7] = { 0 };
    str_flags _flags;

    bool isLargeString() const;

    void setLargeString();

    void pointToInSituMemory();

  public:
    string32();

    string32(const char*);

    string32(const string32&);

    string32(string32&&) noexcept;

    string32& operator=(const string32&);

    string32& operator=(string32&&) noexcept;

    ~string32();

    uint64_t size() const;

    uint64_t capacity() const;

    const char* c_str() const;

    void reserve(uint64_t);

    char& operator[](uint64_t);

    const char& operator[](uint64_t) const;

    string32 operator+(const string32&) const;

    string32& operator+=(const string32&);

    string32 operator+(const char&) const;

    string32& operator+=(const char&);

    friend bool operator==(const string32&, const string32&);

    friend std::ostream& operator<<(std::ostream&, const string32&);
  };
} // namespace utd
